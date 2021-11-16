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

    Tupla4f blanco = {1.0, 1.0, 1.0, 1.0};
public:
    void activar();
    void encender();
    void set_id(GLenum id_);
};

#endif