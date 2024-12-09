#ifndef ARCHIVOSTXT2_H  // Cambi� ArchivosTXT a ARCHIVOSTXT_H para mantener consistencia
#define ARCHIVOSTXT2_H
#include "ListaCircularHistorial.h"
#include <string>

class Archivotxt2 {
public:
    // Constructores y destructores
    Archivotxt2() = default;
    ~Archivotxt2() = default;

    // M�todos
    void guardarHistorial(ListaCircularHistorial &hist);
    void leerHistorial(ListaCircularHistorial &hist);
    void limpiarLista(ListaCircularHistorial& hist);
};

#endif

