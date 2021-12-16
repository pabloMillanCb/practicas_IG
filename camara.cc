#include "camara.h"
#include <iostream>

    Camara::Camara()
    {
        up = {0, 1, 0};
        at = {0, 0, -1};
        eye = {0, 0, 250};

        near = 50.0;
        far = 2000.0;

        tipo = PERSPECTIVA;
    }

    void Camara::actualizarRatio(float left_, float right_, float bottom_, float top_, float near_, float far_)
    {
        if (left_ != 0.0)
            left = left_;

        if (right_ != 0.0)
            right = right_;

        if (bottom_ != 0.0)
            bottom = bottom_;

        if (top_ != 0.0)
            top = top_;

        if (near_ != 0.0)
            near = near_;

        if (far_ != 0.0)
            far = far_;
    }

    void Camara::rotarXExaminar(float angle)
    {
        eye = at + rotarEjeX(eye-at, angle);
    }

    void Camara::rotarYExaminar(float angle)
    {
        eye = at + rotarEjeY(eye-at, angle);
    }

    void Camara::rotarZExaminar(float angle)
    {
        eye = at + rotarEjeZ(eye-at, angle);
    }

    void Camara::rotarXFirstPerson(float angle)
    {
        std::cout << "{" << at(0) << ", " << at(1) << ", " << at(2) << "}\n";

        Tupla3f p = at-eye;
        p = alinearEjes(p);
        p = rotarEjeX(p, angle);
        p = desalinearEjes(p);
        if ( at(0)*p(0) >= 0 )
            at = eye + p;
    }

    void Camara::rotarYFirstPerson(float angle)
    {
        at = eye + rotarEjeY(at-eye, angle);
    }

    void Camara::rotarZFirstPerson(float angle)
    {
        Tupla3f p = at-eye;
        p = alinearEjes(p);
        p = rotarEjeZ(p, angle);
        p = desalinearEjes(p);
        at = eye + p;
    }

    void Camara::mover(float x, float y, float z)
    {
        Tupla3f vector = at - eye;
        eye = {x, y, z};
        at = eye + vector;

        std::cout << "Camara movida\n";
    }

    void Camara::zoom(float factor)
    {
        
    }

    void Camara::setObserver()
    {
        gluLookAt(eye(0), eye(1), eye(2),
                 at(0), at(1), at(2),
                 up(0), up(1), up(2));
        //std::cout << "observer setted\n";
    }

    void Camara::setProyeccion()
    {
        
        if (tipo == PERSPECTIVA)
        {
            glFrustum(left, right, bottom, top, near, far);
        }
        else if (tipo == ORTOGONAL)
        {
            glOrtho(left, right, bottom, top, near, far);
        }
    }

    Tupla3f Camara::rotarEjeX(Tupla3f p, double radianes)
    {
        Tupla3f salida;

        salida(0) = p(0);
        salida(1) = cos(radianes)*p(1) - sin(radianes)*p(2);
        salida(2) = sin(radianes)*p(1) + cos(radianes)*p(2);

        return salida;
    }

    Tupla3f Camara::rotarEjeY(Tupla3f p, double radianes)
    {
        Tupla3f salida;

        salida(0) = cos(radianes)*p(0) + sin(radianes)*p(2);
        salida(1) = p(1);
        salida(2) = -sin(radianes)*p(0) + cos(radianes)*p(2);

        return salida;
    }

    Tupla3f Camara::rotarEjeZ(Tupla3f p, double radianes)
    {
        Tupla3f salida;

        salida(0) = cos(radianes)*p(0) - sin(radianes)*p(1);
        salida(1) = sin(radianes)*p(0) + cos(radianes)*p(1);
        salida(2) = p(2);

        return salida;
    }

    Tupla3f Camara::rotarEje(Tupla3f punto, double radianes, int eje)
    {
        Tupla3f salida;

        if (eje == 0)
            salida = rotarEjeX(punto, radianes);
        else if (eje == 1)
            salida = rotarEjeY(punto, radianes);
        else if (eje == 2)
            salida = rotarEjeZ(punto, radianes);

        return salida;
    }

    Tupla3f Camara::alinearEjes(Tupla3f p)
    {

        Tupla3f z = {0, 0, 1};

            buff = acosf((p(0)*z(0) + p(2)*z(2)) / ( sqrt(p(0)*p(0)+p(2)*p(2)) * sqrt(z(0)*z(0)+z(2)*z(2)) ));
        
        if (p(0) < 0)
        {
            p = rotarEjeY(p, buff);
            buff = -buff;
        }
        else
        {
            p = rotarEjeY(p, -buff);
        }

        return p;
    }

    Tupla3f Camara::desalinearEjes(Tupla3f p)
    {
        p = rotarEjeY(p, buff);

        return p;
    }