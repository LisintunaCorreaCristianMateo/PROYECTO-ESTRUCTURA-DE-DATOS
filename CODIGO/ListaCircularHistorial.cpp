    #include "ListaCircularHistorial.h"
	#include<iostream>
	#include <vector>
	#include <ctime>
	#include <iomanip>
	#include <string>
    #include <fstream>
    #include <sstream>


    using namespace std;
ListaCircularHistorial::~ListaCircularHistorial(){

}

void ListaCircularHistorial::ingresarVehiculo(int puesto, string placa, string cedula, string nombre, 
                                              string nombre2, string apellido, string apellido2, 
                                              string fecha, string horaIngreso) {
    // Crear un nuevo nodo con los datos del historial
    Historial* nuevo = new Historial(puesto, placa, cedula, nombre, nombre2, apellido, apellido2, fecha, horaIngreso);

    // Caso: la lista está vacía
    if (!cabeza) {
        cabeza = nuevo;
        nuevo->setSiguiente(nuevo); // Apunta a sí mismo
        nuevo->setAnterior(nuevo); // Apunta a sí mismo
        cout << "Clase historial >> Vehículo ingresado en el puesto " << nuevo->getPuesto() << ". La lista estaba vacía.\n";
        return;
    }

    // Caso: la lista no está vacía
    Historial* ultimo = cabeza->getAnterior(); // Historial al final de la lista

    // Actualizar punteros para insertar al final
    nuevo->setSiguiente(cabeza);  // El nuevo nodo apunta a la cabeza
    nuevo->setAnterior(ultimo);  // El nuevo nodo apunta al último nodo
    ultimo->setSiguiente(nuevo); // El último nodo apunta al nuevo nodo
    cabeza->setAnterior(nuevo);  // La cabeza apunta al nuevo nodo como anterior

    //cout << "Clase historial >> Vehículo ingresado en el puesto " << nuevo->getPuesto() << ".\n";
}
void ListaCircularHistorial::mostrarHistorial() {
    //leerHistorial(); // Cargar datos desde el archivo

    cout << "--- Historial de Vehiculos---" << endl;

    if (!cabeza) { // Verifica si la lista está vacía
        cout << "No hay historial en el parqueadero." << endl;
        return;
    }

    // Encabezados de columnas
    cout << left 
         << setw(10) << "Puesto" 
         << setw(15) << "Placa" 
         << setw(15) << "Cédula" 
         << setw(15) << "Nombre" 
         << setw(15) << "Nombre 2" 
         << setw(15) << "Apellido" 
         << setw(15) << "Apellido 2" 
         << setw(20) << "Fecha"
         << setw(20) << "Hora Ingreso" 
         << setw(20) << "Hora Salida" << endl;
         
    cout << string(160, '-') << endl; // Separador para mayor claridad

    Historial* actual = cabeza;
    bool historialEncontrado = false;

    // Recorrer la lista circular
    do {
        cout << setw(10) << actual->getPuesto()
             << setw(15) << actual->getPlaca()
             << setw(15) << actual->getCedula()
             << setw(15) << actual->getNombre()
             << setw(15) << actual->getSegundoNombre()
             << setw(15) << actual->getApellido()
             << setw(15) << actual->getSegundoApellido()
             << setw(20) << actual->getFecha()
             << setw(20) << actual->gethoraIngreso()
             << setw(20) << actual->gethoraSalida() << endl;

        historialEncontrado = true;
        actual = actual->getSiguiente(); // Avanzar al siguiente nodo
    } while (actual != cabeza); // Condición para detener el recorrido circular

    if (!historialEncontrado) {
        cout << "No se ha registrado historial en el parqueadero." << endl;
    }

    cout << endl;
}


void ListaCircularHistorial::limpiarLista() {
    if (!cabeza) return; // La lista ya est� vac�a

    Historial* actual = cabeza;
    do {
        Historial* siguiente = actual->getSiguiente();
        delete actual; // Liberar la memoria del nodo actual
        actual = siguiente;
    } while (actual != cabeza);

    cabeza = nullptr; // Resetear la lista
    cout << "Lista limpiada correctamente." << endl;
}

                    
void ListaCircularHistorial::guardarHistorial() {
    ofstream archivo("Historial.txt"); // Sobrescribir el archivo con los datos actuales

    if (!archivo) {
        cout << "Error al abrir el archivo para guardar el historial." << endl;
        return;
    }

    // Verifica que la lista no est� vac�a
    if (!cabeza) {
        cout << "No hay historial para guardar." << endl;
        archivo.close();
        return;
    }

    Historial* actual = cabeza;

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


void ListaCircularHistorial::leerHistorial() {
    //limpiarLista(); // Limpia la lista para evitar duplicados

    ifstream archivo("Historial.txt");

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo: " << "Historial.txt" << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        // Parsear cada l�nea del archivo
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

        // Agregar los datos le�dos a la lista circular
        ingresarVehiculo(puesto, placa, cedula, nombre, segundoNombre, apellido, segundoApellido, fecha, horaIngreso);
    }

    archivo.close();
    cout << "Datos cargados correctamente desde el archivo: " << "Historial.txt" << endl;
}


