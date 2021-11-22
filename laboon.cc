#include "laboon.h"

Laboon::Laboon()
{
    ballena = new ObjPLY("./plys/laboon.ply");
    sombrero = new ObjPLY("./plys/sombrero.ply");

    Material dorado({0.780392, 0.568627, 0.113725, 1.0}, {0.992157, 0.941176, 0.807843, 1.0}, {0.329412, 0.223529, 0.027451, 1.0}, 100);
    Material azul({0.427451, 0.470588, 0.541176, 1.0}, {0.333333, 0.333333, 0.521569, 1.0}, {0.105882, 0.058824, 0.113725, 1.0}, 100);

    sombrero->setMaterial(dorado);
    ballena->setMaterial(azul);
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