#include "aux.h"
#include "malla.h"
#include "cubo.h"

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
   f.push_back(Tupla3i(2, 3, 7));
   f.push_back(Tupla3i(0, 2, 6));
   f.push_back(Tupla3i(1, 0, 4));
   f.push_back(Tupla3i(3, 1, 5));
   f.push_back(Tupla3i(6, 7, 5));
   f.push_back(Tupla3i(0, 3, 2));
   f.push_back(Tupla3i(2, 7, 6));
   f.push_back(Tupla3i(0, 6, 4));
   f.push_back(Tupla3i(1, 4, 5));
   f.push_back(Tupla3i(3, 5, 7));
   f.push_back(Tupla3i(6, 5, 4));

   draw_size = f.size();
   draw_size_a1 = draw_size/2;
   draw_size_a2 = draw_size/2;

   generarColores();


}

