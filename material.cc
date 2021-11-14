#include "material.h"

Material::Material()
{
    difuso = Tupla4f(0.0, 0.0, 0.0, 0.0);
    especular = Tupla4f(0.0, 0.0, 0.0, 0.0);
    ambiente = Tupla4f(0.0, 0.0, 0.0, 0.0);
    brillo = 100.0;
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
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,difuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &brillo);
}