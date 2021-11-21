#include "lucesovni.h"

LucesOvni::LucesOvni()
{
    //aplicar material a luz
    r_bolas = 0;
    bola = new Esfera(12, 12, 12);

    Material dorado({0.780392, 0.568627, 0.113725, 1.0}, {0.992157, 0.941176, 0.807843, 1.0}, {0.329412, 0.223529, 0.027451, 1.0}, 100);
    bola -> setMaterial(dorado);
}

void LucesOvni::draw()
{
    glPushMatrix();
       // glRotatef(0, r_bolas, 0);
        glTranslatef(70, 0, 0);
        bola->draw();
    glPopMatrix();

    glPushMatrix();
       // glRotatef(0, r_bolas + 360/3, 0);
        glTranslatef(0, 0, 70);
        bola->draw();
    glPopMatrix();

    glPushMatrix();
       // glRotatef(0, r_bolas + 360/3*2, 0);
        glTranslatef(-70, 0, 0);
        bola->draw();
    glPopMatrix();

    glPushMatrix();
       // glRotatef(0, r_bolas + 360/3*2, 0);
        glTranslatef(0, 0, -70);
        bola->draw();
    glPopMatrix();
}

void LucesOvni::cambiar_solido()
{
    bola->cambiar_solido();
}
void LucesOvni::cambiar_lineas()
{
    bola->cambiar_lineas();
}
void LucesOvni::cambiar_puntos()
{
    bola->cambiar_puntos();
}
void LucesOvni::cambiar_ajedrez()
{
    bola->cambiar_ajedrez();
}

void LucesOvni::activar_inmediato()
{
    bola->activar_inmediato();
}
void LucesOvni::activar_diferido()
{
    bola->activar_diferido();
}