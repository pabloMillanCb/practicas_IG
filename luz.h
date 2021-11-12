#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz
{
protected:
    Tupla4f posicion;
    GLenum id;
    Tupla4f colorAmbiente;
    Tupla4f colorDifuso;
    bool activada = false;
public:
    void activar();
};

#endif