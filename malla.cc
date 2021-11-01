#include "aux.h"
#include "malla.h"
#include<iostream>

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'drawElements'

void Malla3D::draw_ModoInmediato()
{

   std::cout << "modo inmediato\n";
  // visualizar la malla usando drawElements,
  // completar (práctica 1)
  // ...
   glEnableClientState( GL_VERTEX_ARRAY );
   // indicar el formato y la dirección de memoria del array de vértices
   // (son tuplas de 3 valores float, sin espacio entre ellas)
   glVertexPointer( 3, GL_FLOAT , 0, v.data() ) ;
   // visualizar, indicando: tipo de primitiva, número de índices,
   // tipo de los índices, y dirección de la tabla de índices

   glColorPointer(3, GL_FLOAT, 0, &colorArray[0] );

   if (dibujar[0])
   {
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      std::cout << f.data() << std::endl;
      drawElements( GL_TRIANGLES , draw_size*3, GL_UNSIGNED_INT , f.data());
   }
      
   if (dibujar[1])
   {
      glPointSize(7);
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINTS);
      drawElements( GL_POINTS , draw_size*3, GL_UNSIGNED_INT , f.data());
   }
      
   if (dibujar[2])
   {
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      drawElements( GL_LINE_LOOP , draw_size*3, GL_UNSIGNED_INT , f.data());
   }
      
   // deshabilitar array de vértices
   glDisableClientState( GL_VERTEX_ARRAY );

}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'drawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido()
{
   if (id_vbo_ver == 0)
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), v.data());
   if (id_vbo_tri == 0)
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*3*sizeof(int), f.data());
   if (id_vbo_color == 0)
      id_vbo_color = CrearVBO(GL_ARRAY_BUFFER, colorArray.size()*sizeof(float), colorArray.data()+1);

   glBindBuffer( GL_ARRAY_BUFFER , id_vbo_ver ); // activar VBO de vérti-ces
   glVertexPointer( 3, GL_FLOAT , 0, 0 ); // especifica formato y off-set (=0)
   glBindBuffer( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vér-tices.
   glEnableClientState( GL_VERTEX_ARRAY ); // habilitar tabla de vér-tices


   glBindBuffer( GL_ARRAY_BUFFER , id_vbo_color );
   glColorPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vér-tices.

   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri );// activar VBOde triángulos
   
   if (dibujar[0])
   {
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      drawElements( GL_TRIANGLES , draw_size*3, GL_UNSIGNED_INT , 0);
   }
      
   if (dibujar[1])
   {
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINTS);
      drawElements( GL_TRIANGLES , draw_size*3, GL_UNSIGNED_INT , 0);
   }
      
   if (dibujar[2])
   {
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      drawElements( GL_TRIANGLES , draw_size*3, GL_UNSIGNED_INT , 0);
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

      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glColorPointer(3, GL_FLOAT, 0, &colorRojo[0] );
      drawElements( GL_TRIANGLES , draw_size_a1*3, GL_UNSIGNED_INT , f.data());
      glColorPointer(3, GL_FLOAT, 0, &colorVerde[0] );
      drawElements( GL_TRIANGLES , draw_size_a2*3, GL_UNSIGNED_INT , f.data() + f.size()/2);
   
   }

   else if (modo_dibujado == DIFERIDO)
   {
      if (id_vbo_ver == 0)
         id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), v.data());
      if (id_vbo_tri_1 == 0)
         id_vbo_tri_1 = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, (f.size()/2 + f.size()%2)*3*sizeof(int), f.data());
      if (id_vbo_tri_2 == 0)
         id_vbo_tri_2 = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, (f.size()/2)*3*sizeof(int), f.data() + f.size()/2);
      if (id_vbo_color2 == 0)
         id_vbo_color2 = CrearVBO(GL_ARRAY_BUFFER, colorVerde.size()*sizeof(float), colorVerde.data());
      if (id_vbo_color3 == 0)
         id_vbo_color3 = CrearVBO(GL_ARRAY_BUFFER, colorRojo.size()*sizeof(float), colorRojo.data());

      glBindBuffer( GL_ARRAY_BUFFER , id_vbo_ver ); // activar VBO de vérti-ces
      glVertexPointer( 3, GL_FLOAT , 0, 0 ); // especifica formato y off-set (=0)
      glBindBuffer( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vér-tices.
      glEnableClientState( GL_VERTEX_ARRAY ); // habilitar tabla de vér-tices

      //Imprimir caras verdes
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color2);
      glColorPointer(3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0);
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri_1 );
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      drawElements( GL_TRIANGLES , draw_size_a1*3, GL_UNSIGNED_INT , 0);

      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 ); //desactivar VBO

      //Imprimir caras rojas
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color3);
      glColorPointer(3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0);
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri_2 );
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      drawElements( GL_TRIANGLES , draw_size_a2*3, GL_UNSIGNED_INT , 0);

      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 ); //desactivar VBOcolorRojo
   }
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw()
{
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

Tupla3f Malla3D::rotarEjeX(Tupla3f p, float radianes)
{
   Tupla3f salida;

   salida(0) = p(0);
   salida(1) = cos(radianes)*p(1) - sin(radianes)*p(2);
   salida(2) = sin(radianes)*p(1) + cos(radianes)*p(2);

   return salida;
}

Tupla3f Malla3D::rotarEjeY(Tupla3f p, float radianes)
{
   Tupla3f salida;

   salida(0) = cos(radianes)*p(0) + sin(radianes)*p(2);
   salida(1) = p(1);
   salida(2) = -sin(radianes)*p(0) + cos(radianes)*p(2);

   return salida;
}

Tupla3f Malla3D::rotarEjeZ(Tupla3f p, float radianes)
{
   Tupla3f salida;

   salida(0) = cos(radianes)*p(0) - sin(radianes)*p(1);
   salida(1) = sin(radianes)*p(0) + cos(radianes)*p(1);
   salida(2) = p(2);

   return salida;
}

Tupla3f Malla3D::rotarEje(Tupla3f punto, float radianes, int eje)
{
   Tupla3f salida;

   if (eje == 0)
      salida = rotarEjeX(punto, radianes);
   else if (eje == 1)
      salida = rotarEjeY(punto, radianes);
   else if (eje == 2)
      salida = rotarEjeZ(punto, radianes);
   
   return salida;
}

void Malla3D::generarColores()
{
   for (int i = 0; i < v.size(); i++)
   {
      colorRojo.push_back(1); colorRojo.push_back(0); colorRojo.push_back(0);
      colorVerde.push_back(0); colorVerde.push_back(1); colorVerde.push_back(0);
      colorArray.push_back(1); colorArray.push_back(0); colorArray.push_back(1);
   }
}

bool Malla3D::compararPuntos(Tupla3f a, Tupla3f b)
{
   return a(0) == b(0) && a(1) == b(1) && a(2) == b(2);
}

Tupla3f Malla3D::proyectarPunto(Tupla3f p, int eje)
{
   return Tupla3f( p(eje)*(eje==0), p(eje)*(eje==1), p(eje)*(eje==2) );
}

void Malla3D::drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices)
{
   glDrawElements(mode, count, type, indices);
}