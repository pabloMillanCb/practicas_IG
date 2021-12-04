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
    posicion = {0, 0, 1, 0};

    posicion(1) = cos(alpha)*posicion(1) - sin(alpha)*posicion(2);
    posicion(2) = sin(alpha)*posicion(1) + cos(alpha)*posicion(2);

    posicion(0) = cos(beta)*posicion(0) + sin(beta)*posicion(2);
    posicion(2) = -sin(beta)*posicion(0) + cos(beta)*posicion(2);
} 