#include "luz.h"
#include <iostream>

void Luz::activar()
{
    glEnable(id);

    glLightfv( id, GL_SPECULAR, blanco ) ;
    glLightfv( id, GL_DIFFUSE, colorDifuso ) ;
    glLightfv( id, GL_AMBIENT, colorAmbiente ) ;
    
    //glPushMatrix();
    //glLoadIdentity();
    glLightfv( id, GL_POSITION, posicion);
    //glPopMatrix();
}

void Luz::set_id(GLenum id_)
{
    id = id_;
}