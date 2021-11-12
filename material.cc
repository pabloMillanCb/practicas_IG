#include "material.h"

Material::Material()
{

}

Material::Material(Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float mbrillo)
{
    difuso = mdifuso;
    especular = mespecular;
    ambiente = mambiente;
    brillo = mbrillo;
}

void Material::aplicar()
{
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &difuso(0));
    glMaterialfv(GL_FRONT, GL_SPECULAR, &especular(0));
    glMaterialfv(GL_FRONT, GL_AMBIENT, &ambiente(0));
    glMaterialfv(GL_FRONT, GL_SHININESS, &brillo);
}