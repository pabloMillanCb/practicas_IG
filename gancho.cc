#include "gancho.h"
#include <iostream>

Gancho::Gancho()
{
    foco = new Cilindro(10, 10, 25, 10);
    cable = new Cilindro(10, 10, 80, 2);

    Material negro({0.18275, 0.17, 0.22525, 0.82}, {0.332741, 0.328634, 0.346435, 0.82}, {0.05375, 0.05, 0.06625, 0.82}, 100);
    Material gris({0.2775, 0.2775, 0.2775, 1.0}, {0.773911, 0.773911, 0.773911, 1.0}, {0.23125, 0.23125, 0.23125, 1.0}, 100);

    foco->setMaterial(gris);
    cable->setMaterial(negro);

}
void Gancho::draw()
{
    glPushMatrix();
        //glTranslatef(0.0, -50.0, 0.0);
        cable->draw();
    glPopMatrix();

    glPushMatrix();
        //glTranslatef(0.0, -0.0, 0.0);
        glRotatef(r_y, 0, 1, 0);
        glRotatef(r_x, 1, 0, 0);
        glTranslatef(0.0, -12.5, 0.0);
        foco->draw();
    glPopMatrix();
}
void Gancho::aumentar_foco_x(float aumento)
{
    std::cout << "eeyyy\n";

    r_x += aumento;

    if (aumento + r_x > r_max)
        r_x = r_max;
    else if (aumento + r_x < r_min)
        r_x = r_min;
}
void Gancho::aumentar_foco_y(float aumento)
{
    r_y += aumento;
}

void Gancho::cambiar_solido()
{
    foco->cambiar_solido();
    cable->cambiar_solido();
}
void Gancho::cambiar_lineas()
{
    foco->cambiar_lineas();
    cable->cambiar_lineas();
}
void Gancho::cambiar_puntos()
{
    foco->cambiar_puntos();
    cable->cambiar_puntos();
}
void Gancho::cambiar_ajedrez()
{
    foco->cambiar_ajedrez();
    cable->cambiar_ajedrez();
}

void Gancho::activar_inmediato()
{
    foco->activar_inmediato();
    cable->activar_inmediato();
}

void Gancho::activar_diferido()
{
    foco->activar_diferido();
    cable->activar_diferido();
}