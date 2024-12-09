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


                    


