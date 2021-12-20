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

    difuso_s2 = (mdifuso)*0.5;
    especular_s2 = (mespecular)*0.5;
    ambiente_s2 = (mambiente)*0.5;

    //difuso_s = (mdifuso)*1.2;
    //especular_s = (mespecular)*1.2;
    //ambiente_s = (mambiente)*1.2;
}

void Material::aplicar()
{
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difuso);
    glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT, GL_SHININESS, &brillo);
}

void Material::aplicar_seleccion()
{
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difuso_s);
    glMaterialfv(GL_FRONT, GL_SPECULAR, especular_s);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente_s);
    glMaterialfv(GL_FRONT, GL_SHININESS, &brillo);
}

void Material::aplicar_seleccion2()
{
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difuso_s2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, especular_s2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente_s2);
    glMaterialfv(GL_FRONT, GL_SHININESS, &brillo);
}

void Material::operator=(Material &m)
{
    difuso = m.difuso;
    especular = m.especular;
    ambiente = m.ambiente;
    brillo = m.brillo;
}

void Material::aumentar_brillo(float f)
{
    brillo += f;
}