#ifndef ARCHIVOSTXT_H  // Cambié ArchivosTXT a ARCHIVOSTXT_H para mantener consistencia
#define ARCHIVOSTXT_H

#include "ListaCircularDoble.h"
#include <string>

class Archivotxt {
public:
    // Constructores y destructores
    Archivotxt() = default;
    ~Archivotxt() = default;

    // Métodos
    void guardarDatos(ListaCircularDoble &parqueadero);
    void guardarPlacas(ListaCircularDoble &parqueadero);
    void guardarHistorial(ListaCircularDoble &parqueadero);
};

#endif

