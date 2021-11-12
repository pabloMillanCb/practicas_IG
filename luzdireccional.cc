#include "luzdireccional.h"
#include "aux.h"

LuzDireccional::LuzDireccional(const Tupla2f & orientacion) 
{
    alpha = orientacion(0);
    beta = orientacion(1);
    posicion = Tupla4f(0.0, 0.0, 0.0, 0.0);
}

void LuzDireccional::variarAnguloAlpha( float incremento)
{
    alpha += incremento;
}

void LuzDireccional::variarAnguloBeta( float incremento)
{
    beta += incremento;
}