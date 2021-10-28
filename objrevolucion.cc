#include "aux.h"
#include "objrevolucion.h"




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf)
{
    this->tapa_sup = tapa_sup; this->tapa_inf = tapa_inf; numero_instancias = num_instancias;
    ply::read_vertices(archivo, this->v);
    crearMalla(v, num_instancias, tapa_sup, tapa_inf);
    generarColores();
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf)
{
    this->tapa_sup = tapa_sup; this->tapa_inf = tapa_inf; numero_instancias = num_instancias;
    v = archivo;
    crearMalla(v, num_instancias, tapa_sup, tapa_inf);
    generarColores();
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf)
{

    if (perfil_original[0](1) - perfil_original[perfil_original.size()-1](1) > 0)
    {
        std::reverse(perfil_original.begin(), perfil_original.end());
        std::cout << "Reverse\n";
    }

    Tupla3f polo_norte, polo_sur;

    if (esPolo(perfil_original[0])) //Detectar y etraer polo sur
    {
        polo_sur = perfil_original[0];
        perfil_original.erase(perfil_original.begin());
    }
    else
    {
        polo_sur = proyectarPunto(perfil_original[0]);
    }
        

    if (esPolo(perfil_original[perfil_original.size()-1])) //Detectar y extraer polo norte
    {
        polo_norte = perfil_original[perfil_original.size()-1];
        perfil_original.erase(perfil_original.end()-1);
    }
    else
    {
        polo_norte = proyectarPunto(perfil_original[perfil_original.size()-1]);
    }

    v = perfil_original;

    for (int k = 0; k < num_instancias-1; k++) //Rotacion del perfil y generación de vertices
    {
        for (int i = 0; i < perfil_original.size(); i++)
        {
            perfil_original[i] = rotarEjeY(perfil_original[i], M_PI*2/num_instancias);
            v.push_back(perfil_original[i]);
        } 
    }

    for (int i = 0; i < num_instancias; i++) //Generacion de triangulos del tronco
    {
        for (int j = 0; j < perfil_original.size()-1; j++)
        {
            int a = i*perfil_original.size() + j,
                b =  perfil_original.size()*((i+1)%num_instancias) + j;
            
            f.push_back(Tupla3i(a, b, b+1));
            f.push_back(Tupla3i(a, b+1, a+1));
        }
    }
    std::cout<<std::endl;

    int size_tronco = v.size();
    this->size_tronco = size_tronco;

    int cuenta_tapas = 0;

    if (tapa_sup) //crear tapa superior
    {
        int v_aux = perfil_original.size()-1, v_polo;
        v.push_back(polo_norte);
        v_polo = v.size()-1;
        
        for (int i = 0; i < num_instancias; i++)
        {
            int v_siguiente = (v_aux+perfil_original.size())%size_tronco;
            f.push_back(Tupla3i(v_aux, v_siguiente, v_polo));
            v_aux = v_siguiente;
            n_tapas[cuenta_tapas%2]++;
            cuenta_tapas++;
        }
    }

    if (tapa_inf) //crear tapa inferior
    {
        int v_aux = 0, v_polo;
        v.push_back(polo_sur);
        v_polo = v.size()-1;

        for (int i = 0; i < num_instancias; i++)
        {
            int v_siguiente = (v_aux+perfil_original.size())%size_tronco;
            f.push_back(Tupla3i(v_polo, v_siguiente, v_aux));
            v_aux = v_siguiente;
            n_tapas[cuenta_tapas%2]++;
            cuenta_tapas++;
        }
        std::cout<<std::endl;
    }

    for (int i = 0; i < f.size(); i+=2) //Crear triangulos modo ajedrez
        f1.push_back(f[i]);
    for (int i = 1; i < f.size(); i+=2)
        f2.push_back(f[i]);
    
}

void ObjRevolucion::cambiarTapas()
{
    if (visibilidad_tapas)
    {
        visibilidad_tapas = !visibilidad_tapas;
        int tamanio = f.size();
        int k = 0;

        if (tapa_sup)
            k++;
        if (tapa_inf)
            k++;

        int num_tapas = numero_instancias*k;

        for (int i = tamanio-numero_instancias*k; i < tamanio; i++)
        {
            f_tmp.push_back(f[i]);
        }

        for (int i = tamanio-numero_instancias*k; i < tamanio; i++)
        {
            f.pop_back();
        }

        for (int i = 0; i < n_tapas[0]; i++)
        {
            f1_tmp.push_back(f1.back());
            f1.pop_back();
        }

        for (int i = 0; i < n_tapas[1]; i++)
        {
            f2_tmp.push_back(f2.back());
            f2.pop_back();
        }

    }

    else
    {
        visibilidad_tapas = !visibilidad_tapas;

        for (int i = 0; i < f_tmp.size(); i++)
        {
            f.push_back(f_tmp[i]);
        }

        for (int i = 0; i < f1_tmp.size(); i++)
        {
            f1.push_back(f1_tmp[i]);
        }

        for (int i = 0; i < f2_tmp.size(); i++)
        {
            f2.push_back(f2_tmp[i]);
        }

        f_tmp.clear();
        f1_tmp.clear();
        f2_tmp.clear();
    }
}