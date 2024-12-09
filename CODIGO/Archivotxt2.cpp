#include "Archivotxt2.h"
#include "ListaCircularHistorial.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include<iostream>
using namespace std;

void Archivotxt2::limpiarLista(ListaCircularHistorial &hist) {
    Historial* cabeza = hist.getCabeza();  // Obtenemos la cabeza de la lista
    if (!cabeza) return;  // Si la lista está vacía, no hacemos nada

    Historial* actual = cabeza;  // Usamos 'actual' para recorrer la lista
    do {
        Historial* temp = actual;  // Guardamos el nodo actual en 'temp'
        actual = actual->getSiguiente();  // Movemos 'actual' al siguiente nodo
        delete temp;  // Eliminamos el nodo 'temp'
    } while (actual != cabeza);  // Continuamos hasta que volvamos a la cabeza

    hist.setCabeza(nullptr);  // Establecemos la cabeza de la lista a nullptr (vacía)
}



void Archivotxt2::guardarHistorial(ListaCircularHistorial &hist) {
    ofstream archivo("Historial.txt", ios::app); // Abre el archivo en modo 'append'

    if (!archivo) {
        cout << "Error al abrir el archivo para guardar el historial." << endl;
        return;
    }

    Historial* actual = hist.getCabeza();
    Historial* cabeza = actual;

    // Verifica que la lista no esté vacía
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

        actual = actual->getSiguiente();
    } while (actual != cabeza);

    archivo.close();
    cout << "Datos guardados correctamente en el archivo: " << "Historial.txt" << endl;
}


void Archivotxt2::leerHistorial(ListaCircularHistorial &hist) {
    limpiarLista(hist); // Limpia la lista para evitar duplicados

    ifstream archivo("Historial.txt");

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo: " << "Historial.txt" << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        // Parsear cada lÃ­nea del archivo
        stringstream ss(linea);
        string nombre, segundoNombre, apellido, segundoApellido, cedula, placa, fecha, horaIngreso, horaSalida;
        int puesto;

        // Leer los valores separados por comas
        getline(ss, nombre, ',');
        getline(ss, segundoNombre, ',');
        getline(ss, apellido, ',');
        getline(ss, segundoApellido, ',');
        getline(ss, cedula, ',');
        ss >> puesto;
        ss.ignore();
        getline(ss, placa, ',');
        getline(ss, fecha, ',');
        getline(ss, horaIngreso, ',');
        getline(ss, horaSalida, ',');

        // Crear un nuevo nodo
        Historial* nuevo = new Historial(puesto, placa, cedula, nombre, segundoNombre, apellido, segundoApellido, fecha, horaIngreso);

        // Obtener la cabeza de la lista
        Historial* cabeza = hist.getCabeza();

        // Verificar si la lista estÃ¡ vacÃ­a
        if (!cabeza) {
            // Si estÃ¡ vacÃ­a, el nuevo nodo serÃ¡ la cabeza
            hist.setCabeza(nuevo);
            nuevo->setSiguiente(nuevo); // Apuntando al mismo nodo (circularidad)
            nuevo->setAnterior(nuevo);
        } else {
            // Si no estÃ¡ vacÃ­a, insertar el nodo al final
            Historial* ultimo = cabeza->getAnterior(); // Nodo anterior a la cabeza

            // Actualizar los punteros
            ultimo->setSiguiente(nuevo);
            nuevo->setAnterior(ultimo);
            nuevo->setSiguiente(cabeza);
            cabeza->setAnterior(nuevo);
        }
    }

    archivo.close();
    cout << "Datos cargados correctamente desde el archivo: " << "Historial.txt" << endl;
}
