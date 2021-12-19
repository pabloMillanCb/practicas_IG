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
        LucesOvni(Esfera *b);
        void draw();
        void aumentar_r_bolas(float aumento);
} ;


#endif
