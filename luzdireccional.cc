#include "luzdireccional.h"
#include "aux.h"

LuzDireccional::LuzDireccional(const Tupla2f & orientacion, Tupla4f ambiente, Tupla4f difuso) 
{
    alpha = orientacion(0);
    beta = orientacion(1);
    posicion = Tupla4f(alpha, 0.0, beta, 0.0);
    colorAmbiente = ambiente;
    colorDifuso = difuso;
}

void LuzDireccional::variarAnguloAlpha( float incremento)
{
    alpha += incremento;
}

void LuzDireccional::variarAnguloBeta( float incremento)
{
    beta += incremento;
}