#include "aux.h"
#include "malla.h"
#include "cono.h"

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio)
{
    v.push_back(Tupla3f(0, altura, 0));
    v.push_back(Tupla3f(radio, 0, 0));
    int size_perfil = v.size();

    crearMalla(v, num_instancias_perf, 1, true, true);
    generarColores();
}