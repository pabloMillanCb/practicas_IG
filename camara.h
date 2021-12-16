#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

enum camaras {ORTOGONAL, PERSPECTIVA};

class Camara
{
private:

    Tupla3f eye;
    Tupla3f at;
    Tupla3f up;

    double buff;

    int tipo; //ORTOGONAL o Perspectiva
    float left, right, bottom, top, near, far; //o bien aspect, fov, near, far

    Tupla3f rotarEjeX(Tupla3f punto, double radianes) ; //Rota en el eje X un punto
    Tupla3f rotarEjeY(Tupla3f punto, double radianes) ; //Rota en el eje Y un punto
    Tupla3f rotarEjeZ(Tupla3f punto, double radianes) ; //Rota en el eje Z un punto
    Tupla3f rotarEje(Tupla3f punto, double radianes, int eje) ; //Rota en un eje un punto
    Tupla3f alinearEjes(Tupla3f p);
    Tupla3f desalinearEjes(Tupla3f p);

public:

    Camara();
    void mover(float x, float y, float z);
    void zoom(float factor);
    void actualizarRatio(float left_, float right_, float bottom_, float top_, float near_, float far_);
    void setObserver();
    void setProyeccion();
    void rotarXExaminar(float angle);
    void rotarYExaminar(float angle);
    void rotarZExaminar(float angle);
    void rotarXFirstPerson(float angle);
    void rotarYFirstPerson(float angle);
    void rotarZFirstPerson(float angle);
} ;

#endif