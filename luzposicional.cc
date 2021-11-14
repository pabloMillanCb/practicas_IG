#include "luzposicional.h"
#include "aux.h"
#include <iostream>

LuzPosicional::LuzPosicional(const Tupla3f & orientacion, Tupla4f ambiente, Tupla4f difuso) 
{
    posicion = Tupla4f(orientacion(0), orientacion(1), orientacion(2), 1.0);
    colorAmbiente = ambiente;
    colorDifuso = difuso;
}

void LuzPosicional::Colocar(const Tupla3f & orientacion)
{
    posicion = Tupla4f(orientacion(0), orientacion(1), orientacion(2), 1.0);
    glLightfv( id, GL_POSITION, posicion );
}


int LuzPosicional::get(int i)
{
    return posicion(i);
}