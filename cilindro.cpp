#include "aux.h"
#include "malla.h"
#include "cilindro.h"

Cilindro::Cilindro(float radio, float altura, int num_instancias)
{
    v.push_back(Tupla3f(radio, altura, 0));
    v.push_back(Tupla3f(radio, 0, 0));
    int size_perfil = v.size();

    crearMalla(v, num_instancias, 1, true, true);
    generarColores();
}