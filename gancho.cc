#include "gancho.h"
#include <iostream>

Gancho::Gancho()
{
    lentes = new Cilindro(10, 10, 25, 8);
    cable = new Cilindro(10, 10, 80, 2);

    antenaCono = new Cono(30, 5, 15, 20, false);
    antenaConoR = new Cono(30, 5, 15, 20, false);
    antenaCilindro = new Cilindro(5, 5, 10, 1);
    antenaEsfera = new Esfera(30, 30, 3);

    antenaConoR->invertir_caras();

    Material negro({0.18275, 0.17, 0.22525, 0.82}, {0.332741, 0.328634, 0.346435, 0.82}, {0.05375, 0.05, 0.06625, 0.82}, 100);
    Material gris({0.2775, 0.2775, 0.2775, 1.0}, {0.773911, 0.773911, 0.773911, 1.0}, {0.23125, 0.23125, 0.23125, 1.0}, 100);
    Material azul({0.4, 0.5, 0.4, 1.0}, {1.0, 1.0, 1.0, 1.0}, {0.0, 0.05, 0.0, 1.0}, 100);
    Material dorado({0.780392, 0.568627, 0.113725, 1.0}, {0.992157, 0.941176, 0.807843, 1.0}, {0.329412, 0.223529, 0.027451, 1.0}, 100);

    cable->setMaterial(negro);
    lentes->setMaterial(azul);

    antenaEsfera->setMaterial(dorado);
    antenaCilindro->setMaterial(gris);
    antenaCono->setMaterial(gris);
    antenaConoR->setMaterial(gris);

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
        antenaConoR->draw();
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
    cable->cambiar_solido();
    antenaCono->cambiar_solido();
    antenaConoR->cambiar_solido();
    antenaCilindro->cambiar_solido();
    antenaEsfera->cambiar_solido();
}
void Gancho::cambiar_lineas()
{
    cable->cambiar_lineas();
    antenaCono->cambiar_lineas();
    antenaConoR->cambiar_lineas();
    antenaCilindro->cambiar_lineas();
    antenaEsfera->cambiar_lineas();
}
void Gancho::cambiar_puntos()
{
    cable->cambiar_puntos();
    antenaCono->cambiar_puntos();
    antenaConoR->cambiar_puntos();
    antenaCilindro->cambiar_puntos();
    antenaEsfera->cambiar_puntos();
}
void Gancho::cambiar_ajedrez()
{
    cable->cambiar_ajedrez();
    antenaCono->cambiar_ajedrez();
    antenaConoR->cambiar_ajedrez();
    antenaCilindro->cambiar_ajedrez();
    antenaEsfera->cambiar_ajedrez();
}

void Gancho::activar_inmediato()
{
    cable->activar_inmediato();
    antenaCono->activar_inmediato();
    antenaConoR->activar_inmediato();
    antenaCilindro->activar_inmediato();
    antenaEsfera->activar_inmediato();
}

void Gancho::activar_diferido()
{
    cable->activar_diferido();
    antenaCono->activar_diferido();
    antenaConoR->activar_diferido();
    antenaCilindro->activar_diferido();
    antenaEsfera->activar_diferido();
}
