#include "ArbolHistorial.h"
#include <iomanip>
#include <ctime>
#include <windows.h>

ArbolHistorial::ArbolHistorial() {
    raiz = nullptr;
    srand(time(0));
}
ArbolHistorial::~ArbolHistorial() {
    liberarArbol();
}
NodoHistorial* ArbolHistorial::getRaiz() {
    return raiz;
}
// Implementación de los métodos de ArbolHistorial...

void ArbolHistorial::insertar(NodoHistorial* nuevovehiculo) {
    raiz = insertarRecursivo(raiz, nuevovehiculo);
}
bool ArbolHistorial::estaVacio() {
    return raiz == nullptr;
}

NodoHistorial* ArbolHistorial::insertarRecursivo(NodoHistorial* nodo, NodoHistorial* nuevoVehiculo) {
    if (nodo == nullptr) {
        return nuevoVehiculo;
    }
    if (nuevoVehiculo->getPlaca() < nodo->getPlaca()) {
        nodo->setIzquierda(insertarRecursivo(nodo->getIzquierda(), nuevoVehiculo));
    } else {
        nodo->setDerecha(insertarRecursivo(nodo->getDerecha(), nuevoVehiculo));
    }
    return nodo;
}
void ArbolHistorial::imprimirInorden() {
    cout << left << setw(10) << "Puesto" 
         << setw(10) << "Placa" 
         << setw(15) << "Cedula" 
         << setw(15) << "Nombre" 
         << setw(15) << "SegundoNombre" 
         << setw(15) << "Apellido" 
         << setw(15) << "SegundoApellido" 
         << setw(15) << "Fecha" 
         << setw(15) << "HoraIngreso" 
         << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
    imprimirInordenRecursivo(raiz);
}

void ArbolHistorial::imprimirInordenRecursivo(NodoHistorial* nodo) {
    if (nodo == nullptr) {
        return;
    }
    imprimirInordenRecursivo(nodo->getIzquierda());
    cout << left << setw(10) << nodo->getPuesto() 
         << setw(10) << nodo->getPlaca() 
         << setw(15) << nodo->getCedula() 
         << setw(15) << nodo->getNombre() 
         << setw(15) << nodo->getSegundoNombre() 
         << setw(15) << nodo->getApellido() 
         << setw(15) << nodo->getSegundoApellido() 
         << setw(15) << nodo->getFecha() 
         << setw(15) << nodo->getHoraIngreso() 
         << endl;
    imprimirInordenRecursivo(nodo->getDerecha());
}
void ArbolHistorial::liberarArbol() {
    liberarArbolRecursivo(raiz);
    raiz = nullptr;
}
void ArbolHistorial::liberarArbolRecursivo(NodoHistorial* nodo) {
    if (nodo == nullptr) {
        return;
    }
    liberarArbolRecursivo(nodo->getIzquierda());
    liberarArbolRecursivo(nodo->getDerecha());
    delete nodo;
}

void ArbolHistorial::recorrerPreOrden(std::function<void(NodoHistorial*)> func) {
    recorrerPreOrdenRecursivo(raiz, func);
}

void ArbolHistorial::recorrerPreOrdenRecursivo(NodoHistorial* nodo, std::function<void(NodoHistorial*)> func) {
    if (nodo == nullptr) {
        return;
    }
    func(nodo);
    recorrerPreOrdenRecursivo(nodo->getIzquierda(), func);
    recorrerPreOrdenRecursivo(nodo->getDerecha(), func);
}


// Función para buscar un nodo en el historial por placa
NodoHistorial* ArbolHistorial::buscarEnHistorial(const std::string& placa) {
    NodoHistorial* resultado = nullptr;
    recorrerPreOrden([&resultado, &placa](NodoHistorial* nodo) {
        if (nodo->getPlaca() == placa) {
            resultado = nodo;
        }
    });
    return resultado;
}

void ArbolHistorial::imprimirHistorialInordenRecursivo(NodoHistorial* nodo) {
    if (nodo == nullptr) {
        return;
    }
    imprimirHistorialInordenRecursivo(nodo->getIzquierda());
    cout << left << setw(10) << nodo->getPuesto() 
         << setw(10) << nodo->getPlaca() 
         << setw(15) << nodo->getCedula() 
         << setw(15) << nodo->getNombre() 
         << setw(15) << nodo->getSegundoNombre() 
         << setw(15) << nodo->getApellido() 
         << setw(15) << nodo->getSegundoApellido() 
         << setw(15) << nodo->getFecha() 
         << setw(15) << nodo->getHoraIngreso() 
         << endl;
    imprimirHistorialInordenRecursivo(nodo->getDerecha());
}

void ArbolHistorial::imprimirHistorialInorden() {
    cout << left << setw(10) << "Puesto" 
         << setw(10) << "Placa" 
         << setw(15) << "Cedula" 
         << setw(15) << "Nombre" 
         << setw(15) << "SegundoNombre" 
         << setw(15) << "Apellido" 
         << setw(15) << "SegundoApellido" 
         << setw(15) << "Fecha" 
         << setw(15) << "HoraIngreso" 
         << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
    imprimirHistorialInordenRecursivo(raiz);
}

void ArbolHistorial::graficarArbolHistorialRecursivo(NodoHistorial* nodo, int espacio, int incremento) {
    if (nodo == nullptr) return;

    espacio += incremento;

    graficarArbolHistorialRecursivo(nodo->getDerecha(), espacio, incremento);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10); // Cambiar color a verde
    cout << endl;
    for (int i = incremento; i < espacio; i++) cout << " ";
    cout << nodo->getPlaca() << "\n";
    SetConsoleTextAttribute(hConsole, 7); // Volver al color normal

    graficarArbolHistorialRecursivo(nodo->getIzquierda(), espacio, incremento);
}

void ArbolHistorial::graficarArbolHistorial(NodoHistorial* nodo, int espacio, int incremento) {
    graficarArbolHistorialRecursivo(nodo, espacio, incremento);
}
