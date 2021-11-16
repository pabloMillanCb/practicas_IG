

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
    peon = new ObjRevolucion("./plys/peon.ply", 8, 1, true, true);
    objetos.push_back(peon);
    peon_r = new ObjRevolucion("./plys/peon.ply", 8, 1, true, true);
    objetos.push_back(peon_r);
    cil = new Cilindro(6, 6, 2.3, 0.5);
    objetos.push_back(cil);
    con = new Cono(6, 6, 2.3, 0.7);
    objetos.push_back(con);
    esf = new Esfera(20, 20, 1.4);
    objetos.push_back(esf);
    ply = new ObjPLY("./plys/ant.ply");
    objetos.push_back(ply);

    
    Material m(Tupla4f(0.714, 0.4284, 0.18144, 1.0), Tupla4f(0.393548, 0.271906, 0.166721, 1.0), Tupla4f(0.2125, 0.1275, 0.054, 1.0), 50.0);
    Material blanco(Tupla4f(0.0, 0.0, 0.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(0.0, 0.0, 0.0, 1.0), 200.0);
    Material negro(Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(0.0, 0.0, 0.0, 1.0), Tupla4f(0.05, 0.05, 0.05, 1.0), 200.0);

    //luces.push_back(LuzDireccional(Tupla2f(0.0, 0.0), Tupla4f(0.8, 0.8, 0.8, 1.0), Tupla4f(0.8, 0.8, 0.8, 1.0)));
    luces.push_back(LuzPosicional(Tupla3f(0.0, 100.0, 50.0), Tupla4f(0.8, 0.8, 0.8, 1.0), Tupla4f(0.8, 0.8, 0.8, 1.0)));
    //luces.push_back(LuzPosicional(Tupla3f(0.0, 20.0, 0.0), Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0)));

      peon->setMaterial(blanco);
      peon_r->setMaterial(negro);
    
    luces[0].set_id(GL_LIGHT0);
    //luces[1].set_id(GL_LIGHT1);
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
   glEnable(GL_NORMALIZE);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
   //glScalef(30.0, 30.0, 30.0);
   glPointSize(7);
   glPolygonOffset(2.0, 5.0);

   ejes.draw();

      luces[0].activar();
      luces[1].activar();

      glPushMatrix();
      glTranslatef(30.0, 0.0, 0.0);
      glScalef(30.0, 30.0, 30.0);
      peon->draw();
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-30.0, 0.0, 0.0);
      glScalef(30.0, 30.0, 30.0);
      peon_r->draw();
      glPopMatrix();

   if (cubo->es_visible())
      cubo->draw();
   if (tetraedro->es_visible())
      tetraedro->draw();

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
         
         for (int i = 0; i < luces.size() && modoMenu==SELDIBUJADO; i++)
            luces[i].encender();

         std::cout << "sensiende\n";
         break;
      
      case '2':
         for (int i = 0; i < objetos.size() && modoMenu==SELDIBUJADO; i++)
            objetos[i]->activar_diferido();
         break;
      
      case '3':
         if (modoMenu == SELDIBUJADO)
         {
            peon->cambiarTapas();
            peon_r->cambiarTapas();
            cil->cambiarTapas();
            con->cambiarTapas();
            esf->cambiarTapas();
         }
         break;

      case 'P':
         for (int i = 0; i < objetos.size() && modoMenu==SELVISUALIZACION; i++)
            objetos[i]->cambiar_puntos();
         glDisable(GL_LIGHTING);
         break;

      case 'L':
         for (int i = 0; i < objetos.size() && modoMenu==SELVISUALIZACION; i++)
            objetos[i]->cambiar_lineas();
         glDisable(GL_LIGHTING);
         break;

      case 'S':
         for (int i = 0; i < objetos.size() && modoMenu==SELVISUALIZACION; i++)
            objetos[i]->cambiar_solido();
         glDisable(GL_LIGHTING);
         break;

      case 'A':
         for (int i = 0; i < objetos.size() && modoMenu==SELVISUALIZACION; i++)
            objetos[i]->cambiar_ajedrez();
         glDisable(GL_LIGHTING);
         break;

      case 'I':
         glEnable(GL_LIGHTING);
         for (int i = 0; i < objetos.size() && modoMenu==SELVISUALIZACION; i++)
            objetos[i]->activar_luz();
         break;
      /*case 'Z':
         luces[0].Colocar({luces[0].get(0)+5, luces[0].get(1), luces[0].get(2)});
         break;
      case 'X':
         luces[0].Colocar({luces[0].get(0), luces[0].get(1)+5, luces[0].get(2)});
         break;
      case 'c':
         luces[0].Colocar({luces[0].get(0), luces[0].get(1), luces[0].get(2)+5});
         break;
      case 'B':
         luces[0].Colocar({luces[0].get(0)-5, luces[0].get(1), luces[0].get(2)});
         break;
      case 'N':
         luces[0].Colocar({luces[0].get(0), luces[0].get(1)-5, luces[0].get(2)});
         break;
      case 'M':
         luces[0].Colocar({luces[0].get(0), luces[0].get(1), luces[0].get(2)-5});
         break;*/
         
            
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
