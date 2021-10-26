#include "aux.h"
#include "malla.h"
#include "cilindro.h"

Cilindro::Cilindro(float r, float h, int num_instancias)
{
    v.push_back(Tupla3f(r, h, 0));
    v.push_back(Tupla3f(r, 0, 0));
    int size_perfil = v.size();

    crearMalla(v, num_instancias, true, true);
    //crearTapas(size_perfil, num_instancias, true, true);
    generarColores();
}