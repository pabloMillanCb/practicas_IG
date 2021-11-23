#ifndef LABOON_H_INCLUDED
#define LABOON_H_INCLUDED

#include "aux.h"
#include "objply.h"

class Laboon
{
    private:
        ObjPLY* ballena;
        ObjPLY* sombrero;
        
    public:
        Laboon();
        void draw();

        void cambiar_solido();
        void cambiar_lineas();
        void cambiar_puntos();
        void cambiar_ajedrez();

        void activar_inmediato();
        void activar_diferido();
} ;


#endif
