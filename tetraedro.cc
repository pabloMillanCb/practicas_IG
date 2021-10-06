#include "aux.h"
#include "malla.h"
#include "tetraedro.h"
#include <cmath>
#include <iostream>

Tetraedro::Tetraedro()
{

        Tupla3f a (60.0, 0.0, 0.0),
                b ( a(0)*cos(2*M_PI/3) - a(2)*sin(2*M_PI/3), 0.0, a(0)*sin(2*M_PI/3) + a(2)*cos(2*M_PI/3) ),
                c ( b(0)*cos(2*M_PI/3) - b(2)*sin(2*M_PI/3), 0.0, b(0)*sin(2*M_PI/3) + b(2)*cos(2*M_PI/3) );

        float h = sqrt((a-b).lengthSq() - a(0)*a(0));
        Tupla3f d ( 0, h*3/4, 0 );

        a = a - Tupla3f(0, h/4 , 0);
        b = b - Tupla3f(0, h/4, 0);
        c = c - Tupla3f(0, h/4, 0);

        v.push_back(a);
        v.push_back(b);
        v.push_back(c);
        v.push_back(d);

        f.push_back(Tupla3i(0, 1, 3));
        f.push_back(Tupla3i(2, 0, 3));
        f.push_back(Tupla3i(1, 2, 3));
        f.push_back(Tupla3i(1, 0, 2));

        f2.push_back(Tupla3i(0, 1, 3));
        f2.push_back(Tupla3i(1, 2, 3));
        f2.push_back(Tupla3i(2, 0, 3));
        f2.push_back(Tupla3i(1, 0, 2));

        colorArray[0] = 1; colorArray[1] = 0; colorArray[2] = 1;
        colorArray[3] = 1; colorArray[4] = 0; colorArray[5] = 1;
        colorArray[6] = 1; colorArray[7] = 0; colorArray[8] = 1;
        colorArray[9] = 1; colorArray[10] = 0; colorArray[11] = 1;

        colorRojo[0] = 1; colorRojo[1] = 0; colorRojo[2] = 0; //rojo
        colorRojo[3] = 1;  colorRojo[4] = 0; colorRojo[5] = 0; 
        colorRojo[6] = 1; colorRojo[7] = 0; colorRojo[8] = 0; 
        colorRojo[9] = 1; colorRojo[10] = 0; colorRojo[11] = 0;

        colorVerde[0] = 0;  colorVerde[1] = 1;  colorVerde[2] = 0; // verde
        colorVerde[3] = 0;  colorVerde[4] = 1;  colorVerde[5] = 0; 
        colorVerde[6] = 0;  colorVerde[7] = 1;  colorVerde[8] = 0; 
        colorVerde[9] = 0;  colorVerde[10] = 1; colorVerde[11] = 0;
}
