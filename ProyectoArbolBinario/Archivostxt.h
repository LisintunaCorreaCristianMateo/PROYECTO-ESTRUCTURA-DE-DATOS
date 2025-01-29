#ifndef ARCHIVOSTXT_H
#define ARCHIVOSTXT_H

#include "ArbolParqueadero.h"
#include <string>
#include <iostream>
using namespace std;

class Archivostxt {
public:
    // Constructor y destructor
    Archivostxt() = default;
    ~Archivostxt() = default;

    // M�todos principales
    void leerDesdeArchivo( string nombreArchivo, ArbolParqueadero& arbol);
    void guardarEnArchivo( string nombreArchivo,  ArbolParqueadero& arbol);
};

#endif // ARCHIVOS_H

