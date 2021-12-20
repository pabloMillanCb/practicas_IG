#include "aux.h"
#include "malla.h"
#include<iostream>

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'drawElements'

void Malla3D::drawSeleccion()
{
   glEnableClientState( GL_VERTEX_ARRAY );
   glVertexPointer( 3, GL_FLOAT , 0, v.data() ) ;

   glColorPointer(3, GL_FLOAT, 0, &colorSeleccion[0]);
   //glColor3ub (0.0 ,1.0 ,0.0);

   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   drawElements( GL_TRIANGLES , draw_size*3, GL_UNSIGNED_INT , f.data());
}

void Malla3D::draw_ModoInmediato()
{

  // visualizar la malla usando drawElements,
  // completar (práctica 1)
  // ...
   glEnableClientState( GL_VERTEX_ARRAY );
   // indicar el formato y la dirección de memoria del array de vértices
   // (son tuplas de 3 valores float, sin espacio entre ellas)
   glVertexPointer( 3, GL_FLOAT , 0, v.data() ) ;
   // visualizar, indicando: tipo de primitiva, número de índices,
   // tipo de los índices, y dirección de la tabla de índices

   if (glIsEnabled(GL_LIGHTING))
   {
      dibujar[0] = true;
      dibujar[1] = false;
      dibujar[2] = false;

      glEnableClientState( GL_NORMAL_ARRAY );
      glNormalPointer(GL_FLOAT, 0, nv.data());
   }

   if (textura != nullptr && !ct.empty())
   {
      glEnableClientState( GL_TEXTURE_COORD_ARRAY );
      glTexCoordPointer( 2, GL_FLOAT , 0, ct.data());
      textura -> activar();
   }

   if (dibujar[0])
   {
      glColorPointer(3, GL_FLOAT, 0, &colorArray[0] + prelock);
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      drawElements( GL_TRIANGLES , draw_size*3, GL_UNSIGNED_INT , f.data());
   }
      
   if (dibujar[1])
   {
      glColorPointer(3, GL_FLOAT, 0, &colorArray[0]+1 );
      glPointSize(7);
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      drawElements( GL_TRIANGLES , draw_size*3, GL_UNSIGNED_INT , f.data());
   }
      
   if (dibujar[2] || (isLocked))
   {
      glColorPointer(3, GL_FLOAT, 0, &colorArray[0]+2 );
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      drawElements( GL_TRIANGLES , draw_size*3, GL_UNSIGNED_INT , f.data());
   }
      
   // deshabilitar array de vértices
   glDisableClientState( GL_VERTEX_ARRAY );

   //Deshabilitar array de normales
   if (glIsEnabled(GL_LIGHTING))
      glDisableClientState( GL_NORMAL_ARRAY);

   if (textura != nullptr && !ct.empty())
   {
      glDisable(GL_TEXTURE_2D);
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
   }

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
      id_vbo_color = CrearVBO(GL_ARRAY_BUFFER, colorArray.size()*sizeof(float), colorArray.data());
   if (id_vbo_color2 == 0)
      id_vbo_color2 = CrearVBO(GL_ARRAY_BUFFER, colorArray.size()*sizeof(float), colorArray.data()+1);
   if (id_vbo_color3 == 0)
      id_vbo_color3 = CrearVBO(GL_ARRAY_BUFFER, colorArray.size()*sizeof(float), colorArray.data()+2);
   if (id_vbo_nor == 0)
      id_vbo_nor = CrearVBO(GL_ARRAY_BUFFER, nv.size()*3*sizeof(float), nv.data());

   if (glIsEnabled(GL_LIGHTING))
   {
      glEnableClientState(GL_NORMAL_ARRAY);
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_nor);
      glNormalPointer(GL_FLOAT,0, 0 );
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }

   if (textura != nullptr && !ct.empty())
   {
      glEnable(GL_TEXTURE_2D);
      glEnableClientState( GL_TEXTURE_COORD_ARRAY );
      glTexCoordPointer( 2, GL_FLOAT , 0, ct.data());
      textura -> activar();
   }

   /*if (glIsEnabled(GL_TEXTURE_2D) && !ct.empty())
   {
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glBindBuffer( GL_ARRAY_BUFFER , id_vbo_text );
      glTexCoordPointer(2, GL_FLOAT, 0, 0);
      textura->activar();
   }*/

   glBindBuffer( GL_ARRAY_BUFFER , id_vbo_ver ); // activar VBO de vérti-ces
   glVertexPointer( 3, GL_FLOAT , 0, 0 ); // especifica formato y off-set (=0)
   glBindBuffer( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vér-tices.
   glEnableClientState( GL_VERTEX_ARRAY ); // habilitar tabla de vér-tices

   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri );// activar VBOde triángulos
   
   if (dibujar[0])
   {
      if (prelock)
         glBindBuffer( GL_ARRAY_BUFFER , id_vbo_color2 );
      else
         glBindBuffer( GL_ARRAY_BUFFER , id_vbo_color );
      glColorPointer(3, GL_FLOAT, 0, 0);
      glBindBuffer( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vér-tices.

      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      drawElements( GL_TRIANGLES , draw_size*3, GL_UNSIGNED_INT , 0);
   }
      
   if (dibujar[1])
   {
      glBindBuffer( GL_ARRAY_BUFFER , id_vbo_color2 );
      glColorPointer(3, GL_FLOAT, 0, 0);
      glBindBuffer( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vér-tices.

      std::cout <<" modo puntos\n";
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      drawElements( GL_TRIANGLES , draw_size*3, GL_UNSIGNED_INT , 0);
   }
      
   if (dibujar[2] || (isLocked))
   {
      glBindBuffer( GL_ARRAY_BUFFER , id_vbo_color3 );
      glColorPointer(3, GL_FLOAT, 0, 0);
      glBindBuffer( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vér-tices.

      std::cout <<" modo lineas\n";
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      drawElements( GL_TRIANGLES , draw_size*3, GL_UNSIGNED_INT , 0);
   }
   

   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 ); // desactivar VBOde triángulos
   // desactivar uso de array de vértices
   glDisableClientState( GL_VERTEX_ARRAY );

   if (glIsEnabled(GL_LIGHTING))
   {
      glDisableClientState(GL_NORMAL_ARRAY);
   }

   if (textura != nullptr && !ct.empty())
   {
      glDisable(GL_TEXTURE_2D);
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      //std::cout << "deshabilita textura\n";
   }
}

void Malla3D::draw_ModoAjedrez()
{
   if (modo_dibujado == INMEDIATO)
   {
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
   if (seleccion)
   {
      drawSeleccion();
   }

   /*else if (isLocked || prelock)
   {
      std::cout << "Estoy seleccionado\n";
      if (glIsEnabled(GL_LIGHTING))
      {
         glDisable(GL_LIGHTING);
         drawSeleccion();
         glEnable(GL_LIGHTING);
      }
      else
         drawSeleccion();
   }*/

   else
   {

      if (glIsEnabled(GL_LIGHTING))
      {
         if (isLocked)
            m.aplicar_seleccion2();
         else if (prelock)
            m.aplicar_seleccion();
         else
            m.aplicar();

         modo_ajedrez = false;
      }

      if (modo_ajedrez)
         draw_ModoAjedrez();
      else if (modo_dibujado == INMEDIATO)
         draw_ModoInmediato();
      else if (modo_dibujado == DIFERIDO)
         draw_ModoDiferido();
   }
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

void Malla3D::activar_luz()
{
   modo_dibujado = LUZ;
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

void Malla3D::setMaterial(Material &mat)
{
   m = mat;
}

void Malla3D::generarColores()
{
   for (int i = 0; i < v.size()+5; i++)
   {
      colorRojo.push_back(1); colorRojo.push_back(0); colorRojo.push_back(0);
      colorVerde.push_back(0); colorVerde.push_back(1); colorVerde.push_back(0);
      colorArray.push_back(1); colorArray.push_back(0); colorArray.push_back(1);
   }
}

void Malla3D::setColorSeleccion(Tupla3f c)
{
   for (int i = 0; i < v.size()+2; i++)
   {
      colorSeleccion.push_back(c(0));
      colorSeleccion.push_back(c(1));
      colorSeleccion.push_back(c(2));
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

void Malla3D::mezclarCaras()
{
   std::vector<Tupla3i> aux ;

   //Reordenar vector de triángulos, colocar caras pares al principio e impares al final
    for (int i = 0; i < f.size(); i+=2)
        aux.push_back(f[i]);
    for (int i = 1; i < f.size(); i+=2)
        aux.push_back(f[i]);

    f = aux;
    draw_size = f.size();
    draw_size_a1 = draw_size/2 + (draw_size%2 == 1);
    draw_size_a2 = draw_size/2;
}

void Malla3D::invertir_caras()
{
   for (int i = 0; i < f.size(); i++)
   {
      float aux = f[i](0);
      f[i](0) = f[i](1);
      f[i](1) = aux;
   }

   calcular_normales();
}

void Malla3D::calcular_normales()
{
   Tupla3f normal(0.0, 0.0, 0.0);

   nv.clear();
   for (int i = 0; i < v.size(); i++) //Se inicializa nv a 0 SI EMPIEZA A FALLAR ALGO MIRAR AQUÍ
   {
      nv.push_back(Tupla3f(0.0, 0.0, 0.0));
   }

   for (int i = 0; i < f.size(); i++) //Se recorre el vector de caras, se calcula
   {
      normal = vectorNormal(f[i]);

      nv[ f[i](0) ] = nv[ f[i](0) ] + normal;
      nv[ f[i](1) ] = nv[ f[i](1) ] + normal;
      nv[ f[i](2) ] = nv[ f[i](2) ] + normal;
   }

   for (int i = 0; i < nv.size(); i++)
   {
      Tupla3f aux = normalizar(nv[i]);
      //nv[i] = nv[i].normalized();
   }
}

Tupla3f Malla3D::vectorNormal(Tupla3i c)
{
   Tupla3f a = v[c(1)] - v[c(0)], b = v[c(2)] - v[c(0)];
   return a.cross(b);
}

Tupla3f Malla3D::normalizar(Tupla3f t)
{
   float modulo = sqrt(pow(t(0),2) + pow(t(1),2) + pow(t(2),2));
   return t*(1/modulo);
}

void Malla3D::setTextura(Textura &txt)
{
   textura = &txt;
}

void Malla3D::activar_seleccion()
{
   seleccion = true;
}

void Malla3D::desactivar_seleccion()
{
   seleccion = false;
}

void Malla3D::activar_lock()
{
   isLocked = true;
}

void Malla3D::desactivar_lock()
{
   isLocked = false;
}

bool Malla3D::get_lock()
{
   return isLocked;
}

void Malla3D::activar_prelock()
{
   prelock = true;
}

void Malla3D::desactivar_prelock()
{
   prelock = false;
}