#include "Archivotxt2.h"
#include "ListaCircularHistorial.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include<iostream>
using namespace std;



void Archivotxt2::guardarHistorial(ListaCircularHistorial &hist) {
    // Abrir el archivo en modo sobrescritura
    ofstream archivo("Historial.txt");

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar el historial." << endl;
        return;
    }

    Historial* actual = hist.getCabeza();
    Historial* cabeza = actual;

    // Verifica que la lista no está vacía
    if (!cabeza) {
        cout << "No hay historial para guardar." << endl;
        archivo.close();
        return;
    }

    // Recorrer la lista circular y guardar los datos en el archivo
    do {
        archivo << actual->getNombre() << ","
                << actual->getSegundoNombre() << ","
                << actual->getApellido() << ","
                << actual->getSegundoApellido() << ","
                << actual->getCedula() << ","
                << actual->getPuesto() << ","
                << actual->getPlaca() << ","
                << actual->getFecha() << ","
                << actual->gethoraIngreso() << ","
                << actual->gethoraSalida() << endl;

        cout << "Guardando: " << actual->getNombre() << " " << actual->getPlaca() << endl;  // Depuración

        actual = actual->getSiguiente();
    } while (actual != cabeza);

    archivo.flush();  // Asegurar que se escriban los datos
    archivo.close();
    cout << "Datos guardados correctamente en el archivo: " << "Historial.txt" << endl;
}




void Archivotxt2::leerHistorial(ListaCircularHistorial &hist) {
    hist.limpiarLista(); // Limpiar la lista antes de agregar nuevos datos

    ifstream archivo("Historial.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo: " << "Historial.txt" << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        // Parsear cada línea del archivo
        stringstream ss(linea);
        string nombre, segundoNombre, apellido, segundoApellido, cedula, placa, fecha, horaIngreso, horaSalida;
        int puesto;

        // Leer los valores separados por comas
        if (!getline(ss, nombre, ',') || !getline(ss, segundoNombre, ',') || !getline(ss, apellido, ',') ||
            !getline(ss, segundoApellido, ',') || !getline(ss, cedula, ',') || !(ss >> puesto) || !ss.ignore() ||
            !getline(ss, placa, ',') || !getline(ss, fecha, ',') || !getline(ss, horaIngreso, ',') ||
            !getline(ss, horaSalida, ',')) {
            cerr << "Error al leer los datos de la línea: " << linea << endl;
            continue; // Saltar esta línea si hubo un error en la lectura
        }

        // Crear un nuevo nodo con los datos leídos
        Historial* nuevo = new Historial(puesto, placa, cedula, nombre, segundoNombre, apellido, segundoApellido, fecha, horaIngreso, horaSalida);

        // Insertar el nuevo nodo en la lista utilizando un método de la clase ListaCircularHistorial
        hist.agregarAlFinal(nuevo); // Nuevo método para manejar la inserción en la lista circular
          cout << "Propietario leído: " << nombre;
    }

    archivo.close();
    cout << "Datos cargados correctamente desde el archivo: " << "Historial.txt" << endl;
}

