#ifndef OVNI_H_INCLUDED
#define OVNI_H_INCLUDED

#include "aux.h"
#include "cono.h"
#include "esfera.h"
#include "cubo.h"
#include "lucesovni.h"
#include "gancho.h"
#include "laboon.h"

class Ovni
{
    private:
        Esfera* cabina;
        Cono* cuerpo;
        Cono* abductor;
        Cono* abductorR;
        LucesOvni luces;
        Gancho inferior;
        Laboon laboon;

    protected:
        float h_gancho = 10;
        float r_luces;
        float ctr_ballena = 0;
        float x_ballena = 0;
        float y_ballena = 0;

        const float max_h_gancho = 75.0;
        const float min_h_gancho = 10.0;
        const float max_r_foco_x = 70.0;

        const float escalado_max = 0.45;
        const float h_ballena_max = 70;
        const float ctr_ballena_max = 30;
        const float x_ballena_max = 30;


        
    public:
        Ovni();
        void draw();
        void aumentar_foco_x(float aumento);
        void aumentar_foco_y(float aumento);
        void aumentar_h_gancho(float aumento);
        void aumentar_r_luces(float aumento);
        void aumentar_ballena(float aumento);
        void aumentar_ballena_x(float aumento);
        void aumentar_ballena_y(float aumento);
        void gradosLibertad(int i, float aumento);

        void cambiar_solido();
        void cambiar_lineas();
        void cambiar_puntos();
        void cambiar_ajedrez();

        void activar_inmediato();
        void activar_diferido();
} ;


#endif
