#include "ovni.h"
#include <iostream>

Ovni::Ovni()
{
    //Ovni

    cabina = new Esfera(30, 30, 30); objetos.push_back(cabina);
    cuerpo = new Cono(30, 30, 70, 100, true); objetos.push_back(cuerpo);
    abductor = new Cono(10, 10, 30, 20, false); objetos.push_back(abductor);
    abductorR = new Cono(10, 10, 30, 20, false); objetos.push_back(abductorR);

    abductorR->invertir_caras();

    Material gris({0.4, 0.5, 0.4, 1.0}, {1.0, 1.0, 1.0, 1.0}, {0.0, 0.05, 0.0, 1.0}, 100);
    Material negro({0.2775, 0.2775, 0.2775, 1.0}, {0.773911, 0.773911, 0.773911, 1.0}, {0.23125, 0.23125, 0.23125, 1.0}, 100);

    cabina->setMaterial( gris );
    cuerpo->setMaterial( negro );
    abductor->setMaterial( negro );
    abductorR->setMaterial( negro );

    //LucesOvni

    bola = new Esfera(12, 12, 12); objetos.push_back(bola);
    Material dorado({0.780392, 0.568627, 0.113725, 1.0}, {0.992157, 0.941176, 0.807843, 1.0}, {0.329412, 0.223529, 0.027451, 1.0}, 100);
    bola -> setMaterial(dorado);

    //Laboon

    ballena = new ObjPLY("./plys/laboon.ply"); objetos.push_back(ballena);
    sombrero = new ObjPLY("./plys/sombrero.ply"); objetos.push_back(sombrero);
    Material azul({0.427451, 0.470588, 0.541176, 1.0}, {0.333333, 0.333333, 0.521569, 1.0}, {0.105882, 0.058824, 0.113725, 1.0}, 100);
    sombrero->setMaterial(dorado);
    ballena->setMaterial(azul);

    //Gancho

    lentes = new Cilindro(10, 10, 25, 8); objetos.push_back(lentes);
    cable = new Cilindro(10, 10, 80, 2); objetos.push_back(cable);
    antenaCono = new Cono(30, 5, 15, 20, false); objetos.push_back(antenaCono);
    antenaConoR = new Cono(30, 5, 15, 20, false); objetos.push_back(antenaConoR);
    antenaCilindro = new Cilindro(5, 5, 10, 1); objetos.push_back(antenaCilindro);
    antenaEsfera = new Esfera(30, 30, 3); objetos.push_back(antenaEsfera);

    antenaConoR->invertir_caras();
    cable->setMaterial(negro);
    lentes->setMaterial(azul);
    antenaEsfera->setMaterial(dorado);
    antenaCilindro->setMaterial(gris);
    antenaCono->setMaterial(gris);
    antenaConoR->setMaterial(gris);

    luces = new LucesOvni(bola);
    inferior = new Gancho(lentes, cable, antenaCono, antenaConoR, antenaCilindro, antenaEsfera);
    laboon = new Laboon(ballena, sombrero);
}

void Ovni::draw()
{
    cuerpo->draw();

    glPushMatrix();
        glTranslatef(0, 50, 0);
        cabina->draw();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, -10, 0);
        abductor->draw();
        abductorR->draw();
    glPopMatrix();

    glPushMatrix();
        glRotatef(r_luces, 0, 1, 0);
        luces->draw();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, h_gancho+80, 0);
        glRotatef(180, 1, 0, 0);
        inferior->draw();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, -h_ballena_max*ctr_ballena/ctr_ballena_max, 0.0);
        glScalef(escalado_max*ctr_ballena/ctr_ballena_max, escalado_max*ctr_ballena/ctr_ballena_max, escalado_max*ctr_ballena/ctr_ballena_max);
        glRotatef(y_ballena, 0, 1, 0);
        glRotatef(x_ballena, 0, 0, 1);
        glRotatef(-10, 1, 0, 0);
        laboon->draw();
    glPopMatrix();
}

void Ovni::aumentar_r_luces(float aumento)
{
    r_luces += aumento;
}

void Ovni::aumentar_foco_x(float aumento)
{
    inferior->aumentar_foco_x(aumento);
}

void Ovni::aumentar_foco_y(float aumento)
{
    inferior->aumentar_foco_y(aumento);
}

void Ovni::aumentar_h_gancho(float aumento)
{
    h_gancho += aumento;

    if (aumento + h_gancho > max_h_gancho)
        h_gancho = max_h_gancho;
    else if (aumento + h_gancho < min_h_gancho)
        h_gancho = min_h_gancho;
}

void Ovni::aumentar_ballena(float aumento)
{
    ctr_ballena += aumento;

    if (ctr_ballena > ctr_ballena_max)
        ctr_ballena = ctr_ballena_max;
    else if (ctr_ballena < 0)
        ctr_ballena = 0;
}

void Ovni::aumentar_ballena_x(float aumento)
{
    x_ballena += aumento;

    if (x_ballena > x_ballena_max)
        x_ballena = x_ballena_max;
    else if (x_ballena < -x_ballena_max)
        x_ballena = -x_ballena_max;
}

void Ovni::aumentar_ballena_y(float aumento)
{
    y_ballena += aumento;
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

        case 4:
            aumentar_ballena(aumento);
        break;

        case 5:
            aumentar_ballena_x(aumento);
        break;

        case 6:
            aumentar_ballena_y(aumento);
        break;
    }
}

void Ovni::cambiar_solido()
{
    for (int i = 0; i < objetos.size(); i++)
        objetos[i]->cambiar_solido();
}

void Ovni::cambiar_lineas()
{
    for (int i = 0; i < objetos.size(); i++)
        objetos[i]->cambiar_lineas();
}

void Ovni::cambiar_puntos()
{
    for (int i = 0; i < objetos.size(); i++)
        objetos[i]->cambiar_puntos();
}

void Ovni::cambiar_ajedrez()
{
    for (int i = 0; i < objetos.size(); i++)
        objetos[i]->cambiar_ajedrez();
}

void Ovni::activar_inmediato()
{
    for (int i = 0; i < objetos.size(); i++)
        objetos[i]->activar_inmediato();
}

void Ovni::activar_diferido()
{
    for (int i = 0; i < objetos.size(); i++)
        objetos[i]->activar_diferido();
}

void Ovni::activar_seleccion()
{
    for (int i = 0; i < objetos.size(); i++)
        objetos[i]->activar_seleccion();
}

void Ovni::desactivar_seleccion()
{
    for (int i = 0; i < objetos.size(); i++)
        objetos[i]->desactivar_seleccion();
}

void Ovni::setColorSeleccion(Tupla3f c)
{
   for (int i = 0; i < objetos.size(); i++)
        objetos[i]->setColorSeleccion(c);
}

void Ovni::activar_lock()
{
    for (int i = 0; i < objetos.size(); i++)
        objetos[i]->activar_lock();
}

void Ovni::desactivar_lock()
{
    for (int i = 0; i < objetos.size(); i++)
        objetos[i]->desactivar_lock();
}

bool Ovni::get_lock()
{
    return objetos[0]->get_lock();
}

void Ovni::activar_prelock()
{
    for (int i = 0; i < objetos.size(); i++)
        objetos[i]->activar_prelock();
}

void Ovni::desactivar_prelock()
{
    for (int i = 0; i < objetos.size(); i++)
        objetos[i]->desactivar_prelock();
}