#include "aux.h"
#include "malla.h"
#include "cono.h"

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio)
{

    float r = radio -radio/num_vert_perfil , h = altura/num_vert_perfil;

    v.push_back(Tupla3f(radio, 0, 0));

    while (r > 0 && h < altura)
    {
        v.push_back(Tupla3f(r, h, 0));

        r -= radio/num_vert_perfil;
        h += altura/num_vert_perfil;
    }
    
    v.push_back(Tupla3f(0, altura, 0));

    int size_perfil = v.size();
    crearMalla(v, num_instancias_perf, 1, true, true);
    generarColores();
}