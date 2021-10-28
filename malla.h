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

   void draw_ModoAjedrez();

   void cambiar_visibilidad() ;
   bool es_visible() ;
   void activar_inmediato() ;
   void activar_diferido() ;
   void cambiar_puntos() ;
   void cambiar_lineas() ;
   void cambiar_solido() ;
   void cambiar_ajedrez() ;

   GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram );

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   Tupla3f rotarEjeY(Tupla3f punto, float radianes) ;
   void generarColores();
   bool compararPuntos(Tupla3f a, Tupla3f b);
   Tupla3f proyectarPunto(Tupla3f p);
   bool esPolo(Tupla3f p);
   

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3i> f1, f2 ;
   int id_vbo_tri = 0, id_vbo_tri_1 = 0, id_vbo_tri_2 = 0;
   int id_vbo_ver = 0;
   int id_vbo_color, id_vbo_color2, id_vbo_color3;
   std::vector<float> colorArray, colorRojo, colorVerde;
   float visible = false;
   int modo_dibujado = INMEDIATO;
   bool modo_ajedrez = false;
   bool dibujar[3] = {true, false, false};

   // completar: tabla de colores, tabla de normales de vértices
} ;


#endif
