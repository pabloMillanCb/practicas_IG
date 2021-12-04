#include "textura.h"
#include<iostream>

Textura::Textura(std::string archivo)
{
    jpg::Imagen * pimg = NULL;

    pimg = new jpg::Imagen(archivo);

    width = pimg->tamX();
    height = pimg->tamY();
    
    for (int i = height - 1 ; i >= 0 ; i--){ //CAMBIAR ESTO
      for (int j = 0 ; j < width ; j++){
         unsigned char * d = pimg->leerPixel(j, i);
         data.push_back(d[0]); // R
         data.push_back(d[1]); // G
         data.push_back(d[2]); // B
      }
   }
}

void Textura::activar()
{
    glEnable(GL_TEXTURE_2D);

    if (textura_id == 0)
    {
        glGenTextures(1, &textura_id);
        glBindTexture(GL_TEXTURE_2D, textura_id);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data.data());
    }

    else
    {
        glBindTexture(GL_TEXTURE_2D, textura_id);
    }
}