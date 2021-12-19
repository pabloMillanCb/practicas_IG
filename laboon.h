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
        Laboon(ObjPLY *ball, ObjPLY* som);
        void draw();
} ;


#endif
