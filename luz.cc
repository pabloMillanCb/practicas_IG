#include "luz.h"

void Luz::activar()
{
    if (!activada)
    {
        glEnable(id);
        activada = true;
    }
    else
    {
        glDisable(id);
        activada = false;
    }
}