#include "camara.h"
#include <iostream>

    Camara::Camara(int tipo_, Tupla3f eye_, Tupla3f at_)
    {
        up = {0, 1, 0};
        at = at_;
        eye = eye_;

        near = 50.0;
        far = 2000.0;

        tipo = tipo_;
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
        Tupla3f p = eye-at;
        p = alinearEjes(p);
        p = rotarEjeX(p, angle);
        p = desalinearEjes(p);
        //if ( at(0)*p(0) >= 0 )
        eye = at + p;
    }

    void Camara::rotarYExaminar(float angle)
    {
        eye = at + rotarEjeY(eye-at, angle);
    }

    void Camara::rotarZExaminar(float angle)
    {
        Tupla3f p = eye-at;
        p = alinearEjes(p);
        p = rotarEjeZ(p, angle);
        p = desalinearEjes(p);
        //if ( at(0)*p(0) >= 0 )
        eye = at + p;
    }

    void Camara::rotarXFirstPerson(float angle)
    {

        Tupla3f p = at-eye;
        p = alinearEjes(p);
        p = rotarEjeX(p, angle);
        p = desalinearEjes(p);
        //if ( at(0)*p(0) >= 0 )
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
        if (!locked)
            at = eye + vector;
    }

    void Camara::avanzar(bool dir)
    {
        Tupla3f vector = devolverDireccion();

        if (!dir)
            vector = vector*(-1);

        eye = eye + vector;
    
        if (!locked)
            at = at + vector;
    }

    Tupla3f Camara::devolverDireccion()
    {
        return 10.0f*normalizar(at - eye);
    }

    void Camara::zoom(float factor)
    {
        factor_zoom *= factor;

        if (factor_zoom > 1.2)
            factor_zoom = 1.2;
    }

    void Camara::setObserver()
    {
        gluLookAt(eye(0), eye(1), eye(2),
                 at(0), at(1), at(2),
                 up(0), up(1), up(2));
    }

    void Camara::setProyeccion()
    {
        if (tipo == PERSPECTIVA)
        {
            glFrustum(left*factor_zoom, right*factor_zoom, bottom*factor_zoom, top*factor_zoom, near, far);
        }
        else if (tipo == ORTOGONAL)
        {
            glOrtho(left*factor_zoom, right*factor_zoom, bottom*factor_zoom, top*factor_zoom, near, far);
        }
    }

    Tupla3f Camara::rotarEjeX(Tupla3f p, float radianes)
    {
        Tupla3f salida;

        salida(0) = p(0);
        salida(1) = cos(radianes)*p(1) - sin(radianes)*p(2);
        salida(2) = sin(radianes)*p(1) + cos(radianes)*p(2);

        return salida;
    }

    Tupla3f Camara::rotarEjeY(Tupla3f p, float radianes)
    {
        Tupla3f salida;

        salida(0) = cos(radianes)*p(0) + sin(radianes)*p(2);
        salida(1) = p(1);
        salida(2) = -sin(radianes)*p(0) + cos(radianes)*p(2);

        return salida;
    }

    Tupla3f Camara::rotarEjeZ(Tupla3f p, float radianes)
    {
        Tupla3f salida;

        salida(0) = cos(radianes)*p(0) - sin(radianes)*p(1);
        salida(1) = sin(radianes)*p(0) + cos(radianes)*p(1);
        salida(2) = p(2);

        return salida;
    }

    void Camara::girar(float x, float y)
    {
        if (locked)
        {
            rotarYExaminar(-x);
            rotarXExaminar(-y);
        }

        else
        {
            rotarYFirstPerson(-x);
            rotarXFirstPerson(y);
        }
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
            p = rotarEjeY(p, -buff);

        return p;
    }

    Tupla3f Camara::desalinearEjes(Tupla3f p)
    {
        p = rotarEjeY(p, buff);

        return p;
    }

    Tupla3f Camara::normalizar(Tupla3f t)
    {
        float modulo = sqrt(pow(t(0),2) + pow(t(1),2) + pow(t(2),2));
        return t*(1/modulo);
    }

    void Camara::setPoint(int id)
    {
        id_obj_point = id;
    }

    int Camara::getPoint()
    {
        return id_obj_point;
    }

    void Camara::lock(Tupla3f point)
    {
        locked = true;
        at = point;
    }

    void Camara::unlock()
    {
        locked = false;
    }

    bool Camara::isLocked()
    {
        return locked;
    }

    void Camara::status()
    {
        std::cout << "tipo = " << tipo << std::endl;

        std::cout << "up = " << up << std::endl;
        std::cout << "at = " << at << std::endl;
        std::cout << "eye = " << eye << std::endl;
        std::cout << "near = " << near << std::endl;
        std::cout << "far = " << far << std::endl;
        std::cout << "zoom = " << factor_zoom << std::endl;
        std::cout << "------------------------------------" << std::endl;
    }