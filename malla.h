// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

enum modos {INMEDIATO, DIFERIDO};

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato();

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw() ;

   void cambiar_visibilidad() ;
   bool es_visible() ;
   void activar_inmediato() ;
   void activar_diferido() ;
   void cambiar_puntos() ;
   void cambiar_lineas() ;
   void cambiar_solido() ;

   GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram );

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   int id_vbo_tri;
   int id_vbo_ver;
   float colorArray[24];
   float visible = false;
   int modo_dibujado = INMEDIATO;
   bool dibujar[3] = {true, false, false};

   // completar: tabla de colores, tabla de normales de vértices
} ;


#endif
