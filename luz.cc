#include "luz.h"
#include <iostream>

void Luz::activar()
{
    if (!activada)
    {
        glEnable(id);

        glLightfv( id, GL_SPECULAR, blanco ) ;
        glLightfv( id, GL_DIFFUSE, colorDifuso ) ;
        glLightfv( id, GL_AMBIENT, colorAmbiente ) ;
        
        //glPushMatrix();
        //glLoadIdentity();
        glLightfv( id, GL_POSITION, posicion);
        //glPopMatrix();
        
        activada = true;
        std::cout << "Luz activada con ID " << id << std::endl;
    }
    else
    {
        glDisable(id);
        activada = false;
    }
}

void Luz::set_id(GLenum id_)
{
    id = id_;
}