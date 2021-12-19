#include "laboon.h"

Laboon::Laboon(ObjPLY *ball, ObjPLY* som)
{
    ballena = ball;
    sombrero = som;
}

void Laboon::draw()
{

    glPushMatrix();
        glTranslatef(0, -70, 0);
        ballena->draw();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 55, 65);
        glScalef(0.5, 0.5, 0.5);
        glRotatef(5, 1, 0, 0);
        sombrero->draw();
    glPopMatrix();
}