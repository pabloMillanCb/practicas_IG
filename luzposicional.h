#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

class LuzPosicional : public Luz
{
    public:
        LuzPosicional(const Tupla3f & posicion, Tupla4f ambiente, Tupla4f difuso) ;
        void Colocar(const Tupla3f & orientacion);

        int get(int i);
};

#endif