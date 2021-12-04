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
    ObjRevolucion(const std::string & archivo, int num_instancias, int eje, bool tapa_sup=true, bool tapa_inf=true) ;
    ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, int eje, bool tapa_sup=true, bool tapa_inf=true) ;

    void cambiarTapas();

protected:
    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, int eje, bool tapa_sup, bool tapa_inf);
    void drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices) override;
    bool esPolo(Tupla3f p, int eje);
    void calcular_texturas();
    float distancia(Tupla3f p1, Tupla3f p2);

    Tupla3f rotarEjeX(Tupla3f punto, float radianes) ; //Rota en el eje X un punto
    Tupla3f rotarEjeY(Tupla3f punto, float radianes) ; //Rota en el eje Y un punto
    Tupla3f rotarEjeZ(Tupla3f punto, float radianes) ; //Rota en el eje Z un punto
    Tupla3f rotarEje(Tupla3f punto, float radianes, int eje) ; //Rota en un eje un punto

    int numero_instancias,
        numero_puntos_perfil,
        size_tronco,
        n_tapas[2] = {0, 0};

    bool tapa_sup, 
         tapa_inf, 
         visibilidad_tapas = true;

    std::vector<float> dp; ///distancia al perfil de cada elemento del perfil
} ;

#endif
