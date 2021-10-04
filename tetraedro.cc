#include "aux.h"
#include "malla.h"
#include "tetraedro.h"
#include <cmath>
#include <iostream>

Tetraedro::Tetraedro()
{

   // inicializar la tabla de vértices

    
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

        id_vbo_ver = 0;
        id_vbo_tri = 0;

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

        colorArray[0] = 1; colorArray[1] = 0; colorArray[2] = 1;
        colorArray[3] = 1; colorArray[4] = 0; colorArray[5] = 1;
        colorArray[6] = 1; colorArray[7] = 0; colorArray[8] = 1;
        colorArray[9] = 1; colorArray[10] = 0; colorArray[11] = 1;
        colorArray[12] = 1; colorArray[13] = 0; colorArray[14] = 1;
        colorArray[15] = 1; colorArray[16] = 0; colorArray[17] = 1;
        colorArray[18] = 1; colorArray[19] = 0; colorArray[20] = 1;
        colorArray[21] = 1; colorArray[22] = 0; colorArray[23] = 1;
        
}
