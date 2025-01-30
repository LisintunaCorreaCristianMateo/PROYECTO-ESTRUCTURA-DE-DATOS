#include "Historialtxt.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip> // Para std::setw
#include <sstream>
#include <stdexcept>
#include <algorithm>

using namespace std;

void Historialtxt::leerHistorialTxt(string nombreArchivo, ArbolHistorial &arbol) {
    ifstream archivo(nombreArchivo.c_str(), ios::in); // Abrir archivo para lectura

    if (!archivo) {
        cout << "No se pudo abrir el archivo para leer los datos." << endl;
        return;
    }

    arbol.liberarArbol(); // Limpia el árbol antes de cargar nuevos datos

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) {
            continue; // Ignorar líneas vacías
        }

        // Usar un stringstream para dividir la línea por comas
        stringstream ss(linea);
        string puestostr, placa, cedula, nombre, segundoNombre, apellido, segundoApellido, fecha, horaIngreso;

        // Leer los campos separados por comas
        getline(ss, puestostr, ',');
        getline(ss, placa, ',');
        getline(ss, cedula, ',');
        getline(ss, nombre, ',');
        getline(ss, segundoNombre, ',');
        getline(ss, apellido, ',');
        getline(ss, segundoApellido, ',');
        getline(ss, fecha, ',');
        getline(ss, horaIngreso, ',');

        // Validar y convertir puesto
        int puesto;
        try {
            puesto = stoi(puestostr); // Convertir puesto a entero
            if (puesto < 0) throw invalid_argument("Puesto negativo");
        } catch (exception &e) {
            cout << "Error: Puesto no válido en línea: '" << puestostr << "' (" << e.what() << ")" << endl;
            continue; // Ignorar esta línea si hay error
        }

        // Crear y agregar el vehículo al árbol
        NodoHistorial* nuevoVehiculo = new NodoHistorial(puesto, placa, cedula, nombre, segundoNombre, apellido, segundoApellido, fecha, horaIngreso);
        nuevoVehiculo->setOcupado(true);

        arbol.insertar(nuevoVehiculo);
    }

    archivo.close();
    cout << "Datos cargados desde el archivo: " << nombreArchivo << endl;
}
void Historialtxt::guardarHistorialTxt(string nombreArchivo, ArbolHistorial &arbol) {
    ofstream archivo(nombreArchivo.c_str(), ios::out | ios::trunc); // Abrir archivo para escritura

    if (!archivo) {
        cout << "No se pudo abrir el archivo para guardar los datos." << endl;
        return;
    }

    if (arbol.estaVacio()) {
        cout << "El árbol está vacío, no hay datos para guardar." << endl;
        archivo.close();
        return;
    }

arbol.recorrerPreOrden([&archivo](NodoHistorial* vehiculo) {
    archivo << vehiculo->getPuesto() << ","            // Puesto
            << vehiculo->getPlaca() << ","             // Placa
            << vehiculo->getCedula() << ","            // Cédula
            << vehiculo->getNombre() << ","            // Nombre
            << vehiculo->getSegundoNombre() << ","     // Segundo Nombre
            << vehiculo->getApellido() << ","          // Apellido
            << vehiculo->getSegundoApellido() << ","   // Segundo Apellido
            << vehiculo->getFecha() << ","             // Fecha
            << vehiculo->getHoraIngreso() << endl;     // Hora de Ingreso

    if (!archivo) {
        cout << "Error al escribir en el archivo." << endl;
        return;
    }
});

    archivo.close();
    cout << "Datos guardados en el archivo: " << nombreArchivo << endl;
}
