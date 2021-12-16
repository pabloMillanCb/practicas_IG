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
#include "textura.h"
#include "ovni.h"
#include "camara.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO, MODOALFA, MODOBETA, GRADOSLIBERTAD, SELVELOCIDAD} menu;
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

   Camara *camara;

   std::vector<Malla3D*> objetos;
   std::vector<LuzDireccional> lucesdir;
   std::vector<LuzPosicional> lucespos;
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro= nullptr ; // es importante inicializarlo a 'nullptr'
   ObjRevolucion * peon = nullptr;
   ObjRevolucion * peon2 = nullptr;
   ObjRevolucion * peon_r = nullptr;
   Cilindro * cil = nullptr;
   Cono * con = nullptr;
   Esfera * esf = nullptr;
   Esfera * luna = nullptr;
   Esfera * skybox = nullptr;
   ObjPLY * ply = nullptr;
   Ovni * ovn = nullptr;

   Textura *txt = nullptr;
   Textura *txt_luna = nullptr;
   Textura *txt_skybox = nullptr;

   //Control de animaciones

   std::vector<float> v = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
   float contador[5] = {0, 0, 0, 0, 45};
   float sentido[5] = {1, 1, 1, 1, 1};

   int contador_ballena1 = 0, contador_ballena2 = 0;

   bool animacion_activa = false;
   bool animacion_puntal = false;
   int id_grado = -1;

   float animacion_luz = 0;
   float animacion_luz_2 = 0;
   float animacion_tierra = 0;
   float animacion_luna = 0;
   
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

   //void funcion_idle();
   void animarModeloJerarquico();

};
#endif
