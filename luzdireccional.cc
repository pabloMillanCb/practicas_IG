#include "luzdireccional.h"
#include "aux.h"

LuzDireccional::LuzDireccional(const Tupla2f & orientacion, Tupla4f ambiente, Tupla4f difuso) 
{
    alpha = orientacion(0);
    beta = orientacion(1);
    aplicarRotaciones();
    colorAmbiente = ambiente;
    colorDifuso = difuso;
}

void LuzDireccional::variarAnguloAlpha( float incremento)
{
    alpha += incremento;
    aplicarRotaciones();
}

void LuzDireccional::variarAnguloBeta( float incremento)
{
    beta += incremento;
    aplicarRotaciones();
}

void LuzDireccional::aplicarRotaciones()
{
    posicion(0) = sin(alpha)*cos(beta);
    posicion(1) = sin(alpha)*sin(beta);
    posicion(2) = cos(alpha);
    posicion(3) = 0;
} 