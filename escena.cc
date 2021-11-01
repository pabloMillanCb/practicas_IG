

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include <iostream>

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de la escena....
    // .......completar: ...
    // .....
    cubo = new Cubo(60);
    tetraedro = new Tetraedro();
    objetos.push_back(cubo);
    objetos.push_back(tetraedro);
    peon = new ObjRevolucion("./plys/peon.ply", 3, 1, true, true);
    objetos.push_back(peon);
    /*cil = new Cilindro(6, 6, 1.0, 1.5);
    objetos.push_back(cil);
    con = new Cono(6, 6, 1.0, 1.5);
    objetos.push_back(con);*/

}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
   glEnable(GL_CULL_FACE);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
    ejes.draw();

    if (cubo->es_visible())
      cubo->draw();
    if (tetraedro->es_visible())
      tetraedro->draw();

   glScalef(50.0, 50.0, 50.0);
   glPointSize(7);
   peon->draw();
   //cil->draw();
   //con->draw();
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
         break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO; 
         std::cout << "Selecciona un objeto\n";
         break ;
        case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         break ;
       case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         std::cout << "Selecciona un modo de dibujados\n";
         break ;
         // COMPLETAR con los diferentes opciones de teclado
      case 'C':
         if (modoMenu == SELOBJETO)
            cubo->cambiar_visibilidad();
         break;
      
      case 'T':
         if (modoMenu == SELOBJETO)
            tetraedro->cambiar_visibilidad();
         break;
      
      case '1':
         for (int i = 0; i < objetos.size() && modoMenu==SELDIBUJADO; i++)
            objetos[i]->activar_inmediato();
         break;
      
      case '2':
         for (int i = 0; i < objetos.size() && modoMenu==SELDIBUJADO; i++)
            objetos[i]->activar_diferido();
         break;
      
      case '3':
         if (modoMenu == SELDIBUJADO)
         {
            peon->cambiarTapas();
            //cil->cambiarTapas();
            //con->cambiarTapas();
         }
         break;

      case 'P':
         for (int i = 0; i < objetos.size() && modoMenu==SELVISUALIZACION; i++)
            objetos[i]->cambiar_puntos();
         break;

      case 'L':
         for (int i = 0; i < objetos.size() && modoMenu==SELVISUALIZACION; i++)
            objetos[i]->cambiar_lineas();
         break;

      case 'S':
         for (int i = 0; i < objetos.size() && modoMenu==SELVISUALIZACION; i++)
            objetos[i]->cambiar_solido();
         break;

      case 'A':
         for (int i = 0; i < objetos.size() && modoMenu==SELVISUALIZACION; i++)
            objetos[i]->cambiar_ajedrez();
         break;
         
            
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
