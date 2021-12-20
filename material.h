#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"

class Material
{
    protected:
        Tupla4f difuso;
        Tupla4f especular;
        Tupla4f ambiente;

        Tupla4f difuso_s = {0.5f,0.5f,0.0f,1.0f };
        Tupla4f especular_s = {0.0f,0.0f,0.0f,1.0f };
        Tupla4f ambiente_s = {0.60f,0.60f,0.50f,1.0f };

        Tupla4f difuso_s2 = { 0.780392f, 0.568627f, 0.113725f, 1.0f };
        Tupla4f especular_s2 = { 0.992157f, 0.941176f, 0.807843f, 1.0f };
        Tupla4f ambiente_s2 = { 0.329412f, 0.223529f, 0.027451f,1.0f };

        float brillo;
        
    public:
        Material();
        Material(Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float mbrillo);
        void aplicar();
        void aplicar_seleccion();
        void aplicar_seleccion2();
        void operator=(Material &m);
        void aumentar_brillo(float f);
   
} ;


#endif
