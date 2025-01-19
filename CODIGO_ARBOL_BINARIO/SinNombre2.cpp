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

    string obtenerFechaActual() {
        time_t now = time(0);
        tm* tiempo = localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", tiempo);
        return string(buffer);
    }

    string obtenerHoraActual() {
        time_t now = time(0);
        tm* tiempo = localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%H:%M:%S", tiempo);
        return string(buffer);
    }

public:
    Nodo(int valor) : puesto(valor), ocupado(false), izquierda(nullptr), derecha(nullptr) {}

    void setOcupado(bool estado) { ocupado = estado; }

    int getPuesto() { return puesto; }
    bool isOcupado() { return ocupado; }
    string getPlaca() { return placa; }
    string getCedula() { return cedula; }
    string getNombre() { return nombre; }
    string getSegundoNombre() { return segundoNombre; }
    string getApellido() { return apellido; }
    string getSegundoApellido() { return segundoApellido; }
    string getFecha() { return fecha; }
    string getHoraIngreso() { return horaIngreso; }
    string getHoraSalida() { return horaSalida; }

    Nodo* getIzquierda() { return izquierda; }
    Nodo* getDerecha() { return derecha; }
    void setIzquierda(Nodo* nodo) { izquierda = nodo; }
    void setDerecha(Nodo* nodo) { derecha = nodo; }

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
        fecha = obtenerFechaActual();
        horaIngreso = obtenerHoraActual();
        ocupado = true;
    }

    void liberarDatos() {
        ocupado = false;
        placa = cedula = nombre = segundoNombre = apellido = segundoApellido = fecha = horaIngreso = horaSalida = "";
    }

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

    void mostrarVehiculo() {
        if (ocupado) {
            cout << "Puesto: " << puesto << " | Placa: " << placa << "\n";
        }
    }
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


    Nodo* crearParqueadero(int inicio, int fin) {
        if (inicio > fin) return nullptr;

        int medio = (inicio + fin) / 2;
        Nodo* raiz = new Nodo(medio);

        raiz->setIzquierda(crearParqueadero(inicio, medio - 1));
        raiz->setDerecha(crearParqueadero(medio + 1, fin));

        return raiz;
    }

    int contarPuestosLibres(Nodo* raiz) {
        if (raiz == nullptr) return 0;
        return (!raiz->isOcupado() ? 1 : 0) + contarPuestosLibres(raiz->getIzquierda()) + contarPuestosLibres(raiz->getDerecha());
    }

    bool existeAutos(Nodo* raiz) {
        if (raiz == nullptr) return false;
        if (raiz->isOcupado()) return true;
        return existeAutos(raiz->getIzquierda()) || existeAutos(raiz->getDerecha());
    }

    void mostrarVehiculos(Nodo* raiz) {
        if (raiz == nullptr) return;
        mostrarVehiculos(raiz->getIzquierda());
        raiz->mostrarVehiculo();
        mostrarVehiculos(raiz->getDerecha());
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

    void mostrarVehiculos() {
        cout << "\nVehículos registrados:\n";
        mostrarVehiculos(raiz);
    }
    
    
    
void ImprimirPropietario(Nodo* nodo) {
    if (nodo == nullptr) return; // Verifica que el nodo no sea nulo

    // Imprimir datos del propietario
    cout << left << setw(15) << nodo->getCedula() 
         << setw(20) << (nodo->getNombre() + " " + nodo->getSegundoNombre()) 
         << setw(20) << (nodo->getApellido() + " " + nodo->getSegundoApellido()) 
         << setw(10) << nodo->getPlaca() << endl;
}

void encontrarPropietaro(Nodo* raiz) {
	if (raiz == nullptr) return;
	
	    encontrarPropietaro(raiz->getIzquierda());
	
	    // Verifica si el propietario está ocupado antes de mostrarlo
	    if (raiz->isOcupado()) {
	        ImprimirPropietario(raiz); // Pasa el nodo actual a la función
	    }
	
	    encontrarPropietaro(raiz->getDerecha());
}

    void mostrarDatosPropietarios() {
    

    bool resultado = existeAutos(raiz);
    if (resultado ==true){
    	    	
    	cout << "--- Detalles del Puesto y Vehículo ---\n";


    // Encabezados de columnas
    cout << left << setw(10) << "Puesto" 
         << setw(10) << "Placa" 
         << setw(15) << "Cedula" 
         << setw(20) << "Nombre" 
         << setw(20) << "Apellido" 
         << setw(15) << "Fecha" 
         << setw(10) << "Hora" << endl;
    cout << string(100, '-') << endl;
    
    encontrarPropietaro(raiz);
	}
	else{
		std::cout << "No hay autos en el parqueadero" << std::endl;
	}
}

};

int main() {
    Parqueadero parqueadero(1, 40); // Crear el parqueadero con puestos del 1 al 40
    int opcion, puesto;

   do {
        cout << "\n--- Menu ---\n";
        cout << "1. Registrar un vehiculo\n";
        cout << "2. Liberar un vehiculo\n";
        cout << "3. Mostrar parqueadero\n";
        cout << "4. Mostrar datos de propietarios\n";
        cout << "5. Mostrar vehículos registrados\n";
        cout << "6. Salir\n";
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
                parqueadero.mostrarDatosPropietarios();
                break;
            case 5:
                parqueadero.mostrarVehiculos();
                break;
            case 6:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida, por favor elige otra.\n";
        }
    } while (opcion != 6);

    return 0;
}

