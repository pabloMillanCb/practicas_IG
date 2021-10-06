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



   f2.push_back(Tupla3i(0, 1, 3));
   f2.push_back(Tupla3i(2, 3, 7));
   f2.push_back(Tupla3i(0, 2, 6));
   f2.push_back(Tupla3i(1, 0, 4));
   f2.push_back(Tupla3i(3, 1, 5));
   f2.push_back(Tupla3i(6, 7, 5));

   f2.push_back(Tupla3i(0, 3, 2));
   f2.push_back(Tupla3i(2, 7, 6));
   f2.push_back(Tupla3i(0, 6, 4));
   f2.push_back(Tupla3i(1, 4, 5));
   f2.push_back(Tupla3i(3, 5, 7));
   f2.push_back(Tupla3i(6, 5, 4));



   colorArray[0] = 1; colorArray[1] = 0; colorArray[2] = 0; //rojo
   colorArray[3] = 0; colorArray[4] = 1; colorArray[5] = 0; //verde
   colorArray[6] = 0; colorArray[7] = 0; colorArray[8] = 1; //azul
   colorArray[9] = 1; colorArray[10] = 1; colorArray[11] = 0; //amarillo
   colorArray[12] = 1; colorArray[13] = 0; colorArray[14] = 1; //morado
   colorArray[15] = 0; colorArray[16] = 1; colorArray[17] = 1; //cian
   colorArray[18] = 1; colorArray[19] = 1; colorArray[20] = 1; //blanco
   colorArray[21] = 0; colorArray[22] = 0; colorArray[23] = 0; //negro

   colorRojo[0] = 1; colorRojo[1] = 0; colorRojo[2] = 0; //rojo
   colorRojo[3] = 1;  colorRojo[4] = 0; colorRojo[5] = 0; 
   colorRojo[6] = 1; colorRojo[7] = 0; colorRojo[8] = 0; 
   colorRojo[9] = 1; colorRojo[10] = 0; colorRojo[11] = 0;
   colorRojo[12] = 1; colorRojo[13] = 0; colorRojo[14] = 0; 
   colorRojo[15] = 1; colorRojo[16] = 0; colorRojo[17] = 0; 
   colorRojo[18] = 1; colorRojo[19] = 0; colorRojo[20] = 0;
   colorRojo[21] = 1; colorRojo[22] = 0; colorRojo[23] = 0;

   colorVerde[0] = 0;  colorVerde[1] = 1;  colorVerde[2] = 0; // verde
   colorVerde[3] = 0;  colorVerde[4] = 1;  colorVerde[5] = 0; 
   colorVerde[6] = 0;  colorVerde[7] = 1;  colorVerde[8] = 0; 
   colorVerde[9] = 0;  colorVerde[10] = 1; colorVerde[11] = 0;
   colorVerde[12] = 0; colorVerde[13] = 1; colorVerde[14] = 0; 
   colorVerde[15] = 0; colorVerde[16] = 1; colorVerde[17] = 0; 
   colorVerde[18] = 0; colorVerde[19] = 1; colorVerde[20] = 0;
   colorVerde[21] = 0; colorVerde[22] = 1; colorVerde[23] = 0;


}

