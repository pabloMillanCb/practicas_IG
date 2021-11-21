#ifndef OVNI_H_INCLUDED
#define OVNI_H_INCLUDED

#include "aux.h"
#include "cono.h"
#include "esfera.h"
#include "cubo.h"
#include "lucesovni.h"
#include "gancho.h"

class Ovni
{
    private:
        Esfera* cabina;
        Cono* cuerpo;
        LucesOvni luces;
        Gancho inferior;

    protected:
        float h_gancho = 10;
        float r_luces;

        const float max_h_gancho = 75.0;
        const float min_h_gancho = 10.0;
        const float max_r_foco_x = 70.0;
        
    public:
        Ovni();
        void draw();
        void aumentar_foco_x(float aumento);
        void aumentar_foco_y(float aumento);
        void aumentar_h_gancho(float aumento);
        void aumentar_r_luces(float aumento);
        void gradosLibertad(int i, float aumento);

        void cambiar_solido();
        void cambiar_lineas();
        void cambiar_puntos();
        void cambiar_ajedrez();

        void activar_inmediato();
        void activar_diferido();
} ;


#endif
