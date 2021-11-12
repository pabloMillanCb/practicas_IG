#include "luzposicional.h"
#include "aux.h"

LuzPosicional::LuzPosicional(const Tupla3f & orientacion) 
{
    posicion = Tupla4f(orientacion(0), orientacion(1), orientacion(2), 1.0);
}