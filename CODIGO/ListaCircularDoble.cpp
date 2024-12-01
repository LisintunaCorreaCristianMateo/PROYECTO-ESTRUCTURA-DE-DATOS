	#include "ListaCircularDoble.h"
	#include<iostream>
	#include <vector>
	#include <ctime>
	#include <iomanip>
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

    // Función para insertar un nodo en la lista circular
    void ListaCircularDoble::insertarNodo(int puesto, bool esIzquierda) {
        Nodo* nuevo = new Nodo(puesto);
        if (esIzquierda) {
            if (!cabezaIzquierda) { // Si la lista izquierda está vacía
                cabezaIzquierda = nuevo;
                cabezaIzquierda->siguiente = cabezaIzquierda;
                cabezaIzquierda->anterior = cabezaIzquierda;
            } else { // Agregar al final de la lista izquierda
                Nodo* ultimo = cabezaIzquierda->anterior;
                ultimo->siguiente = nuevo;
                nuevo->anterior = ultimo;
                nuevo->siguiente = cabezaIzquierda;
                cabezaIzquierda->anterior = nuevo;
            }
        } else {
            if (!cabezaDerecha) { // Si la lista derecha está vacía
                cabezaDerecha = nuevo;
                cabezaDerecha->siguiente = cabezaDerecha;
                cabezaDerecha->anterior = cabezaDerecha;
            } else { // Agregar al final de la lista derecha
                Nodo* ultimo = cabezaDerecha->anterior;
                ultimo->siguiente = nuevo;
                nuevo->anterior = ultimo;
                nuevo->siguiente = cabezaDerecha;
                cabezaDerecha->anterior = nuevo;
            }
        }
    }

    // Función para dibujar el parqueadero en forma de anillo
    void ListaCircularDoble::dibujarParqueadero() {
        Nodo* actualIzquierda = cabezaIzquierda;
        Nodo* actualDerecha = cabezaDerecha;

        cout << "\n--- Estado del Parqueadero Circular ---\n";
        // Dibujar la fila izquierda
        do {
            if (actualIzquierda->ocupado) {
                cout << "[P" << setw(2) << actualIzquierda->puesto << ": " << actualIzquierda->placa << "]";
            } else {
                cout << "[P" << setw(2) << actualIzquierda->puesto << ": Libre ]";
            }
            actualIzquierda = actualIzquierda->siguiente;
        } while (actualIzquierda != cabezaIzquierda);
        cout << endl;

        // Dibujar la vía (línea de guiones)
        for (int i = 0; i < puestosPorLado; i++) {
            cout << "   ---   ";
        }
        cout << endl;

        // Dibujar la fila derecha
        do {
            if (actualDerecha->ocupado) {
                cout << "[P" << setw(2) << actualDerecha->puesto << ": " << actualDerecha->placa << "]";
            } else {
                cout << "[P" << setw(2) << actualDerecha->puesto << ": Libre ]";
            }
            actualDerecha = actualDerecha->siguiente;
        } while (actualDerecha != cabezaDerecha);
        cout << endl;
    }

    // Función para determinar los puestos vacíos
    void ListaCircularDoble:: mostrarPuestosLibres() {
        Nodo* actual = cabezaIzquierda;
        cout << "Puestos libres (Izquierda): ";
        do {
            if (!actual->ocupado) {
                cout << actual->puesto << " ";
            }
            actual = actual->siguiente;
        } while (actual != cabezaIzquierda);
        cout << endl;

        actual = cabezaDerecha;
        cout << "Puestos libres (Derecha): ";
        do {
            if (!actual->ocupado) {
                cout << actual->puesto << " ";
            }
            actual = actual->siguiente;
        } while (actual != cabezaDerecha);
        cout << endl;
    }

    // Función para ingresar un vehículo en un puesto vacío aleatorio
    void ListaCircularDoble::ingresarVehiculo(string placa) {
        vector<Nodo*> puestosLibres;
        Nodo* actual = cabezaIzquierda;

        // Recopilar todos los puestos libres en la fila izquierda
        do {
            if (!actual->ocupado) {
                puestosLibres.push_back(actual);
            }
            actual = actual->siguiente;
        } while (actual != cabezaIzquierda);

        // Recopilar todos los puestos libres en la fila derecha
        actual = cabezaDerecha;
        do {
            if (!actual->ocupado) {
                puestosLibres.push_back(actual);
            }
            actual = actual->siguiente;
        } while (actual != cabezaDerecha);

        if (puestosLibres.empty()) {
            cout << "No hay puestos disponibles." << endl;
            return;
        }

        // Seleccionar un puesto vacío aleatorio
        srand(time(0));
        int indiceAleatorio = rand() % puestosLibres.size();
        Nodo* puestoSeleccionado = puestosLibres[indiceAleatorio];

        // Asignar el vehículo al puesto seleccionado
        puestoSeleccionado->ocupado = true;
        puestoSeleccionado->placa = placa;

        cout << "Vehículo con placa " << placa << " ingresado en el puesto " << puestoSeleccionado->puesto << "." << endl;
    }

    // Función para eliminar un vehículo
    void ListaCircularDoble::retirarVehiculo(int puesto) {
        Nodo* actual = cabezaIzquierda;

        // Buscar en la fila izquierda
        do {
            if (actual->puesto == puesto) {
                if (actual->ocupado) {
                    cout << "Vehículo con placa " << actual->placa << " retirado del puesto " << puesto << "." << endl;
                    actual->ocupado = false;
                    actual->placa = "";
                } else {
                    cout << "El puesto " << puesto << " está libre." << endl;
                }
                return;
            }
            actual = actual->siguiente;
        } while (actual != cabezaIzquierda);

        // Buscar en la fila derecha
        actual = cabezaDerecha;
        do {
            if (actual->puesto == puesto) {
                if (actual->ocupado) {
                    cout << "Vehículo con placa " << actual->placa << " retirado del puesto " << puesto << "." << endl;
                    actual->ocupado = false;
                    actual->placa = "";
                } else {
                    cout << "El puesto " << puesto << " está libre." << endl;
                }
                return;
            }
            actual = actual->siguiente;
        } while (actual != cabezaDerecha);

        cout << "El puesto " << puesto << " no existe." << endl;
    }

