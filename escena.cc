

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include <iostream>
#include "laboon.h"

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
   Front_plane       = 50.0;
   Back_plane        = 10000.0;
   Observer_distance = 4*Front_plane;
   Observer_angle_x  = 0.0 ;
   Observer_angle_y  = 0.0 ;

   ejes.changeAxisSize( 5000 );

   // crear los objetos de la escena....
   // .......completar: ...
   // .....
   cubo = new Cubo(30);
   tetraedro = new Tetraedro();
   peon = new ObjRevolucion("./plys/peon.ply", 8, 1, true, true);
   peon_r = new ObjRevolucion("./plys/peon.ply", 8, 1, true, true);
   cil = new Cilindro(6, 6, 40, 20);

   con = new Cono(6, 6, 2.3, 0.7, true);
   esf = new Esfera(50, 50, 1000);
   luna = new Esfera(50, 50, 60);
   skybox = new Esfera(100, 100, 3000);
   ovn = new Ovni();
   ply = new ObjPLY("./plys/laboon.ply");

   objetos.push_back(cubo);
   objetos.push_back(tetraedro);
   objetos.push_back(peon);
   objetos.push_back(peon_r);
   objetos.push_back(cil);
   objetos.push_back(con);
   objetos.push_back(esf);
   objetos.push_back(luna);
   objetos.push_back(ply);
   objetos.push_back(skybox);

   camara.push_back(new Camara(PERSPECTIVA));
   camara.push_back(new Camara(PERSPECTIVA));
   camara.push_back(new Camara(ORTOGONAL));

   Material bronce(Tupla4f(0.714, 0.4284, 0.18144, 1.0), Tupla4f(0.393548, 0.271906, 0.166721, 1.0), Tupla4f(0.2125, 0.1275, 0.054, 1.0), 50.0);
   Material espacio(Tupla4f(0.0, 0.0, 0.0, 1.0), Tupla4f(0.0, 0.0, 0.0, 1.0), Tupla4f(0.3, 0.3, 0.3, 1.0), 50.0);
   Material tierra(Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(0.0, 0.0, 0.0, 1.0), Tupla4f(0.1, 0.1, 0.1, 1.0), 100.0);
   Material negro(Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(0.0, 0.0, 0.0, 1.0), Tupla4f(0.0, 0.0, 0.0, 1.0), 200.0);

   lucesdir.push_back(LuzDireccional(Tupla2f(0.0, 0.0), Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0)));
   lucespos.push_back(LuzPosicional(Tupla3f(0.0, 0.0, 0.0), Tupla4f(1.0, 1.0, 1.0, 0.3), Tupla4f(1.0, 1.0, 1.0, 0.3)));

   skybox->setMaterial(espacio);
   esf->setMaterial(tierra);
   luna->setMaterial(tierra);
   cubo->setMaterial(bronce);
   tetraedro->setMaterial(bronce);

   lucesdir[0].set_id(GL_LIGHT0);
   lucespos[0].set_id(GL_LIGHT1);

   txt = new Textura("./txt/text-tierra.jpg"); ///txt/text-lata-1.jpg"
   txt_luna = new Textura("./txt/luna.jpg"); ///txt/text-lata-1.jpg"
   txt_skybox = new Textura("./txt/cielo.jpg"); ///txt/text-lata-1.jpg"

   esf->setTextura(*txt);
   luna->setTextura(*txt_luna);
   skybox->setTextura(*txt_skybox);
   skybox->invertir_caras();

   objetos_sel.push_back(esf);
   objetos_sel.push_back(luna);
   objetos_sel.push_back(cubo);
   objetos_sel.push_back(tetraedro);
   //Ovni, con id == 4

   for (int i = 0; i < objetos_sel.size(); i++)
   {
      pos_objetos.push_back(Tupla3f(0.0, 0.0, 0.0));
   }

   pos_objetos.push_back({0.0, 0.0, 0.0});

   objetos_sel[0]->setColorSeleccion(Tupla3f(0.0, 1.0, 0.0));
   col_objetos.push_back(Tupla3f(0.0, 1.0, 0.0));

   objetos_sel[1]->setColorSeleccion(Tupla3f(0.0, 1.0, 1.0));
   col_objetos.push_back(Tupla3f(0.0, 1.0, 1.0));

   objetos_sel[2]->setColorSeleccion(Tupla3f(1.0, 0.0, 0.0));
   col_objetos.push_back(Tupla3f(1.0, 0.0, 0.0));

   objetos_sel[3]->setColorSeleccion(Tupla3f(1.0, 0.0, 1.0));
   col_objetos.push_back(Tupla3f(1.0, 0.0, 1.0));

   ovn->setColorSeleccion(Tupla3f(0.0, 0.0, 1.0));
   col_objetos.push_back(Tupla3f(0.0, 0.0, 1.0));
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
   glShadeModel(GL_SMOOTH);
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
   {
      ejes.draw();

   }

   glPushMatrix();
      skybox->draw();
   glPopMatrix();

   lucesdir[0].activar();

   glPushMatrix();
      glTranslatef(0, 50, 0);
      glRotatef(animacion_luz_2, 0, 1, 0);
      glTranslatef(60, 0, 0);
      lucespos[0].activar();
   glPopMatrix();

   dibuja_objetos();
}

void Escena::dibuja_objetos()
{
   glPushMatrix();
         glTranslatef(0.0, 0.0, -1500.0);
         glRotatef(20.0, 0, 0, 1);
         glRotatef(animacion_tierra, 0, 1, 0);
         esf->draw();
         glPushMatrix();
            obtenerCoordenadas(0);
         glPopMatrix();
      glPopMatrix();

      glPushMatrix();
         glTranslatef(0.0, 0.0, -1500.0);
         glRotatef(35.0, 0, 0, 1);
         glRotatef(animacion_luna, 0, 1, 0);
         glTranslatef(0.0, 0.0, 1100.0);
         luna->draw();
         glPushMatrix();
            obtenerCoordenadas(1);
         glPopMatrix();
      glPopMatrix();

      glPushMatrix();
         glTranslatef(-200.0, 50.0, -100.0);
         glRotatef(animacion_luna, 0, 0, 1);
         glRotatef(30.0, 0, 1, 0);
         glPushMatrix();
            obtenerCoordenadas(2);
         glPopMatrix();
         if (cubo->es_visible())
            cubo->draw();
      glPopMatrix();

      glPushMatrix();
         glTranslatef(200.0, -50.0, -100.0);
         glRotatef(animacion_luna, 0, 0, 1);
         glRotatef(30.0, 0, 1, 0);
         obtenerCoordenadas(3);
         if (tetraedro->es_visible())
            tetraedro->draw();
      glPopMatrix();

      glPushMatrix();
         glTranslatef(0.0, 15.0, 0.0);
         glScalef(0.6, 0.6, 0.6);
         ovn->draw();
         obtenerCoordenadas(4);
      glPopMatrix();
}

void Escena::dibuja_seleccion()
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla

   ovn->activar_seleccion();
   for (int i = 0; i < objetos_sel.size(); i++)
      objetos_sel[i]->activar_seleccion();

   dibuja_objetos();

   ovn->desactivar_seleccion();
   for (int i = 0; i < objetos_sel.size(); i++)
      objetos_sel[i]->desactivar_seleccion();
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
         else
         {
            std::cout << "Menu de seleccion de cámara (1-3)\n";
            modoMenu = SELCAMARA;
         }
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
         
         if (modoMenu == GRADOSLIBERTAD || modoMenu == SELVELOCIDAD)
            id_grado = 0;

         if (modoMenu == NADA && glIsEnabled(GL_LIGHTING))
         {
            if (glIsEnabled(GL_LIGHT0))
            glDisable(GL_LIGHT0);
            else
               glEnable(GL_LIGHT0);
         }

         if (modoMenu == SELCAMARA)
         {
            id_cam = 0;
            camara[id_cam] -> setProyeccion();
            std::cout << "Camara 1 activada\n";

            change_observer();
            change_projection(0);
         }

         break;
      
      case '2':

         if (modoMenu == SELDIBUJADO)
         {
            for (int i = 0; i < objetos.size(); i++)
               objetos[i]->activar_diferido();

            ovn->activar_diferido();
         }

         if (modoMenu == GRADOSLIBERTAD || modoMenu == SELVELOCIDAD)
            id_grado = 1;

         if (modoMenu == NADA && glIsEnabled(GL_LIGHTING))
         {
            if (glIsEnabled(GL_LIGHT1))
            glDisable(GL_LIGHT1);
            else
               glEnable(GL_LIGHT1);
         }

         if (modoMenu == SELCAMARA)
         {
            id_cam = 1;
            camara[id_cam] -> setProyeccion();
            std::cout << "Camara 2 activada\n";

            change_observer();
            change_projection(0);
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

         if (modoMenu == GRADOSLIBERTAD || modoMenu == SELVELOCIDAD)
            id_grado = 2;
         
         if (modoMenu == SELCAMARA)
         {
            id_cam = 2;
            camara[id_cam] -> setProyeccion();
            std::cout << "Camara 3 activada\n";

            change_observer();
            change_projection(0);
         }
         
         break;

      case '4':
   
         if (modoMenu == GRADOSLIBERTAD || modoMenu == SELVELOCIDAD)
            id_grado = 3;
         break;

      case '5':
   
         if (modoMenu == GRADOSLIBERTAD || modoMenu == SELVELOCIDAD)
            id_grado = 4;
         break;

      case '6':
   
         if (modoMenu == GRADOSLIBERTAD || modoMenu == SELVELOCIDAD)
            id_grado = 5;
         break;

      case '7':
   
         if (modoMenu == GRADOSLIBERTAD || modoMenu == SELVELOCIDAD)
            id_grado = 6;
         break;

      case 'P':

         if (modoMenu == SELVISUALIZACION)
         {
            for (int i = 0; i < objetos.size(); i++)
            objetos[i]->cambiar_puntos();

            ovn->cambiar_puntos();
            //glDisable(GL_LIGHTING);
         }

         if (glIsEnabled(GL_LIGHTING))
            animacion_puntal = !animacion_puntal;
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

            glDisable(GL_LIGHTING);
         }
         else
         {
            modoMenu = SELVELOCIDAD;
         }
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

         if (modoMenu == SELVELOCIDAD)
         {
            switch(id_grado)
            {
               case -1:
               std::cout << "Aumentando velocidad general\n";
                  for (int i = 0; i < v.size(); i++)
                     v[i]++;
                  break;

               case 1:
                  v[0]++;
                  break;

               case 2:
                  v[1]++;
                  break;

               case 3:
                  v[2]++;
                  break;

               case 4:
                  v[3]++;
                  break;
               
               case 5:
                  v[4]++;
                  break;

               case 6:
                  v[5]++;
                  break;

               case 7:
                  v[6]++;
                  break;
               
               case 8:
                  v[7]++;
                  break;

               case 9:
                  v[8]++;
                  break;

               case 0:
                  v[9]++;
                  break;
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

         if (modoMenu == SELVELOCIDAD)
         {
            switch(id_grado)
            {
               case -1:
                  for (int i = 0; i < v.size(); i++)
                  {
                     if (v[i] > 0)
                        v[i]--;
                  }
                  break;

               case 1:
                  if (v[0] > 0)
                     v[0]--;
                  break;

               case 2:
                  if (v[1] > 0)
                     v[1]--;
                  break;

               case 3:
                  if (v[2] > 0)
                     v[2]--;
                  break;

               case 4:
                  if (v[3] > 0)
                     v[3]--;
                  break;
               
               case 5:
                  if (v[4] > 0)
                     v[4]--;
                  break;

               case 6:
                  if (v[5] > 0)
                     v[5]--;
                  break;

               case 7:
                  if (v[6] > 0)
                     v[6]--;
                  break;

               case 8:
                  if (v[7] > 0)
                     v[7]--;
                  break;

               case 9:
                  if (v[8] > 0)
                     v[8]--;
                  break;

               case 0:
                  if (v[9] > 0)
                     v[9]--;
                  break;
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

      case 'W':
            posicion = posicion + camara[id_cam]->devolverDireccion();
            camara[id_cam]->mover(posicion(0), posicion(1), posicion(2));
         break;

      case 'E':
            posicion = posicion - camara[id_cam]->devolverDireccion();
            camara[id_cam]->mover(posicion(0), posicion(1), posicion(2));
         break;

      case 'X':
            camara[id_cam]->status();
         break;

      case 'J':
            camara[id_cam]->zoom(1.05);
            std::cout << "Zoom mas\n";
            change_projection(0);
         break;

      case 'K':
            camara[id_cam]->zoom(0.95);
            std::cout << "Zoom menos\n";
            change_projection(0);
         break;

      /*case 'H':
            posicion(1) = posicion(1)+10;
            camara[id_cam]->mover(posicion(0), posicion(1), posicion(2));
         break;

      case 'K':
            posicion(1) = posicion(1)-10;
            camara[id_cam]->mover(posicion(0), posicion(1), posicion(2));
         break;Tupla3f devolverDireccion();*/
         
            
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         camara[id_cam] -> girar(0.1, 0.0);//rotarYFirstPerson(0.1);
         break;
	   case GLUT_KEY_RIGHT:
         camara[id_cam] -> rotarYFirstPerson(-0.1);
         break;
	   case GLUT_KEY_UP:
         camara[id_cam] -> rotarXFirstPerson(-0.1);
         break;
	   case GLUT_KEY_DOWN:
         camara[id_cam] -> rotarXFirstPerson(0.1);
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}
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
   //const float wx = float(Height)*ratio_xy ;
   camara[id_cam] -> setProyeccion();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10; ///10;
   Height = newHeight/10; ///10;
   for (int i = 0; i < camara.size(); i++)
      camara[i] -> actualizarRatio(-Width/2, Width/2, -Height/2, Height/2, Front_plane, Back_plane);
   change_projection( float(newHeight)/float(newWidth) );;
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara[id_cam])
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   camara[id_cam] -> setObserver();
   //glGetFloatv(GL_MODELVIEW_MATRIX, m_vista);
}

void Escena::animarModeloJerarquico()
{
   if (animacion_activa)
   {
      ovn->aumentar_r_luces(v[0]*1.5 *(v[0]>0));
      ovn->aumentar_foco_y(-v[1]*0.5 *(v[1]>0));

      if (contador[0] >= 90)
      {
         sentido[0] = -sentido[0];
         contador[0] = 0;
      }
         
      if (contador[1] >= 40)
      {
         sentido[1] = -sentido[1];
         contador[1] = 0;
      }

      ovn->aumentar_h_gancho(v[2]*sentido[0]*0.3 *(v[2]>0));
      ovn->aumentar_foco_x(v[3]*sentido[1]*0.5 *(v[3]>0));

      contador[0] += v[2]*0.3;
      contador[1] += v[3]*0.5;

      ovn->aumentar_ballena(sentido[2]*v[4]*0.2 *(v[4]>0));
      ovn->aumentar_ballena_x(sentido[3]*v[5]*0.5 *(v[5]>0));

      if (contador[4] <= 90)
         ovn->aumentar_ballena_y(sentido[4]*(sentido[4]<=90)*v[6]*0.2 *(v[6]>0));

      contador[2] += 1*v[4];

      if (contador[2] >= 500)
      {
         contador[2] = 0;
         sentido[2] = -sentido[2];
      }

      contador[3] += v[5]*0.5;

      if (contador[3] >= 90)
      {
         contador[3] = 0;
         sentido[3] = -sentido[3];
      }

      contador[4] += v[5]*0.2;

      if (contador[4] >= 100)
      {
         contador[4] = 0;
         sentido[4] = -sentido[4];
      }

      //animacion_luz = v[7]*0.5;
      lucesdir[0].variarAnguloAlpha(0.01*v[7]);
      animacion_luz_2 += v[7]*animacion_puntal;
      animacion_tierra += v[8]*0.1;
      animacion_luna += v[9]*0.2;
   }
}

void Escena::obtenerCoordenadas(int id)
{
   GLfloat matrixMV[16];
   glGetFloatv(GL_MODELVIEW_MATRIX, matrixMV);

   pos_objetos[id] = Tupla3f{matrixMV[12], matrixMV[13], matrixMV[14]};

   //std::cout << "Coordenadas " << xCenterTriangle << ", " << yCenterTriangle << ", " << zCenterTriangle << "\n";
}

void Escena::ratonMovido ( int x, int y )
{
   if ( estadoRaton)
   {
      camara[id_cam]->girar((float)(x-xant)/100, (float)(y-yant)/100);

      std::cout << "Muevo " << x-xant << " " << y-yant << std::endl;
      xant = x;
      yant = y;
   }
}

void Escena::clickRaton( int boton, int estado, int x, int y)
{
   if ( boton == GLUT_RIGHT_BUTTON )
   {
      xant = x; yant = y;

      if (estado == GLUT_DOWN)
      {
         estadoRaton = true;
      }

      else
      {
         estadoRaton = false;
      }
   }

   else if ( boton == GLUT_LEFT_BUTTON)
   {
      //std::cout << "x = " << x << ", y = " << y << std::endl;

      if (estado != GLUT_DOWN)
      {
         dibuja_seleccion();

         GLint viewport[4];
         GLfloat pixels[3];
         glGetIntegerv(GL_VIEWPORT, viewport);
         glReadPixels(x, viewport[3]-y, 1, 1, GL_RGB, GL_FLOAT, (void*)pixels);
         Tupla3f color(pixels[0], pixels[1], pixels[2]);

         //std::cout << "Color = " << color << std::endl;
         int id = getColorObjeto(color);

         if (id == -1)
            camara[id_cam]->unlock();
         else
            camara[id_cam]->lock(pos_objetos[id]);

         std::cout << "gotcha " << id << "\n";
         std::cout << "pos " << pos_objetos[id] << "\n";
      }
   }
}

int Escena::getColorObjeto(Tupla3f color)
{

   int salida = -1;

   std::cout << "Color es " << color << std::endl;

   for (int i = 0; i < col_objetos.size(); i++)
   {
      if (color(0) == col_objetos[i](0) && color(1) == col_objetos[i](1) && color(2) == col_objetos[i](2))
      {
         salida = i;
         i = col_objetos.size();
      }
   }

   return salida;
}