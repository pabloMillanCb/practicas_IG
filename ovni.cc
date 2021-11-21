#include "ovni.h"
#include <iostream>

Ovni::Ovni()
{
    cabina = new Esfera(30, 30, 30);
    cuerpo = new Cono(30, 30, 70, 100);

    Material cab({0.4, 0.5, 0.4, 1.0}, {0.7, 0.04, 0.04, 1.0}, {0.0, 0.05, 0.0, 1.0}, 100);
    Material cue({0.2775, 0.2775, 0.2775, 1.0}, {0.773911, 0.773911, 0.773911, 1.0}, {0.23125, 0.23125, 0.23125, 1.0}, 100);

    cabina->setMaterial( cab );
    cuerpo->setMaterial( cue );

}

void Ovni::draw()
{

    cuerpo->draw();
    Esfera hola(39, 30, 30);
    //hola.draw();

    glPushMatrix();
        glTranslatef(0, 50, 0);
        cabina->draw();
    glPopMatrix();

    glPushMatrix();
        glRotatef(r_luces, 0, 1, 0);
        luces.draw();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, -h_gancho, 0);
        inferior.draw();
    glPopMatrix();
}

void Ovni::aumentar_r_luces(float aumento)
{
    r_luces += aumento;
}

void Ovni::aumentar_foco_x(float aumento)
{
    inferior.aumentar_foco_x(aumento);
}

void Ovni::aumentar_foco_y(float aumento)
{
    inferior.aumentar_foco_y(aumento);
}

void Ovni::aumentar_h_gancho(float aumento)
{
    h_gancho += aumento;

    if (aumento + h_gancho > max_h_gancho)
        h_gancho = max_h_gancho;
    else if (aumento + h_gancho < min_h_gancho)
        h_gancho = min_h_gancho;

}

void Ovni::gradosLibertad(int i, float aumento)
{
    switch(i){
        case 0:
            aumentar_r_luces(aumento);
        break;

        case 1:
            aumentar_foco_y(aumento);
        break;

        case 2:
            aumentar_h_gancho(aumento);
        break;

        case 3:
            aumentar_foco_x(aumento);
        break;
    }
}

void Ovni::cambiar_solido()
{
    cabina->cambiar_solido();
    cuerpo->cambiar_solido();
    luces.cambiar_solido();
    inferior.cambiar_solido();
}
void Ovni::cambiar_lineas()
{
    cabina->cambiar_lineas();
    cuerpo->cambiar_lineas();
    luces.cambiar_lineas();
    inferior.cambiar_lineas();
}
void Ovni::cambiar_puntos()
{
    cabina->cambiar_puntos();
    cuerpo->cambiar_puntos();
    luces.cambiar_puntos();
    inferior.cambiar_puntos();
}
void Ovni::cambiar_ajedrez()
{
    cabina->cambiar_ajedrez();
    cuerpo->cambiar_ajedrez();
    luces.cambiar_ajedrez();
    inferior.cambiar_ajedrez();
}

void Ovni::activar_inmediato()
{
    cabina->activar_inmediato();
    cuerpo->activar_inmediato();
    luces.activar_inmediato();
    inferior.activar_inmediato();
}
void Ovni::activar_diferido()
{
    cabina->activar_diferido();
    cuerpo->activar_diferido();
    luces.activar_diferido();
    inferior.activar_diferido();
}
