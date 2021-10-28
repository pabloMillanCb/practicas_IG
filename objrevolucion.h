// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
   public:
       ObjRevolucion();
   ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
   ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;

   void cambiarTapas();

protected:
    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf);
    void crearTapas(int size_perfil, int num_instancias, bool tapa_sup, bool tapa_inf);

    int numero_instancias, size_tronco, n_tapas[2] = {0, 0};
    bool tapa_sup, tapa_inf, visibilidad_tapas = true;
    std::vector<Tupla3i> f_tmp, f1_tmp, f2_tmp;
} ;




#endif
