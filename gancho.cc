#include "gancho.h"
#include <iostream>

Gancho::Gancho()
{
    foco = new Cilindro(10, 10, 25, 10);
    lentes = new Cilindro(10, 10, 25, 8);
    cable = new Cilindro(10, 10, 80, 2);

    antenaCono = new Cono(30, 5, 15, 20, false);
    antenaCilindro = new Cilindro(5, 5, 10, 1);
    antenaEsfera = new Esfera(30, 30, 3);

    Material negro({0.18275, 0.17, 0.22525, 0.82}, {0.332741, 0.328634, 0.346435, 0.82}, {0.05375, 0.05, 0.06625, 0.82}, 100);
    Material gris({0.2775, 0.2775, 0.2775, 1.0}, {0.773911, 0.773911, 0.773911, 1.0}, {0.23125, 0.23125, 0.23125, 1.0}, 100);
    Material azul({0.4, 0.5, 0.4, 1.0}, {1.0, 1.0, 1.0, 1.0}, {0.0, 0.05, 0.0, 1.0}, 100);
    Material dorado({0.780392, 0.568627, 0.113725, 1.0}, {0.992157, 0.941176, 0.807843, 1.0}, {0.329412, 0.223529, 0.027451, 1.0}, 100);

    foco->setMaterial(gris);
    cable->setMaterial(negro);
    lentes->setMaterial(azul);

    antenaEsfera->setMaterial(dorado);
    antenaCilindro->setMaterial(gris);
    antenaCono->setMaterial(gris);

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
        glTranslatef(0.0, -15, 0.0);
        antenaCono->draw();
    glPopMatrix();

    glPushMatrix();
        //glTranslatef(0.0, -0.0, 0.0);
        glRotatef(r_y, 0, 1, 0);
        glRotatef(r_x, 1, 0, 0);
        glTranslatef(0.0, -15, 0.0);
        antenaCilindro->draw();
    glPopMatrix();

    glPushMatrix();
        //glTranslatef(0.0, -0.0, 0.0);
        glRotatef(r_y, 0, 1, 0);
        glRotatef(r_x, 1, 0, 0);
        glTranslatef(0.0, -18, 0.0);
        antenaEsfera->draw();
    glPopMatrix();

    /*glPushMatrix();
        //glTranslatef(0.0, -0.0, 0.0);
        glRotatef(r_y, 0, 1, 0);
        glRotatef(r_x, 1, 0, 0);
        glTranslatef(10.0, -12.5, 0.0);
        foco->draw();
    glPopMatrix();

    glPushMatrix();
        //glTranslatef(0.0, -0.0, 0.0);
        glRotatef(r_y, 0, 1, 0);
        glRotatef(r_x, 1, 0, 0);
        glTranslatef(-10.0, -12.5, 0.0);
        foco->draw();
    glPopMatrix();

    glPushMatrix();
        //glTranslatef(0.0, -0.0, 0.0);
        glRotatef(r_y, 0, 1, 0);
        glRotatef(r_x, 1, 0, 0);
        glTranslatef(10.0, -11.5, 0.0);
        lentes->draw();
    glPopMatrix();

    glPushMatrix();
        //glTranslatef(0.0, -0.0, 0.0);
        glRotatef(r_y, 0, 1, 0);
        glRotatef(r_x, 1, 0, 0);
        glTranslatef(-10.0, -11.5, 0.0);
        lentes->draw();
    glPopMatrix();*/
}
void Gancho::aumentar_foco_x(float aumento)
{
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
