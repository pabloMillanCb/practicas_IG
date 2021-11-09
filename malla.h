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

   void draw_ModoInmediato(); // dibuja el objeto en modo inmediato
   void draw_ModoDiferido();  // dibuja el objeto en modo diferido (usando VBOs)
   void draw() ; // función que redibuja el objeto
   void draw_ModoAjedrez();
   void cambiar_visibilidad() ;
   bool es_visible() ;
   void activar_inmediato() ;
   void activar_diferido() ;
   void cambiar_puntos() ;
   void cambiar_lineas() ;
   void cambiar_solido() ;
   void cambiar_ajedrez() ;
   void mezclarCaras(); //Prepara el vector de triángulos para el modo ajedrez

   GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram );

   protected:

   virtual void drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices);
   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   Tupla3f vectorNormal(Tupla3i c);
   void generarColores();

   Tupla3f proyectarPunto(Tupla3f p, int eje); //Proyecta un punto en el eje Y
   bool compararPuntos(Tupla3f a, Tupla3f b);

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> nv;
   std::vector<float> colorArray, colorRojo, colorVerde;

   int draw_size, draw_size_a1, draw_size_a2,
       id_vbo_tri = 0, id_vbo_tri_1 = 0, id_vbo_tri_2 = 0,
       id_vbo_ver = 0, id_vbo_color = 0, id_vbo_color2 = 0, id_vbo_color3 = 0,
       modo_dibujado = INMEDIATO;

   float visible = false;
   bool modo_ajedrez = false,
        dibujar[3] = {true, false, false};

   // completar: tabla de colores, tabla de normales de vértices
} ;


#endif
