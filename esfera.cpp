#include "aux.h"
#include "malla.h"
#include "esfera.h"

Esfera::Esfera (const int num_vert_perfil, const int num_instancias_perf, const float radio)
{
    Tupla3f p(0.0, radio, 0.0);

    for (int i = 0; i < num_vert_perfil; i++)
    {
        v.push_back(p);
        p = rotarEjeZ(p, M_PI/num_vert_perfil);
    }

    int size_perfil = v.size();
    crearMalla(v, num_instancias_perf, 1, true, true);
    generarColores();
}