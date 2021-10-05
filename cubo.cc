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

   v.push_back(Tupla3f(-lado/2, -lado/2, -lado/2)); //rojo 0
   v.push_back(Tupla3f(lado/2, -lado/2, -lado/2)); //verde 1
   v.push_back(Tupla3f(-lado/2, -lado/2, lado/2)); //azul 2
   v.push_back(Tupla3f(lado/2, -lado/2, lado/2)); //amarillo 3

   v.push_back(Tupla3f(-lado/2, lado/2, -lado/2)); //morado 4
   v.push_back(Tupla3f(lado/2, lado/2, -lado/2)); //cian 5
   v.push_back(Tupla3f(-lado/2, lado/2, lado/2)); //blanco 6
   v.push_back(Tupla3f(lado/2, lado/2, lado/2)); //negro 7

   
   f.push_back(Tupla3i(0, 1, 3));
   f.push_back(Tupla3i(0, 3, 2));

   f.push_back(Tupla3i(2, 3, 7));
   f.push_back(Tupla3i(2, 7, 6));

   f.push_back(Tupla3i(0, 2, 6));
   f.push_back(Tupla3i(0, 6, 4));

   f.push_back(Tupla3i(1, 0, 4));
   f.push_back(Tupla3i(1, 4, 5));

   f.push_back(Tupla3i(3, 1, 5));
   f.push_back(Tupla3i(3, 5, 7));

   f.push_back(Tupla3i(6, 7, 5));
   f.push_back(Tupla3i(6, 5, 4));

   colorArray[0] = 1; colorArray[1] = 0; colorArray[2] = 0; //rojo
   colorArray[3] = 0; colorArray[4] = 1; colorArray[5] = 0; //verde
   colorArray[6] = 0; colorArray[7] = 0; colorArray[8] = 1; //azul
   colorArray[9] = 1; colorArray[10] = 1; colorArray[11] = 0; //amarillo
   colorArray[12] = 1; colorArray[13] = 0; colorArray[14] = 1; //morado
   colorArray[15] = 0; colorArray[16] = 1; colorArray[17] = 1; //cian
   colorArray[18] = 1; colorArray[19] = 1; colorArray[20] = 1; //blanco
   colorArray[21] = 0; colorArray[22] = 0; colorArray[23] = 0; //negro


}

