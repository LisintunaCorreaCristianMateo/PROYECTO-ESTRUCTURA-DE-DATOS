#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Clase Nodo que representa cada espacio del parqueadero
class Nodo {
private:
    int puesto;              // Número del puesto
    bool ocupado;            // Si el puesto está ocupado o no
    string placa;            // Placa del vehículo (si está ocupado)
    string cedula;
    string nombre;
    string segundoNombre;
    string apellido;
    string segundoApellido;
    string fecha;
    string horaIngreso;
    string horaSalida;

    Nodo* izquierda;
    Nodo* derecha;

public:
    Nodo(int valor) : puesto(valor), ocupado(false), izquierda(nullptr), derecha(nullptr) {}

    int getPuesto() { return puesto; }
    bool isOcupado() { return ocupado; }
    void setOcupado(bool estado) { ocupado = estado; }

    void llenarDatos() {
        
        cout << "Placa del vehículo: ";
        cin >> placa;
        cout << "Cédula: ";
        cin >> cedula;
        cout << "Nombre: ";
        cin >> nombre;
        cout << "Segundo Nombre: ";
        cin >> segundoNombre;
        cout << "Apellido: ";
        cin >> apellido;
        cout << "Segundo Apellido: ";
        cin >> segundoApellido;
        cout << "Fecha de ingreso: ";
        cin >> fecha;
        cout << "Hora de ingreso: ";
        cin >> horaIngreso;
        ocupado = true;
    }

    void liberarDatos() {
        ocupado = false;
        placa = cedula = nombre = segundoNombre = apellido = segundoApellido = fecha = horaIngreso = horaSalida = "";
    }

    Nodo* getIzquierda() { return izquierda; }
    Nodo* getDerecha() { return derecha; }
    void setIzquierda(Nodo* nodo) { izquierda = nodo; }
    void setDerecha(Nodo* nodo) { derecha = nodo; }

    void imprimirDatos() {
        cout << "Puesto: " << puesto << (ocupado ? " [Ocupado]" : " [Libre]") << "\n";
        if (ocupado) {
            cout << "  Placa: " << placa << "\n";
            cout << "  Cédula: " << cedula << "\n";
            cout << "  Nombre: " << nombre << " " << segundoNombre << "\n";
            cout << "  Apellido: " << apellido << " " << segundoApellido << "\n";
            cout << "  Fecha de ingreso: " << fecha << "\n";
            cout << "  Hora de ingreso: " << horaIngreso << "\n";
        }
    }

    string getPlaca() { return placa; }
};

class Parqueadero {
private:
    Nodo* raiz;

    Nodo* insertar(Nodo* raiz, int valor) {
        if (raiz == nullptr) {
            return new Nodo(valor);
        }

        if (valor < raiz->getPuesto()) {
            raiz->setIzquierda(insertar(raiz->getIzquierda(), valor));
        } else {
            raiz->setDerecha(insertar(raiz->getDerecha(), valor));
        }

        return raiz;
    }

    Nodo* crearParqueadero(int inicio, int fin) {
        if (inicio > fin) return nullptr;

        int medio = (inicio + fin) / 2;
        Nodo* raiz = new Nodo(medio);

        raiz->setIzquierda(crearParqueadero(inicio, medio - 1));
        raiz->setDerecha(crearParqueadero(medio + 1, fin));

        return raiz;
    }

    Nodo* buscarPuestoLibre(Nodo* raiz, int& contador, int objetivo) {
        if (raiz == nullptr) return nullptr;

        Nodo* nodoIzq = buscarPuestoLibre(raiz->getIzquierda(), contador, objetivo);
        if (nodoIzq != nullptr) return nodoIzq;

        if (!raiz->isOcupado()) {
            contador++;
            if (contador == objetivo) return raiz;
        }

        Nodo* nodoDer = buscarPuestoLibre(raiz->getDerecha(), contador, objetivo);
        return nodoDer;
    }

    void imprimirArbol(Nodo* raiz, int nivel) {
        if (raiz == nullptr) return;

        imprimirArbol(raiz->getDerecha(), nivel + 1);

        for (int i = 0; i < nivel; ++i) {
            cout << "    ";
        }

        if (raiz->isOcupado()) {
            cout << "\033[1;31m" << raiz->getPuesto() << " [" << raiz->getPlaca() << "]\033[0m" << endl;
        } else {
            cout << raiz->getPuesto() << " [Libre]" << endl;
        }

        imprimirArbol(raiz->getIzquierda(), nivel + 1);
    }

    int contarPuestosLibres(Nodo* raiz) {
        if (raiz == nullptr) return 0;
        return (!raiz->isOcupado() ? 1 : 0) + contarPuestosLibres(raiz->getIzquierda()) + contarPuestosLibres(raiz->getDerecha());
    }

public:
    Parqueadero(int inicio, int fin) {
        raiz = crearParqueadero(inicio, fin);
        srand(time(0));
    }

    void ocuparPuesto() {
        int puestosLibres = contarPuestosLibres(raiz);
        if (puestosLibres == 0) {
            cout << "No hay puestos disponibles.\n";
            return;
        }

        int puestoAleatorio = rand() % puestosLibres + 1;
        int contador = 0;
        Nodo* nodo = buscarPuestoLibre(raiz, contador, puestoAleatorio);
        if (nodo != nullptr) {
            nodo->llenarDatos();
            cout << "Vehículo registrado en el puesto " << nodo->getPuesto() << ".\n";
        }
    }

    void liberarPuesto(int puesto) {
        Nodo* nodo = buscarPuestoLibre(raiz, puesto, puesto);
        if (nodo == nullptr || !nodo->isOcupado()) {
            cout << "El puesto " << puesto << " ya está libre o no existe.\n";
            return;
        }
        nodo->liberarDatos();
        cout << "Puesto " << puesto << " liberado con éxito.\n";
    }

    void mostrarParqueadero() {
        cout << "\nEstado actual del parqueadero: \n";
        imprimirArbol(raiz, 0);
    }
};

int main() {
    Parqueadero parqueadero(1, 40); // Crear el parqueadero con puestos del 1 al 40
    int opcion, puesto;

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Ocupar un puesto\n";
        cout << "2. Liberar un puesto\n";
        cout << "3. Mostrar parqueadero\n";
        cout << "4. Salir\n";
        cout << "Elige una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                parqueadero.ocuparPuesto();
                break;
            case 2:
                cout << "Ingresa el número del puesto a liberar: ";
                cin >> puesto;
                parqueadero.liberarPuesto(puesto);
                break;
            case 3:
                parqueadero.mostrarParqueadero();
                break;
            case 4:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida, por favor elige otra.\n";
        }
    } while (opcion != 4);

    return 0;
}

