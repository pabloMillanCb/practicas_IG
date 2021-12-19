#include "lucesovni.h"

LucesOvni::LucesOvni(Esfera *b)
{
    //aplicar material a luz
    r_bolas = 0;
    bola = b;
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