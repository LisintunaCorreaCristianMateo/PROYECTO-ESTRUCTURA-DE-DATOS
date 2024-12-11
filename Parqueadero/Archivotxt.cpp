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
ofstream archivo("Placas.txt");
if (!archivo) {
    cerr << "Error al abrir el archivo para guardar las placas." << endl;
    return;
}

Nodo* actualIzquierda = parqueadero.getCabezaIzquierda();
Nodo* actualDerecha = parqueadero.getCabezaDerecha();

// Recorrer la lista izquierda
do {
    if (actualIzquierda->isOcupado()) {
        archivo << actualIzquierda->getPlaca() << "," << actualIzquierda->getPuesto() << endl;
    }
    actualIzquierda = actualIzquierda->getSiguiente();
} while (actualIzquierda != parqueadero.getCabezaIzquierda());

// Recorrer la lista derecha (si aplica)
do {
    if (actualDerecha->isOcupado()) {
        archivo << actualDerecha->getPlaca() << "," << actualDerecha->getPuesto() << endl;
    }
    actualDerecha = actualDerecha->getSiguiente();
} while (actualDerecha != parqueadero.getCabezaDerecha());
}



// Lectura


void Archivotxt::leerPlacas(ListaCircularDoble &parqueadero) {
    ifstream archivo("Placas.txt");

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo: " << "Placas.txt" << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        // Parsear cada línea del archivo
        stringstream ss(linea);
        int puesto;
        string placa;

        getline(ss, placa, ',');
        ss >> puesto; ss.ignore();
 

        // Buscar el nodo correspondiente al puesto
        Nodo* actual = parqueadero.getCabezaIzquierda();
        bool encontrado = false;

        // Buscar en la fila izquierda
        do {
            if (actual->getPuesto() == puesto) {
                encontrado = true;
                break;
            }
            actual = actual->getSiguiente();
        } while (actual != parqueadero.getCabezaIzquierda());

        // Buscar en la fila derecha si no se encuentra en la izquierda
        if (!encontrado) {
            actual = parqueadero.getCabezaDerecha();
            do {
                if (actual->getPuesto() == puesto) {
                    encontrado = true;
                    break;
                }
                actual = actual->getSiguiente();
            } while (actual !=parqueadero.getCabezaDerecha());
        }

        // Si el puesto se encontró, actualizar sus datos
        if (encontrado) {
            actual->setPlaca(placa);
            actual->setOcupado(true);
        }
        if(!encontrado){
        	cout<<"El puesto es"<<puesto<<endl;
            cout<<"Puesto no encontrado en la lista para asignar atributos\n\n";
            
        }
    }

    archivo.close();
  //  cout << "Datos cargados correctamente desde el archivo: " << "Placas.txt" << endl;
}

void Archivotxt::leerDatos(ListaCircularDoble &parqueadero) {
    ifstream archivo("Propietarios.txt");

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo: " << "Propietarios.txt" << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        // Parsear cada línea del archivo
        stringstream ss(linea);
        
        string placa,nombre,segundoNombre,apellido,segundoApellido,cedula;

        
        getline(ss, nombre, ',');
        getline(ss, segundoNombre, ',');
        getline(ss, apellido, ',');
        getline(ss, segundoApellido, ',');
        getline(ss, cedula, ',');
        getline(ss, placa, ',');
        
 

        // Buscar el nodo correspondiente al puesto
        Nodo* actual = parqueadero.getCabezaIzquierda();
        bool encontrado = false;

        // Buscar en la fila izquierda
        do {
            if (actual->getPlaca() == placa) {
                encontrado = true;
                break;
            }
            actual = actual->getSiguiente();
        } while (actual != parqueadero.getCabezaIzquierda());

        // Buscar en la fila derecha si no se encuentra en la izquierda
        if (!encontrado) {
            actual = parqueadero.getCabezaDerecha();
            do {
                if (actual->getPlaca() == placa) {
                    encontrado = true;
                    break;
                }
                actual = actual->getSiguiente();
            } while (actual !=parqueadero.getCabezaDerecha());
        }

        // Si la placa se encontró, actualizar sus datos
        if (encontrado) {
            actual->setNombre(nombre);
            actual->setSegundoNombre(segundoNombre);
            actual->setApellido(apellido);
            actual->setSegundoApellido(segundoApellido);
            actual->setCedula(cedula);
        }
    }

    archivo.close();
    //cout << "Datos cargados correctamente desde el archivo: " << "Propietarios.txt" << endl;
}












