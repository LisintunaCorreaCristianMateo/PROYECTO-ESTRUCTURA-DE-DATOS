	#include "ListaCircularDoble.h"
	#include<iostream>
	#include <vector>
	#include <ctime>
	#include <iomanip>
	#include <string>
	using namespace std;

	//constructor
	ListaCircularDoble::ListaCircularDoble(int puestosTotales)  {
    	totalPuestos=puestosTotales;
    	cabezaIzquierda=NULL;
		cabezaDerecha=NULL;
    	
        puestosPorLado = puestosTotales / 2; // La mitad de los puestos se asignan a cada lado

        // Crear los puestos de la fila izquierda
        for (int i = 1; i <= puestosPorLado; i++) {
            insertarNodo(i, true);
        }

        // Crear los puestos de la fila derecha
        for (int i = puestosPorLado + 1; i <= totalPuestos; i++) {
            insertarNodo(i, false);
        }
    }
	//destructor
    ListaCircularDoble::~ListaCircularDoble(){
    	
	}

    // Función para obtener la fecha actual
string obtenerFechaActual() {
    time_t tiempoActual = time(nullptr);
    tm* fechaLocal = localtime(&tiempoActual);

    char buffer[20]; // Buffer para almacenar la fecha
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", fechaLocal);

    return string(buffer);
}

// Función para obtener la hora actual
string obtenerHoraActual() {
    time_t tiempoActual = time(nullptr);
    tm* horaLocal = localtime(&tiempoActual);

    char buffer[20]; // Buffer para almacenar la hora
    strftime(buffer, sizeof(buffer), "%H:%M:%S", horaLocal);

    return string(buffer);
}

    // Funci�n para insertar un nodo en la lista circular
void ListaCircularDoble::insertarNodo(int puesto, bool esIzquierda) {
    Nodo* nuevo = new Nodo(puesto);
    if (esIzquierda) {
        if (!cabezaIzquierda) { // Si la lista izquierda está vacía
            cabezaIzquierda = nuevo;
            cabezaIzquierda->setSiguiente(cabezaIzquierda);
            cabezaIzquierda->setAnterior(cabezaIzquierda);
        } else { // Agregar al final de la lista izquierda
            Nodo* ultimo = cabezaIzquierda->getAnterior();
            ultimo->setSiguiente(nuevo);
            nuevo->setAnterior(ultimo);
            nuevo->setSiguiente(cabezaIzquierda);
            cabezaIzquierda->setAnterior(nuevo);
        }
    } else {
        if (!cabezaDerecha) { // Si la lista derecha está vacía
            cabezaDerecha = nuevo;
            cabezaDerecha->setSiguiente(cabezaDerecha);
            cabezaDerecha->setAnterior(cabezaDerecha);
        } else { // Agregar al final de la lista derecha
            Nodo* ultimo = cabezaDerecha->getAnterior();
            ultimo->setSiguiente(nuevo);
            nuevo->setAnterior(ultimo);
            nuevo->setSiguiente(cabezaDerecha);
            cabezaDerecha->setAnterior(nuevo);
        }
    }
}


    // Funci�n para dibujar el parqueadero en forma de anillo
void ListaCircularDoble::dibujarParqueadero() {
    Nodo* actualIzquierda = cabezaIzquierda;
    Nodo* actualDerecha = cabezaDerecha;

    cout << "\n--- Estado del Parqueadero Circular ---\n";

    // Dibujar la fila izquierda
    do {
        if (actualIzquierda->isOcupado()) {
            cout << "\033[1;31m"; // Rojo brillante
            cout << "[P" << setw(2) << actualIzquierda->getPuesto() 
                 << ": " << actualIzquierda->getPlaca() << "]  ";
            cout << "\033[0m"; // Restablecer color
        } else {
            cout << "[P" << setw(2) << actualIzquierda->getPuesto() << "]  ";
        }
        actualIzquierda = actualIzquierda->getSiguiente();
    } while (actualIzquierda != cabezaIzquierda);
    cout << endl;

    for (int i = 0; i < puestosPorLado; i++) {
        cout << "   ---   ";
    }
    cout << endl;

    // Dibujar la fila derecha
    do {
        if (actualDerecha->isOcupado()) {
            cout << "\033[1;31m";
            cout << "[P" << setw(2) << actualDerecha->getPuesto() 
                 << ": " << actualDerecha->getPlaca() << "]  ";
            cout << "\033[0m";
        } else {
            cout << "[P" << setw(2) << actualDerecha->getPuesto() << "]  ";
        }
        actualDerecha = actualDerecha->getSiguiente();
    } while (actualDerecha != cabezaDerecha);
    cout << endl;
}


    // Funci�n para determinar los puestos vac�os
void ListaCircularDoble::mostrarPuestosLibres() {
    Nodo* actual = cabezaIzquierda;
    cout << "Puestos libres (Izquierda): ";
    do {
        if (!actual->isOcupado()) {
            cout << actual->getPuesto() << " ";
        }
        actual = actual->getSiguiente();
    } while (actual != cabezaIzquierda);
    cout << endl;

    actual = cabezaDerecha;
    cout << "Puestos libres (Derecha): ";
    do {
        if (!actual->isOcupado()) {
            cout << actual->getPuesto() << " ";
        }
        actual = actual->getSiguiente();
    } while (actual != cabezaDerecha);
    cout << endl;
}

    // Funci�n para ingresar un veh�culo en un puesto vac�o aleatorio
void ListaCircularDoble::ingresarVehiculo(string placa, string cedula, string nombre, 
                                          string nombre2, string apellido, string apellido2) {
    vector<Nodo*> puestosLibres;
    Nodo* actual = cabezaIzquierda;

    do {
        if (!actual->isOcupado()) {
            puestosLibres.push_back(actual);
        }
        actual = actual->getSiguiente();
    } while (actual != cabezaIzquierda);

    actual = cabezaDerecha;
    do {
        if (!actual->isOcupado()) {
            puestosLibres.push_back(actual);
        }
        actual = actual->getSiguiente();
    } while (actual != cabezaDerecha);

    if (puestosLibres.empty()) {
        cout << "No hay puestos disponibles." << endl;
        return;
    }

    srand(time(0));
    int indiceAleatorio = rand() % puestosLibres.size();
    Nodo* puestoSeleccionado = puestosLibres[indiceAleatorio];

    puestoSeleccionado->setOcupado(true);
    puestoSeleccionado->setPlaca(placa);

    cout << "Vehículo con placa " << placa << " ingresado en el puesto " << puestoSeleccionado->getPuesto() << "." << endl;
}


    // Funci�n para eliminar un veh�culo
void ListaCircularDoble::retirarVehiculo(int puesto) {
    Nodo* actual = cabezaIzquierda;

    do {
        if (actual->getPuesto() == puesto) {
            if (actual->isOcupado()) {
                cout << "Vehículo con placa " << actual->getPlaca() 
                     << " retirado del puesto " << puesto << "." << endl;
                actual->setOcupado(false);
                actual->setPlaca(string(""));
            } else {
                cout << "El puesto " << puesto << " está libre." << endl;
            }
            return;
        }
        actual = actual->getSiguiente();
    } while (actual != cabezaIzquierda);

    actual = cabezaDerecha;
    do {
        if (actual->getPuesto() == puesto) {
            if (actual->isOcupado()) {
                cout << "Vehículo con placa " << actual->getPlaca() 
                     << " retirado del puesto " << puesto << "." << endl;
                actual->setOcupado(false);
                actual->setPlaca("");
            } else {
                cout << "El puesto " << puesto << " está libre." << endl;
            }
            return;
        }
        actual = actual->getSiguiente();
    } while (actual != cabezaDerecha);

    cout << "El puesto " << puesto << " no existe." << endl;
}
// metodos para la impresion
void ListaCircularDoble::mostrarDatos() {
    Nodo* actual = cabezaIzquierda;

    cout << "--- Datos de los Propietarios ---" << endl;

    if (!cabezaIzquierda && !cabezaDerecha) {
        cout << "No hay datos disponibles en el parqueadero." << endl;
        return;
    }

    // Recorrer todos los nodos en la lista circular
    do {
        if (actual->isOcupado()) { // Verifica si el puesto est� ocupado
            cout << "Puesto " << actual->getPuesto() << ": " << endl;
            cout << "  Nombre: " << actual->getNombre() << " " << actual->getApellido() << endl;
            cout << "  Cedula: " << actual->getCedula() << endl;
            cout << "  Placa: " << actual->getPlaca() << endl;
            cout << "------------------------------------" << endl;
        }
        actual = actual->getSiguiente();
    } while (actual != cabezaIzquierda); // Continuar hasta dar la vuelta completa

    cout << endl;
}


void ListaCircularDoble::mostrarAutos() {
    Nodo* actual = cabezaIzquierda;

    cout << "--- Autos Registrados en el Parqueadero ---" << endl;

    if (!cabezaIzquierda) { // Verifica si hay nodos en la lista
        cout << "No hay autos en el parqueadero." << endl;
        return;
    }

    bool autosEncontrados = false;

    // Recorrer todos los nodos en la lista circular
    do {
        if (actual->isOcupado()) { // Verifica si el puesto está ocupado
            cout << "Puesto " << actual->getPuesto() << ": " << actual->getPlaca() << endl;
            autosEncontrados = true;
        }
        actual = actual->getSiguiente();
    } while (actual != cabezaIzquierda);

    if (!autosEncontrados) {
        cout << "No hay autos registrados en este momento." << endl;
    }

    cout << endl;
}




void ListaCircularDoble::mostrarHistorial() {
    Nodo* actual = cabezaIzquierda;

    cout << "--- Historial de Vehiculos ---" << endl;

    if (!cabezaIzquierda) { // Verifica si hay nodos en la lista
        cout << "No hay historial en el parqueadero." << endl;
        return;
    }

    bool historialEncontrado = false;

    // Recorrer todos los nodos en la lista circular
    do {
        if (actual->isOcupado() || (!actual->gethoraIngreso().empty() && !actual->gethoraSalida().empty())) { 
            // Mostrar historial solo si hay registro de entrada y salida
            cout << "Puesto " << actual->getPuesto() << ": " << actual->getPlaca() << endl;
            cout << "  Entrada: " << actual->gethoraIngreso() << endl;
            cout << "  Salida: " << actual->gethoraSalida() << endl;
            historialEncontrado = true;
        }
        actual = actual->getSiguiente();
    } while (actual != cabezaIzquierda);

    if (!historialEncontrado) {
        cout << "No se ha registrado historial en el parqueadero." << endl;
    }

    cout << endl;
}






