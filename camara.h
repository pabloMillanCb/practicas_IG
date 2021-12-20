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
    float leftz, rightz, bottomz, topz; //o bien aspect, fov, near, far
    float factor_zoom = 1;

    bool locked = false;

    Tupla3f rotarEjeX(Tupla3f punto, float radianes) ; //Rota en el eje X un punto
    Tupla3f rotarEjeY(Tupla3f punto, float radianes) ; //Rota en el eje Y un punto
    Tupla3f rotarEjeZ(Tupla3f punto, float radianes) ; //Rota en el eje Z un punto
    Tupla3f rotarEje(Tupla3f punto, float radianes, int eje) ; //Rota en un eje un punto
    Tupla3f alinearEjes(Tupla3f p);
    Tupla3f desalinearEjes(Tupla3f p);
    Tupla3f normalizar(Tupla3f t);
    void updateZoom();

    int id_obj_point = -1;

public:

    Camara(int tipo_);
    void mover(float x, float y, float z);
    void avanzar(bool dir);
    void zoom(float factor);
    void actualizarRatio(float left_, float right_, float bottom_, float top_, float near_, float far_);
    void setObserver();
    void setProyeccion();

    void girar(float x, float y);
    void rotarXExaminar(float angle);
    void rotarYExaminar(float angle);
    void rotarZExaminar(float angle);
    void rotarXFirstPerson(float angle);
    void rotarYFirstPerson(float angle);
    void rotarZFirstPerson(float angle);

    Tupla3f devolverDireccion();
    int getTipo();
    void setPoint(int id);
    int getPoint();

    void lock(Tupla3f point);
    void unlock();
    bool isLocked();
    
    void status();
} ;

#endif