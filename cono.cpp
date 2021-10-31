#include "aux.h"
#include "malla.h"
#include "cono.h"

Cono::Cono(float r, float h, int num_instancias)
{
    v.push_back(Tupla3f(0, h, 0));
    v.push_back(Tupla3f(r, 0, 0));
    int size_perfil = v.size();

    crearMalla(v, num_instancias, 1, true, true);
    generarColores();
}