#include "aux.h"
#include "malla.h"
#include "cubo.h"
#include <iostream>
Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   id_vbo_ver = 0;
   id_vbo_tri = 0;

   v.push_back(Tupla3f(-lado/2, -lado/2, -lado/2));
   v.push_back(Tupla3f(lado/2, -lado/2, -lado/2));
   v.push_back(Tupla3f(-lado/2, -lado/2, lado/2));
   v.push_back(Tupla3f(lado/2, -lado/2, lado/2));

   v.push_back(Tupla3f(-lado/2, lado/2, -lado/2));
   v.push_back(Tupla3f(lado/2, lado/2, -lado/2));
   v.push_back(Tupla3f(-lado/2, lado/2, lado/2));
   v.push_back(Tupla3f(lado/2, lado/2, lado/2));

   
   f.push_back(Tupla3i(0, 1, 2));
   f.push_back(Tupla3i(1, 3, 2));

   f.push_back(Tupla3i(5, 1, 0));
   f.push_back(Tupla3i(5, 0, 4));

   f.push_back(Tupla3i(1, 5, 7));
   f.push_back(Tupla3i(1, 7, 3));

   f.push_back(Tupla3i(3, 7, 6));
   f.push_back(Tupla3i(2, 3, 6));

   f.push_back(Tupla3i(2, 6, 4));
   f.push_back(Tupla3i(2, 4, 0));

   f.push_back(Tupla3i(6, 5, 4));
   f.push_back(Tupla3i(6, 7, 5));

   colorArray[0] = 1; colorArray[1] = 0; colorArray[2] = 1;
   colorArray[3] = 1; colorArray[4] = 0; colorArray[5] = 1;
   colorArray[6] = 1; colorArray[7] = 0; colorArray[8] = 1;
   colorArray[9] = 0; colorArray[10] = 0; colorArray[11] = 1;
   colorArray[12] = 0; colorArray[13] = 0; colorArray[14] = 1;
   colorArray[15] = 0; colorArray[16] = 0; colorArray[17] = 1;
   colorArray[18] = 0; colorArray[19] = 0; colorArray[20] = 1;
   colorArray[21] = 0; colorArray[22] = 0; colorArray[23] = 1;


}

