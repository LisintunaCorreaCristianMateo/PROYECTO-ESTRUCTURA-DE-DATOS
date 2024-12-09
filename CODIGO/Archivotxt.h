#ifndef ARCHIVOSTXT_H  // Cambi� ArchivosTXT a ARCHIVOSTXT_H para mantener consistencia
#define ARCHIVOSTXT_H
#include "ListaCircularDoble.h"
#include <string>

class Archivotxt {
public:
    // Constructores y destructores
    Archivotxt() = default;
    ~Archivotxt() = default;

    // M�todos
    void guardarDatos(ListaCircularDoble &parqueadero);
    void guardarPlacas(ListaCircularDoble &parqueadero);
    //void guardarHistorial(ListaCircularDoble &parqueadero);
    
    //Metodos lecturas txt
    void leerPlacas(ListaCircularDoble &parqueadero);
    void leerDatos(ListaCircularDoble &parqueadero);
   
    
};

#endif

