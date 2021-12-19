#ifndef GANCHO_H_INCLUDED
#define GANCHO_H_INCLUDED

#include "aux.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"

class Gancho
{
    private:
        Cilindro* cable;
        Cilindro* lentes;
        Cono* antenaCono;
        Cono* antenaConoR;
        Cilindro* antenaCilindro;
        Esfera* antenaEsfera;

    protected:
        const float r_max = 90;
        const float r_min = 0;
        float r_x = 45;
        float r_y = 0;
        
    public:
        Gancho(Cilindro *len, Cilindro *cab, Cono *ant, Cono *antR, Cilindro *antCil, Esfera *antEsf);
        void draw();
        void aumentar_foco_x(float aumento);
        void aumentar_foco_y(float aumento);
} ;


#endif
