#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"

class Material
{
    protected:
        Tupla4f difuso;
        Tupla4f especular;
        Tupla4f ambiente;
        float brillo;
    public:
        Material();
        Material(Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float mbrillo);
        void aplicar();
        void operator=(Material &m);
   
} ;


#endif
