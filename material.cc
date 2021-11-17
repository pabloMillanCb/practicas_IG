#include "material.h"
#include <iostream>

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
    std::cout << "aplicando material con valor " << difuso(0) << std::endl;

    glMaterialfv(GL_FRONT, GL_DIFFUSE, difuso);
    glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT, GL_SHININESS, &brillo);
}

void Material::operator=(Material &m)
{
    difuso = m.difuso;
    especular = m.especular;
    ambiente = m.ambiente;
    brillo = m.brillo;
}