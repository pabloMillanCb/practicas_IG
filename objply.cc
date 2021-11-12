#include "objply.h"
#include "ply_reader.h"
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, this->v, this->f );
   
   draw_size = f.size();
   draw_size_a1 = draw_size/2;
   draw_size_a2 = draw_size/2;

   generarColores();
   mezclarCaras();
   calcular_normales();
}


