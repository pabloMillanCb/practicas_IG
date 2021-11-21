#ifndef GANCHO_H_INCLUDED
#define GANCHO_H_INCLUDED

#include "aux.h"
#include "cilindro.h"

class Gancho
{
    private:
        Cilindro* foco;
        Cilindro* cable;

    protected:
        const float r_max = 130;
        const float r_min = 90;
        float r_x = 90;
        float r_y = 0;
        
    public:
        Gancho();
        void draw();
        void aumentar_foco_x(float aumento);
        void aumentar_foco_y(float aumento);

        void cambiar_solido();
        void cambiar_lineas();
        void cambiar_puntos();
        void cambiar_ajedrez();

        void activar_inmediato();
        void activar_diferido();
} ;


#endif
