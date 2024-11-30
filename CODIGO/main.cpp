#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Clase Nodo que representa cada espacio del parqueadero
class Nodo {
public:
    int puesto;              // N�mero del puesto
    bool ocupado;            // Si el puesto est� ocupado o no
    string placa;            // Placa del veh�culo (si est� ocupado)
    Nodo* siguiente;         // Apunta al siguiente nodo
    Nodo* anterior;          // Apunta al nodo anterior

    Nodo(int p) : puesto(p), ocupado(false), placa(""), siguiente(nullptr), anterior(nullptr) {}
};

// Clase ListaCircularDoble para el manejo del parqueadero
class ListaCircularDoble {
private:
    Nodo* cabezaIzquierda;    // Cabeza de la fila izquierda
    Nodo* cabezaDerecha;      // Cabeza de la fila derecha
    int totalPuestos;         // N�mero total de puestos (incluye ambos lados)
    int puestosPorLado;       // N�mero de puestos en cada lado

public:
    ListaCircularDoble(int puestosTotales) : cabezaIzquierda(nullptr), cabezaDerecha(nullptr), totalPuestos(puestosTotales) {
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

    // Funci�n para insertar un nodo en la lista circular
    void insertarNodo(int puesto, bool esIzquierda) {
        Nodo* nuevo = new Nodo(puesto);
        if (esIzquierda) {
            if (!cabezaIzquierda) { // Si la lista izquierda est� vac�a
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
            if (!cabezaDerecha) { // Si la lista derecha est� vac�a
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

    // Funci�n para dibujar el parqueadero en forma de anillo
    void dibujarParqueadero() {
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

        // Dibujar la v�a (l�nea de guiones)
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

    // Funci�n para determinar los puestos vac�os
    void mostrarPuestosLibres() {
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

    // Funci�n para ingresar un veh�culo en un puesto vac�o aleatorio
    void ingresarVehiculo(string placa) {
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

        // Seleccionar un puesto vac�o aleatorio
        srand(time(0));
        int indiceAleatorio = rand() % puestosLibres.size();
        Nodo* puestoSeleccionado = puestosLibres[indiceAleatorio];

        // Asignar el veh�culo al puesto seleccionado
        puestoSeleccionado->ocupado = true;
        puestoSeleccionado->placa = placa;

        cout << "Veh�culo con placa " << placa << " ingresado en el puesto " << puestoSeleccionado->puesto << "." << endl;
    }

    // Funci�n para eliminar un veh�culo
    void retirarVehiculo(int puesto) {
        Nodo* actual = cabezaIzquierda;

        // Buscar en la fila izquierda
        do {
            if (actual->puesto == puesto) {
                if (actual->ocupado) {
                    cout << "Veh�culo con placa " << actual->placa << " retirado del puesto " << puesto << "." << endl;
                    actual->ocupado = false;
                    actual->placa = "";
                } else {
                    cout << "El puesto " << puesto << " est� libre." << endl;
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
                    cout << "Veh�culo con placa " << actual->placa << " retirado del puesto " << puesto << "." << endl;
                    actual->ocupado = false;
                    actual->placa = "";
                } else {
                    cout << "El puesto " << puesto << " est� libre." << endl;
                }
                return;
            }
            actual = actual->siguiente;
        } while (actual != cabezaDerecha);

        cout << "El puesto " << puesto << " no existe." << endl;
    }
};

// Funci�n principal
int main() {
    int totalPuestos = 100; // Total de puestos (6 a cada lado)
    ListaCircularDoble parqueadero(totalPuestos);

    int opcion;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Dibujar parqueadero\n";
        cout << "2. Ver puestos libres\n";
        cout << "3. Ingresar veh�culo\n";
        cout << "4. Retirar veh�culo\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opci�n: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            parqueadero.dibujarParqueadero();
            break;
        case 2:
            parqueadero.mostrarPuestosLibres();
            break;
        case 3: {
            string placa;
            cout << "Ingrese la placa del veh�culo: ";
            cin >> placa;
            parqueadero.ingresarVehiculo(placa);
            break;
        }
        case 4: {
            int puesto;
            cout << "Ingrese el n�mero del puesto a liberar: ";
            cin >> puesto;
            parqueadero.retirarVehiculo(puesto);
            break;
        }
        case 5:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opci�n inv�lida. Intente nuevamente." << endl;
        }
    } while (opcion != 5);

    return 0;
}

