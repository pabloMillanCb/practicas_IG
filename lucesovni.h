#ifndef LUCESOVNI_H_INCLUDED
#define LUCESOVNI_H_INCLUDED

#include "aux.h"
#include "esfera.h"

class LucesOvni
{
    private:
        Esfera * bola;

    protected:
        float r_bolas;
        
    public:
        LucesOvni();
        void draw();
        void aumentar_r_bolas(float aumento);

        void cambiar_solido();
        void cambiar_lineas();
        void cambiar_puntos();
        void cambiar_ajedrez();

        void activar_inmediato();
        void activar_diferido();
} ;


#endif
