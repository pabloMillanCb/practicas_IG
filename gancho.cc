#include "gancho.h"
#include <iostream>

Gancho::Gancho(Cilindro *len, Cilindro *cab, Cono *ant, Cono *antR, Cilindro *antCil, Esfera *antEsf)
{
    lentes = len;
    cable = cab;

    antenaCono = ant;
    antenaConoR = antR;
    antenaCilindro = antCil;
    antenaEsfera = antEsf;
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
