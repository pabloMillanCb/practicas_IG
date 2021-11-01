#include "aux.h"
#include "malla.h"
#include "cilindro.h"

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio)
{
    for (float i = 0; i < altura; i += altura/num_vert_perfil)
        v.push_back(Tupla3f(radio, i, 0));
    
    v.push_back(Tupla3f(radio, altura, 0));

    int size_perfil = v.size();
    crearMalla(v, num_instancias_perf, 1, true, true);
    generarColores();
}