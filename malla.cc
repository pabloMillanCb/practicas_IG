#include "aux.h"
#include "malla.h"
#include<iostream>

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato()
{

   std::cout << "modo inmediato\n";
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)
  // ...
   glEnableClientState( GL_VERTEX_ARRAY );
   // indicar el formato y la dirección de memoria del array de vértices
   // (son tuplas de 3 valores float, sin espacio entre ellas)
   glVertexPointer( 3, GL_FLOAT , 0, v.data() ) ;
   // visualizar, indicando: tipo de primitiva, número de índices,
   // tipo de los índices, y dirección de la tabla de índices

   glColorPointer(3, GL_FLOAT, 0, colorArray );

   if (dibujar[0])
   {
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glDrawElements( GL_TRIANGLES , f.size ()*3, GL_UNSIGNED_INT , f.data() );
   }
      
   if (dibujar[1])
   {
      glPointSize(7);
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINTS);
      glDrawElements( GL_POINTS , f.size ()*3, GL_UNSIGNED_INT , f.data() );
   }
      
   if (dibujar[2])
   {
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glDrawElements( GL_LINE_LOOP , f.size ()*3, GL_UNSIGNED_INT , f.data() );
   }
      
   // deshabilitar array de vértices
   glDisableClientState( GL_VERTEX_ARRAY );

}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido()
{

   std::cout << "modo diferido\n";

   if (id_vbo_ver == 0)
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), v.data());
   if (id_vbo_tri == 0)
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*3*sizeof(int), f.data());

   glBindBuffer( GL_ARRAY_BUFFER , id_vbo_ver ); // activar VBO de vérti-ces
   glVertexPointer( 3, GL_FLOAT , 0, 0 ); // especifica formato y off-set (=0)
   glBindBuffer( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vér-tices.
   glEnableClientState( GL_VERTEX_ARRAY ); // habilitar tabla de vér-tices

   glColorPointer(3, GL_FLOAT, 0, colorArray );

   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri );// activar VBOde triángulos
   
   if (dibujar[0])
   {
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glDrawElements( GL_TRIANGLES , f.size ()*3, GL_UNSIGNED_INT , 0 );
   }
      
   if (dibujar[1])
   {
      glPointSize(7);
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINTS);
      glDrawElements( GL_POINTS , f.size ()*3, GL_UNSIGNED_INT , 0 );
   }
      
   if (dibujar[2])
   {
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glDrawElements( GL_LINE_LOOP , f.size ()*3, GL_UNSIGNED_INT , 0 );
   }

   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 ); // desactivar VBOde triángulos
   // desactivar uso de array de vértices
   glDisableClientState( GL_VERTEX_ARRAY );
}

void Malla3D::draw_ModoAjedrez()
{
   if (modo_dibujado == INMEDIATO)
   {
      std::cout << "modo inmediato\n";
      glEnableClientState( GL_VERTEX_ARRAY );
      glVertexPointer( 3, GL_FLOAT , 0, v.data() );
      glColorPointer(3, GL_FLOAT, 0, colorArray );

      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glColorPointer(3, GL_FLOAT, 0, colorRojo );
      glDrawElements( GL_TRIANGLES , f2.size ()*3/2, GL_UNSIGNED_INT , f2.data() );
      glColorPointer(3, GL_FLOAT, 0, colorVerde );
      glDrawElements( GL_TRIANGLES , f2.size ()*3/2, GL_UNSIGNED_INT , f2.data() + f2.size()/2 );
   }

   else if (modo_dibujado == DIFERIDO)
   {
      std::cout << "modo diferido\n";

      if (id_vbo_ver == 0)
         id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), v.data());
      if (id_vbo_tri_1 == 0)
         id_vbo_tri_1 = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, (f.size()/2)*3*sizeof(int), f2.data());
      if (id_vbo_tri_2 == 0)
         id_vbo_tri_2 = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, (f.size()/2)*3*sizeof(int), f2.data() + f2.size()/2);

      glBindBuffer( GL_ARRAY_BUFFER , id_vbo_ver ); // activar VBO de vérti-ces
      glVertexPointer( 3, GL_FLOAT , 0, 0 ); // especifica formato y off-set (=0)
      glBindBuffer( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vér-tices.
      glEnableClientState( GL_VERTEX_ARRAY ); // habilitar tabla de vér-tices

      //Imprimir caras rojas
      glColorPointer(3, GL_FLOAT, 0, colorRojo );
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri_1 );
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glDrawElements( GL_TRIANGLES , f2.size ()*3/2, GL_UNSIGNED_INT , 0 ); //f2.size ()*3/2

      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 ); //desactivar VBO

      //Imprimir caras rojas
      glColorPointer(3, GL_FLOAT, 0, colorVerde );
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri_2 );
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glDrawElements( GL_TRIANGLES , f2.size ()*3/2, GL_UNSIGNED_INT , 0 );

      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 ); //desactivar VBOcolorRojo
   }

   glDisableClientState( GL_VERTEX_ARRAY );
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido D6UJUW

void Malla3D::draw()
{
   // completar .....(práctica 1)
   if (modo_ajedrez)
      draw_ModoAjedrez();
   else if (modo_dibujado == INMEDIATO)
      draw_ModoInmediato();
   else if (modo_dibujado == DIFERIDO)
      draw_ModoDiferido();
}

GLuint Malla3D::CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram )
{
   GLuint id_vbo ; // resultado: identificador de VBO
   glGenBuffers( 1, & id_vbo ); // crear nuevo VBO, obtener identificador (nunca 0)
   glBindBuffer( tipo_vbo , id_vbo ); // activar el VBO usando su identificador
// esta instrucción hace la transferencia de datos desde RAM hacia GPU
   glBufferData( tipo_vbo , tamanio_bytes , puntero_ram , GL_STATIC_DRAW );
   glBindBuffer( tipo_vbo , 0 ); // desactivación del VBO (activar 0)
   return id_vbo ;
}

void Malla3D:: cambiar_visibilidad()
{
   visible = !visible;
}

bool Malla3D:: es_visible()
{
   return visible;
}

void Malla3D::activar_inmediato()
{
   modo_dibujado = INMEDIATO;
}

void Malla3D::activar_diferido()
{
   modo_dibujado = DIFERIDO;
}

void Malla3D::cambiar_solido()
{
   dibujar[0] = !dibujar[0];
}
void Malla3D::cambiar_puntos()
{
   dibujar[1] = !dibujar[1];
}
void Malla3D::cambiar_lineas()
{
   dibujar[2] = !dibujar[2];
}

void Malla3D::cambiar_ajedrez()
{
   modo_ajedrez = !modo_ajedrez;
}
