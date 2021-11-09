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
    this->tapa_sup = tapa_sup; this->tapa_inf = tapa_inf; numero_instancias = num_instancias;
    ply::read_vertices(archivo, this->v);
    crearMalla(v, num_instancias, eje, tapa_sup, tapa_inf);
    mezclarCaras();
    generarColores();
    
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)
 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, int eje, bool tapa_sup, bool tapa_inf)
{
    this->tapa_sup = tapa_sup; this->tapa_inf = tapa_inf; numero_instancias = num_instancias;
    v = archivo;
    crearMalla(v, num_instancias, eje, tapa_sup, tapa_inf);
    mezclarCaras();
    generarColores();
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, int eje, bool tapa_sup, bool tapa_inf)
{
    Tupla3f polo_norte, polo_sur;

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
        perfil_original.erase(perfil_original.end()-1);
    }
    else
    {
        polo_norte = proyectarPunto(perfil_original[perfil_original.size()-1], eje);
    }

    v = perfil_original;

    //Rotacion del perfil y generación de vertices
    for (int k = 0; k < num_instancias-1; k++)
    {
        for (int i = 0; i < perfil_original.size(); i++)
        {
            perfil_original[i] = rotarEje(perfil_original[i], M_PI*2/num_instancias, eje);
            v.push_back(perfil_original[i]);
        } 
    }

    //Generacion de malla de triángulos del tronco
    for (int i = 0; i < num_instancias; i++)
    {
        for (int j = 0; j < perfil_original.size()-1; j++)
        {
            int a = i*perfil_original.size() + j,
                b =  perfil_original.size()*((i+1)%num_instancias) + j;
            
            f.push_back(Tupla3i(a, b, b+1));
            f.push_back(Tupla3i(a, b+1, a+1));
        }
    }

    int size_vertices_tronco = v.size();
    size_tronco = f.size();
    int cuenta_tapas = 0;

    //Crear los triángulos de la tapa superior
    if (tapa_sup)
    {
        int v_aux = perfil_original.size()-1, v_polo;
        v.push_back(polo_norte);
        v_polo = v.size()-1;
        
        for (int i = 0; i < num_instancias; i++)
        {
            int v_siguiente = (v_aux+perfil_original.size())%size_vertices_tronco;
            f.push_back(Tupla3i(v_aux, v_siguiente, v_polo));
            v_aux = v_siguiente;
            n_tapas[cuenta_tapas%2]++;
            cuenta_tapas++;
        }
    }

    //Crear los triángulos de la tapa inferior
    if (tapa_inf)
    {
        int v_aux = 0, v_polo;
        v.push_back(polo_sur);
        v_polo = v.size()-1;

        for (int i = 0; i < num_instancias; i++)
        {
            int v_siguiente = (v_aux+perfil_original.size())%size_vertices_tronco;
            f.push_back(Tupla3i(v_polo, v_siguiente, v_aux));
            v_aux = v_siguiente;
            n_tapas[cuenta_tapas%2]++;
            cuenta_tapas++;
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
        salida = (abs(p(1)) < UMBRAL_0 && abs(p(2)) < UMBRAL_0);
    if (eje == 1)
        salida = (abs(p(0)) < UMBRAL_0 && abs(p(2)) < UMBRAL_0);
    if (eje == 2)
        salida = (abs(p(0)) < UMBRAL_0 && abs(p(1)) < UMBRAL_0);
    
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