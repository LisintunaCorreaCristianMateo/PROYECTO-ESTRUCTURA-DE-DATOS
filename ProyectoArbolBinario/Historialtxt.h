#ifndef HistorialTXT_H
#define HistorialTXT_H

#include "ArbolHistorial.h"
#include <string>
#include <iostream>
using namespace std;

class Historialtxt {
public:
    // Constructor y destructor
    Historialtxt() = default;
    ~Historialtxt() = default;

    // M�todos principales
    void leerHistorialTxt( string nombreArchivo, ArbolHistorial& arbol);
    void guardarHistorialTxt(string nombreArchivo, ArbolHistorial &arbol);
    
};

#endif // ARCHIVOS_H

