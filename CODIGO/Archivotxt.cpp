#include "Archivotxt.h"
#include "ListaCircularDoble.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include<iostream>

using namespace std;

void Archivotxt::guardarDatos(ListaCircularDoble &parqueadero) {
    ofstream archivo("Propietarios.txt");

    if (!archivo) {
        cout << "Error al abrir el archivo para guardar los datos sin placa." << endl;
        return;
    }

    Nodo* actualIzquierda = parqueadero.getCabezaIzquierda();
    Nodo* actualDerecha = parqueadero.getCabezaDerecha();
    Nodo* cabezaIzquierda = actualIzquierda;  // Declarar la cabeza para el ciclo
    Nodo* cabezaDerecha = actualDerecha;      // Declarar la cabeza para el ciclo

    // Recorrer la lista izquierda
    do {
        if (actualIzquierda->isOcupado()) {
            archivo << actualIzquierda->getNombre() << ","
                    << actualIzquierda->getSegundoNombre() << ","
                    << actualIzquierda->getApellido() << ","
                    << actualIzquierda->getSegundoApellido() << ","
                    << actualIzquierda->getCedula() << ","
                    << actualIzquierda->getPlaca() << endl;
        }
        actualIzquierda = actualIzquierda->getSiguiente();
    } while (actualIzquierda != cabezaIzquierda);  // Usar cabezaIzquierda para el ciclo

    // Recorrer la lista derecha
    do {
        if (actualDerecha->isOcupado()) {
            archivo << actualDerecha->getNombre() << ","
                    << actualDerecha->getSegundoNombre() << ","
                    << actualDerecha->getApellido() << ","
                    << actualDerecha->getSegundoApellido() << ","
                    << actualDerecha->getCedula() << ","
                    << actualDerecha->getPlaca() << endl;
        }
        actualDerecha = actualDerecha->getSiguiente();
    } while (actualDerecha != cabezaDerecha);  // Usar cabezaDerecha para el ciclo

    archivo.close();
}
void Archivotxt::guardarPlacas(ListaCircularDoble &parqueadero) {
ofstream archivo("placas.txt");
if (!archivo) {
    cerr << "Error al abrir el archivo para guardar las placas." << endl;
    return;
}

Nodo* actualIzquierda = parqueadero.getCabezaIzquierda();
Nodo* actualDerecha = parqueadero.getCabezaDerecha();

// Recorrer la lista izquierda
do {
    if (actualIzquierda->isOcupado()) {
        archivo << actualIzquierda->getPlaca() << ";" << actualIzquierda->getPuesto() << endl;
    }
    actualIzquierda = actualIzquierda->getSiguiente();
} while (actualIzquierda != parqueadero.getCabezaIzquierda());

// Recorrer la lista derecha (si aplica)
do {
    if (actualDerecha->isOcupado()) {
        archivo << actualDerecha->getPlaca() << ";" << actualDerecha->getPuesto() << endl;
    }
    actualDerecha = actualDerecha->getSiguiente();
} while (actualDerecha != parqueadero.getCabezaDerecha());
}

void Archivotxt::guardarHistorial(ListaCircularDoble &parqueadero) {
    ofstream archivo("Historial.txt");

    if (!archivo) {
        cout << "Error al abrir el archivo para guardar el historial." << endl;
        return;
    }

    Nodo* actualIzquierda = parqueadero.getCabezaIzquierda();
    Nodo* actualDerecha = parqueadero.getCabezaDerecha();

    // Recorrer la lista izquierda
    do {
        if (!actualIzquierda->gethoraIngreso().empty() || actualIzquierda->isOcupado()) {
            archivo << actualIzquierda->getPuesto() << ","
                    << actualIzquierda->getPlaca() << ","
                    << actualIzquierda->gethoraIngreso() << ",";
            if (actualIzquierda->gethoraSalida().empty()) {
                archivo << "Vehiculo parqueado" << endl;
            } else {
                archivo << actualIzquierda->gethoraSalida() << endl;
            }
        }
        actualIzquierda = actualIzquierda->getSiguiente();
    } while (actualIzquierda != parqueadero.getCabezaIzquierda());
    							
    
    							

    // Recorrer la lista derecha
    do {
        if (!actualDerecha->gethoraIngreso().empty() || actualDerecha->isOcupado()) {
            archivo << actualDerecha->getPuesto() << ","
                    << actualDerecha->getPlaca() << ","
                    << actualDerecha->gethoraIngreso() << ",";
            if (actualDerecha->gethoraSalida().empty()) {
                archivo << "Vehiculo parqueado" << endl;
            } else {
                archivo << actualDerecha->gethoraSalida() << endl;
            }
        }
        actualDerecha = actualDerecha->getSiguiente();
    } while (actualDerecha != parqueadero.getCabezaDerecha());
    							

    archivo.close();
    cout << "Historial guardado en 'Historial.txt'." << endl;
}










