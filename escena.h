#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "luz.h"
#include "luzdireccional.h"
#include "luzposicional.h"
#include "material.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO} menu;
class Escena
{

   private:

   bool figuras[2] = {false, false};

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
    


   void clear_window();

   menu modoMenu=NADA;
   // Objetos de la escena
   Ejes ejes;
   std::vector<Malla3D*> objetos;
   std::vector<LuzPosicional> luces;
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro= nullptr ; // es importante inicializarlo a 'nullptr'
   ObjRevolucion * peon = nullptr;
   ObjRevolucion * peon2 = nullptr;
   ObjRevolucion * peon_r = nullptr;
   Cilindro * cil = nullptr;
   Cono * con = nullptr;
   Esfera * esf = nullptr;
   ObjPLY * ply = nullptr;
   
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;
  /* glPushMatrix();
      glTranslatef(-2.5, -1.15, 0.0);
      glScalef(30.06, 30.06, 30.06);
      cil->draw();
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0.0, -1.15, 2.5);
      con->draw();
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0.0, 0.0, -2.5);
      esf->draw();
   glPopMatrix();

   /*glPushMatrix();
      glTranslatef(2.5, 2.5, 2.5);
      peon_r->draw();
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0.0, 0.0, 0.0);
      glScalef(0.06, 0.06, 0.06);
      ply->draw();
   glPopMatrix();*/

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif
