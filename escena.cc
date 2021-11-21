

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
    cil = new Cilindro(6, 6, 40, 20);
    objetos.push_back(cil);
    con = new Cono(6, 6, 2.3, 0.7);
    objetos.push_back(con);
    esf = new Esfera(20, 20, 1.4);
    objetos.push_back(esf);
    ovn = new Ovni();

    Material bronce(Tupla4f(0.714, 0.4284, 0.18144, 1.0), Tupla4f(0.393548, 0.271906, 0.166721, 1.0), Tupla4f(0.2125, 0.1275, 0.054, 1.0), 50.0);
    Material blanco(Tupla4f(0.0, 0.0, 0.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(0.0, 0.0, 0.0, 1.0), 100.0);
    Material negro(Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(0.0, 0.0, 0.0, 1.0), Tupla4f(0.0, 0.0, 0.0, 1.0), 200.0);

    lucesdir.push_back(LuzDireccional(Tupla2f(0.0, 100.0), Tupla4f(0.8, 0.8, 0.8, 1.0), Tupla4f(0.4, 0.4, 0.4, 1.0)));
    lucespos.push_back(LuzPosicional(Tupla3f(-70.0, 100.0, 70.0), Tupla4f(0.8, 0.8, 0.8, 1.0), Tupla4f(0.8, 0.8, 0.8, 1.0)));

    peon->setMaterial(blanco);
    peon_r->setMaterial(negro);
    esf->setMaterial(bronce);
    
    lucesdir[0].set_id(GL_LIGHT0);
    lucespos[0].set_id(GL_LIGHT1);

    glShadeModel(GL_SMOOTH);
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
   Material bronce(Tupla4f(0.714, 0.4284, 0.18144, 1.0), Tupla4f(0.393548, 0.271906, 0.166721, 1.0), Tupla4f(0.2125, 0.1275, 0.054, 1.0), 50.0);
    Material blanco(Tupla4f(0.0, 0.0, 0.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(0.0, 0.0, 0.0, 1.0), 200.0);
    Material negro(Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(0.2, 0.2, 0.2, 1.0), Tupla4f(0.05, 0.05, 0.05, 1.0), 200.0);


   glEnable(GL_CULL_FACE);
   glEnable(GL_NORMALIZE);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
   //glScalef(30.0, 30.0, 30.0);
   glPointSize(7);
   glPolygonOffset(2.0, 5.0);

   if (glIsEnabled(GL_LIGHTING))
   {
      glDisable(GL_LIGHTING);
      ejes.draw();
      glEnable(GL_LIGHTING);
   }
   else
      ejes.draw();

      for (int i = 0; i < lucesdir.size(); i++)
         lucesdir[i].activar();
      
      for (int i = 0; i < lucespos.size(); i++)
         lucespos[i].activar();

      

      glPushMatrix();
      //glTranslatef(50.0, 0.0, 50.0);
      
      /*glTranslatef(0.0, -40.0, 0.0);
      glRotatef(50, 0, 1, 0);
      glRotatef(90, 1, 0, 0);
      glTranslatef(0.0, -20.0, 0.0);*/
      
      //cil->draw();
      ovn->draw();
      glPopMatrix();

      /*glPushMatrix();
      glTranslatef(50.0, 0.0, 0.0);
      glScalef(30.0, 30.0, 30.0);
      peon->draw();
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-50.0, 0.0, 0.0);
      glScalef(30.0, 30.0, 30.0);
      peon_r->draw();
      glPopMatrix();

      glPushMatrix();
      glTranslatef(0.0, 0.0, -70.0);
      glScalef(30.0, 30.0, 30.0);
      esf->draw();
      glPopMatrix();

   if (cubo->es_visible())
      cubo->draw();
   if (tetraedro->es_visible())
      tetraedro->draw();ply*/

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

         id_grado = -1;
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
         std::cout << "Modo Selección de visualización\n";
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

         if (modoMenu == SELDIBUJADO)
         {
            for (int i = 0; i < objetos.size(); i++)
               objetos[i]->activar_inmediato();

            ovn->activar_inmediato();
         }
         
         if (modoMenu == GRADOSLIBERTAD)
            id_grado = 0;

         if (modoMenu == NADA && glIsEnabled(GL_LIGHTING))
         {
            if (glIsEnabled(GL_LIGHT0))
            glDisable(GL_LIGHT0);
            else
               glEnable(GL_LIGHT0);
         }
         break;
      
      case '2':

         if (modoMenu == SELDIBUJADO)
         {
            for (int i = 0; i < objetos.size(); i++)
               objetos[i]->activar_diferido();

            ovn->activar_diferido();
         }

         if (modoMenu == GRADOSLIBERTAD)
            id_grado = 1;

         if (modoMenu == NADA && glIsEnabled(GL_LIGHTING))
         {
            if (glIsEnabled(GL_LIGHT1))
            glDisable(GL_LIGHT1);
            else
               glEnable(GL_LIGHT1);
         }
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

         if (modoMenu == GRADOSLIBERTAD)
            id_grado = 2;
         break;

      case '4':
   
         if (modoMenu == GRADOSLIBERTAD)
            id_grado = 3;
         break;

      case 'P':

         if (modoMenu == SELVISUALIZACION)
         {
            for (int i = 0; i < objetos.size(); i++)
            objetos[i]->cambiar_puntos();

            ovn->cambiar_puntos();
         }

         glDisable(GL_LIGHTING);
         break;

      case 'L':
         
         if (modoMenu == SELVISUALIZACION)
         {
            for (int i = 0; i < objetos.size(); i++)
            objetos[i]->cambiar_lineas();

            ovn->cambiar_lineas();
         }

         glDisable(GL_LIGHTING);
         break;

      case 'S':
         
         if (modoMenu == SELVISUALIZACION)
         {
            for (int i = 0; i < objetos.size(); i++)
            objetos[i]->cambiar_solido();

            ovn->cambiar_solido();
         }

         glDisable(GL_LIGHTING);
         break;

      case 'A':

         if (modoMenu == SELVISUALIZACION)
         {   
            for (int i = 0; i < objetos.size(); i++)
               objetos[i]->cambiar_ajedrez();

            ovn->cambiar_ajedrez();
            
            glDisable(GL_LIGHTING);
         }
         
         else if (glIsEnabled(GL_LIGHTING))
         {
            modoMenu = MODOALFA;
            std::cout << "Variar angulo alfa\n";
         }

         else
         {
            animacion_activa = !animacion_activa;
         }

         break;

      case 'I':
         glEnable(GL_LIGHTING);
         modoMenu = NADA;
         break;

      case 'M':
         modoMenu = GRADOSLIBERTAD;
         std::cout << "Modo grados de libertad\n";

         break;

      case '+':

         if (modoMenu == GRADOSLIBERTAD)
         {
            if (id_grado == -1)
               std::cout << "Selecciona un grado: 0-3\n";

            else
            {
               ovn->gradosLibertad(id_grado, 2.0);
            }
         }

         break;

      case '-':

         if (modoMenu == GRADOSLIBERTAD)
         {
            if (id_grado == -1)
               std::cout << "Selecciona un grado: 0-3\n";

            else
            {
               ovn->gradosLibertad(id_grado, -2.0);
            }
         }

         break;

      case 'B':
         modoMenu = MODOBETA;
         std::cout << "Variar angulo alfa\n";
         break;
      case '>':
         if (modoMenu == MODOALFA)
            lucesdir[0].variarAnguloAlpha(0.1);
         if (modoMenu == MODOBETA)
            lucesdir[0].variarAnguloBeta(0.1);
         break;
      case '<':
         if (modoMenu == MODOALFA)
            lucesdir[0].variarAnguloAlpha(-0.1);
         if (modoMenu == MODOBETA)
            lucesdir[0].variarAnguloBeta(-0.1);
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

void Escena::animarModeloJerarquico()
{
   if (animacion_activa)
   {
      ovn->aumentar_r_luces(velocidad*1.5);
      ovn->aumentar_foco_y(-velocidad*0.5);

      if (contador1 >= 65)
      {
         sentido1 = -sentido1;
         contador1 = 0;
      }
         
      if (contador2 >= 40)
      {
         sentido2 = -sentido2;
         contador2 = 0;
      }

      ovn->aumentar_h_gancho(velocidad*sentido1*0.3);
      ovn->aumentar_foco_x(velocidad*sentido2*0.5);

      contador1 += velocidad*0.3;
      contador2 += velocidad*0.5;
   }
}