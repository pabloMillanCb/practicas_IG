#include "luz.h"
#include <iostream>

void Luz::activar()
{
    glLightfv( id, GL_SPECULAR, blanco ) ;
    glLightfv( id, GL_DIFFUSE, colorDifuso ) ;
    glLightfv( id, GL_AMBIENT, colorAmbiente ) ;   
    glLightfv( id, GL_POSITION, posicion);
}

void Luz::encender()
{
    if (!glIsEnabled(id))
        glEnable(id);
    else
        glDisable(id);
}

void Luz::set_id(GLenum id_)
{
    id = id_;
}