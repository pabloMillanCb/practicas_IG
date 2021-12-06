#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


ObjRevolucion::ObjRevolucion() {}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, int eje, bool tapa_sup, bool tapa_inf)
{
    ply::read_vertices(archivo, this->v);
    crearMalla(v, num_instancias, eje, tapa_sup, tapa_inf);
    mezclarCaras();
    generarColores();
    calcular_normales();
    calcular_texturas();
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)
 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, int eje, bool tapa_sup, bool tapa_inf)
{
    v = archivo;
    crearMalla(v, num_instancias, eje, tapa_sup, tapa_inf);
    mezclarCaras();
    generarColores();
    calcular_normales();
    calcular_texturas();
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, int eje, bool tapa_sup, bool tapa_inf)
{
    Tupla3f polo_norte, polo_sur;

    numero_puntos_perfil = perfil_original.size();

    this->tapa_sup = tapa_sup; this->tapa_inf = tapa_inf; numero_instancias = num_instancias;

    for (int i = 0; i < perfil_original.size(); i++) //Calcular dp usado en la funcion de calcular_textura()
    {
        dp.push_back(distancia(perfil_original[0], perfil_original[i]));
    }

    //Si el perfil está en el orden inverso al estandar, invertirlo
    if (perfil_original[0](eje) - perfil_original[perfil_original.size()-1](eje) > 0)
    {
        std::reverse(perfil_original.begin(), perfil_original.end());
    }

    //Detectar y extraer polo sur del perfil original
    if (esPolo(perfil_original[0], eje))
    {
        polo_sur = perfil_original[0];
        perfil_original.erase(perfil_original.begin());
    }
    else
    {
        polo_sur = proyectarPunto(perfil_original[0], eje);
    }
        
    //Detectar y extraer polo norte del perfil original
    if (esPolo(perfil_original[perfil_original.size()-1], eje))
    {
        polo_norte = perfil_original[perfil_original.size()-1];
        perfil_original.pop_back();
    }
    else
    {
        polo_norte = proyectarPunto(perfil_original[perfil_original.size()-1], eje);
    }

    v = perfil_original;

    //Rotacion del perfil y generación de vertices
    std::vector<Tupla3f> perfil_original_aux = perfil_original;

    for (int k = 0; k < num_instancias-1; k++) //Quitado el -1 para la P5
    {
        for (int i = 0; i < perfil_original.size(); i++)
        {
            perfil_original[i] = rotarEje(perfil_original[i], M_PI*2/num_instancias, eje);
            v.push_back(perfil_original[i]);
        } 
    }
    for (int i = 0; i < perfil_original.size(); i++)
    {
        v.push_back(v[i]);
    }

    std::cout << "Los vertices tienen que ser " << v.size() << std::endl;

    //Generacion de malla de triángulos del tronco
    for (int i = 0; i < num_instancias; i++)
    {
        for (int j = 0; j < perfil_original.size()-1; j++)
        {
            int a = perfil_original.size()*i + j,
                b = perfil_original.size()*(i+1) + j;
            
            f.push_back(Tupla3i(a, b, b+1));
            f.push_back(Tupla3i(a, b+1, a+1));
        }
    }

    int size_vertices_tronco = perfil_original.size() * num_instancias;
    size_tronco = f.size();
    int cuenta_tapas = 0;

    //Crear los triángulos de la tapa superior
    if (tapa_sup)
    {
        int v_aux = perfil_original.size()-1, v_polo;
        v_polo = v.size();
        for (int i = 0; i <= num_instancias+1; i++)
            v.push_back(polo_norte);
        
        for (int i = 0; i < num_instancias; i++)
        {
            int v_siguiente = (v_aux+perfil_original.size())%size_vertices_tronco;
            f.push_back(Tupla3i(v_aux, v_siguiente, v_polo));
            v_aux = v_siguiente;
            n_tapas[cuenta_tapas%2]++;
            cuenta_tapas++;
            v_polo++;
        }
    }

    //Crear los triángulos de la tapa inferior
    if (tapa_inf)
    {
        int v_aux = 0, v_polo;
        v_polo = v.size();
        for (int i = 0; i <= num_instancias+1; i++) //Añadido para funcionamiento de P5
            v.push_back(polo_sur);

        for (int i = 0; i < num_instancias; i++)
        {
            int v_siguiente = (v_aux+perfil_original.size())%size_vertices_tronco;
            f.push_back(Tupla3i(v_polo, v_siguiente, v_aux));
            v_aux = v_siguiente;
            n_tapas[cuenta_tapas%2]++;
            cuenta_tapas++;
            v_polo++;
        }
    }
}

void ObjRevolucion::cambiarTapas()
{
    if (visibilidad_tapas)
    {
        draw_size = draw_size - n_tapas[0] - n_tapas[1];
        draw_size_a1 -= n_tapas[0];
        draw_size_a2 -= n_tapas[1];

        visibilidad_tapas = false;
    }
    else
    {
        draw_size = f.size();
        draw_size_a1 = draw_size/2 + (draw_size%2 == 1);
        draw_size_a2 = draw_size/2;

        visibilidad_tapas = true;
    }
}

void ObjRevolucion::drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices)
{
    if (!modo_ajedrez && !visibilidad_tapas)
    {
        glDrawElements(mode, size_tronco/2*3, type, indices);
        glDrawElements(mode, size_tronco/2*3, type, indices+sizeof(int)*3*(f.size()/2+f.size()%2));
    }

    else
    {
        glDrawElements(mode, count, type, indices);
    }
}

bool ObjRevolucion::esPolo(Tupla3f p, int eje)
{
    bool salida = false;

    if (eje == 0)
        salida = (fabs(p(1)) < UMBRAL_0 && fabs(p(2)) < UMBRAL_0);
    if (eje == 1)
        salida = (fabs(p(0)) < UMBRAL_0 && fabs(p(2)) < UMBRAL_0);
    if (eje == 2)
        salida = (fabs(p(0)) < UMBRAL_0 && fabs(p(1)) < UMBRAL_0);
    
    return salida;
}

Tupla3f ObjRevolucion::rotarEjeX(Tupla3f p, float radianes)
{
   Tupla3f salida;

   salida(0) = p(0);
   salida(1) = cos(radianes)*p(1) - sin(radianes)*p(2);
   salida(2) = sin(radianes)*p(1) + cos(radianes)*p(2);

   return salida;
}

Tupla3f ObjRevolucion::rotarEjeY(Tupla3f p, float radianes)
{
   Tupla3f salida;

   salida(0) = cos(radianes)*p(0) + sin(radianes)*p(2);
   salida(1) = p(1);
   salida(2) = -sin(radianes)*p(0) + cos(radianes)*p(2);

   return salida;
}

Tupla3f ObjRevolucion::rotarEjeZ(Tupla3f p, float radianes)
{
   Tupla3f salida;

   salida(0) = cos(radianes)*p(0) - sin(radianes)*p(1);
   salida(1) = sin(radianes)*p(0) + cos(radianes)*p(1);
   salida(2) = p(2);

   return salida;
}

Tupla3f ObjRevolucion::rotarEje(Tupla3f punto, float radianes, int eje)
{
   Tupla3f salida;

   if (eje == 0)
      salida = rotarEjeX(punto, radianes);
   else if (eje == 1)
      salida = rotarEjeY(punto, radianes);
   else if (eje == 2)
      salida = rotarEjeZ(punto, radianes);
   
   return salida;
}

float ObjRevolucion::distancia(Tupla3f p1, Tupla3f p2)
{
    return sqrt( (p1(0)-p2(0))*(p1(0)-p2(0)) + (p1(1)-p2(1))*(p1(1)-p2(1)) + (p1(2)-p2(2))*(p1(2)-p2(2)) );
}

void ObjRevolucion::calcular_texturas()
{
    int tam_perfil_sin_polos = numero_puntos_perfil - tapa_sup - tapa_inf;
    int tam_v_tronco = tam_perfil_sin_polos*(numero_instancias+1);

    /*std::cout << "numero_puntos_perfil = " << numero_puntos_perfil << std::endl;
    std::cout << "tamano_perfil_sin_polos = " << tam_perfil_sin_polos << std::endl;
    std::cout << "tam_v_tronco = " << tam_v_tronco << std::endl;
    std::cout << "tam_v = " << v.size() << std::endl;
    std::cout << "tam_v NORMAL = " << numero_instancias*numero_puntos_perfil << std::endl;*/

    std::cout << "-------el perfil es " << numero_puntos_perfil << std::endl;
    std::cout << "-------el perfil sin polos es " << tam_perfil_sin_polos << std::endl;
    std::cout << "-------numero de instancias es " << numero_instancias << std::endl;
    std::cout << "-------v_tronco es " << tam_v_tronco << std::endl;


   for (int i = 0; i <= numero_instancias; i++)
    {
        float si = float(i)/numero_instancias;
        //std::cout << "si a = " << si << std::endl;

        for (int j = 0; j < tam_perfil_sin_polos; j++)
        {
            ct.push_back(Tupla2f(si, dp[j]/dp[dp.size()-1] )); 
            //std::cout << "(" << si << ", " << dp[j]/dp[dp.size()-1] << ")" << std::endl;
        }
    }

    std::cout << "Los vertices han sido " << ct.size() << std::endl;

    std::cout << "HOLAAAAAAAAA"<< std::endl;
    std::cout << "ct = " << ct.size() << std::endl;
    std::cout << "v = " << v.size() << std::endl;
    std::cout << "HOLAAAAAAAAA"<< std::endl;

    for (int k = 0; k < numero_instancias && tapa_sup; k++)
    {
        float si = float(k)/numero_instancias;
        ct.push_back(Tupla2f(si, 1));

        //std::cout << "ct b = " << si << std::endl;
    }

    for (int k = 0; k < numero_instancias && tapa_inf; k++)
    {
        float si = float(k)/numero_instancias;
        ct.push_back(Tupla2f(si, 0));

        //std::cout << "si c " << si << std::endl;
    }

    std::cout << "ADIOOOS"<< std::endl;
    std::cout << "ct = " << ct.size() << std::endl;
    std::cout << "v = " << v.size() << std::endl;
    std::cout << "ADIOOOS"<< std::endl;
}