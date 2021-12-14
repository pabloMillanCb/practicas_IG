#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

class Camara
{
private:

    Tupla3f eye;
    Tupla3f at;
    Tupla3f up;

    int tipo; //ORTOGONAL o Perspectiva
    float left, right, near, far; //o bien aspect, fov, near, far

    void rotarXExaminar(float angle);
    void rotarYExaminar(float angle);
    void rotarZExaminar(float angle);
    void rotarXFirstPerson(float angle);
    void rotarYFirstPerson(float angle);
    void rotarZFirstPerson(float angles);

public:

    Camara();
    void mover(float x, float y, float z);
    void zoom(float factor);
    void setObserver();
    void setProyeccion();
} ;

#endif