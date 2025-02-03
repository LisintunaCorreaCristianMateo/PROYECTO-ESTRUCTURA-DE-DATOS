#include "ArbolParqueadero.h"
#include <iomanip>
#include <ctime>


ArbolParqueadero::ArbolParqueadero() {
    raiz = nullptr;
    srand(time(0));
}
ArbolParqueadero::~ArbolParqueadero() {
    liberarArbol();
}
NodoVehiculo* ArbolParqueadero::getRaiz() {
    return raiz;
}

// Implementación de los métodos de ArbolParqueadero...

void ArbolParqueadero::insertar(NodoVehiculo* nuevovehiculo) {
    raiz = insertarRecursivo(raiz, nuevovehiculo);
}

NodoVehiculo* ArbolParqueadero::insertarRecursivo(NodoVehiculo* nodo, NodoVehiculo* nuevoVehiculo) {
    if (nodo == nullptr) {
        return nuevoVehiculo;
    }
    if (nuevoVehiculo->getPuesto() < nodo->getPuesto()) { // Cambiar << por <
        nodo->setIzquierda(insertarRecursivo(nodo->getIzquierda(), nuevoVehiculo));
    } else {
        nodo->setDerecha(insertarRecursivo(nodo->getDerecha(), nuevoVehiculo));
    }
    return nodo;
}


void ArbolParqueadero::imprimirInorden() {
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

void ArbolParqueadero::imprimirInordenRecursivo(NodoVehiculo* nodo) {
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

void ArbolParqueadero::imprimirPreorden() {
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
    imprimirPreordenRecursivo(raiz);
}

void ArbolParqueadero::imprimirPreordenRecursivo(NodoVehiculo* nodo) {
    if (nodo == nullptr) {
        return;
    }
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
    imprimirPreordenRecursivo(nodo->getIzquierda());
    imprimirPreordenRecursivo(nodo->getDerecha());
}

void ArbolParqueadero::imprimirPosordenRecursivo(NodoVehiculo* nodo) {
    if (nodo == nullptr) {
        return;
    }
    imprimirPosordenRecursivo(nodo->getIzquierda());
    imprimirPosordenRecursivo(nodo->getDerecha());
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
}

void ArbolParqueadero::imprimirPosorden() {
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
    imprimirPosordenRecursivo(raiz);
}

void ArbolParqueadero::recorrerPreOrden(std::function<void(NodoVehiculo*)> func) {
    recorrerPreOrdenRecursivo(raiz, func);
}
bool ArbolParqueadero::estaVacio() {
    return raiz == nullptr;
}
void ArbolParqueadero::recorrerPreOrdenRecursivo(NodoVehiculo* nodo, std::function<void(NodoVehiculo*)> func) {
    if (nodo == nullptr) {
        return;
    }
    func(nodo);
    recorrerPreOrdenRecursivo(nodo->getIzquierda(), func);
    recorrerPreOrdenRecursivo(nodo->getDerecha(), func);
}
void ArbolParqueadero::liberarArbol() {
    liberarArbolRecursivo(raiz);
    raiz = nullptr;
}

void ArbolParqueadero::liberarArbolRecursivo(NodoVehiculo* nodo) {
    if (nodo == nullptr) {
        return;
    }
    liberarArbolRecursivo(nodo->getIzquierda());
    liberarArbolRecursivo(nodo->getDerecha());
    delete nodo;
}
// Función para verificar si un puesto ya está ocupado
bool ArbolParqueadero::puestoOcupado(int puesto, const std::unordered_set<int>& puestosOcupados) {
    return puestosOcupados.find(puesto) != puestosOcupados.end();
}

// Función para obtener todos los puestos ocupados del árbol
void ArbolParqueadero::obtenerPuestosOcupados(NodoVehiculo* nodo, std::unordered_set<int>& puestosOcupados) {
    if (nodo == nullptr) {
        return;
    }
    puestosOcupados.insert(nodo->getPuesto());
    obtenerPuestosOcupados(nodo->getIzquierda(), puestosOcupados);
    obtenerPuestosOcupados(nodo->getDerecha(), puestosOcupados);
}
void ArbolParqueadero::eliminar(string placa) {
    raiz = eliminarRecursivo(raiz, placa);
}

NodoVehiculo* ArbolParqueadero::eliminarRecursivo(NodoVehiculo* nodo, std::string placa) {
    if (nodo == nullptr) {
        return nullptr;
    }

    if (placa < nodo->getPlaca()) {
        nodo->setIzquierda(eliminarRecursivo(nodo->getIzquierda(), placa));
    } else if (placa > nodo->getPlaca()) {
        nodo->setDerecha(eliminarRecursivo(nodo->getDerecha(), placa));
    } else {
        // Nodo encontrado

        // Caso 1: Nodo sin hijos o con un solo hijo
        if (nodo->getIzquierda() == nullptr) {
            NodoVehiculo* temp = nodo->getDerecha();
            delete nodo; // Eliminar el nodo actual
            return temp; // Retornar el hijo derecho
        } else if (nodo->getDerecha() == nullptr) {
            NodoVehiculo* temp = nodo->getIzquierda();
            delete nodo; // Eliminar el nodo actual
            return temp; // Retornar el hijo izquierdo
        }

        // Caso 2: Nodo con dos hijos
        // Obtener el predecesor (máximo en el subárbol izquierdo)
        NodoVehiculo* temp = encontrarMaximo(nodo->getIzquierda());

        // Reemplazar los datos del nodo actual con los del predecesor
        nodo->setPlaca(temp->getPlaca());
        nodo->setCedula(temp->getCedula());
        nodo->setNombre(temp->getNombre());
        nodo->setSegundoNombre(temp->getSegundoNombre());
        nodo->setApellido(temp->getApellido());
        nodo->setSegundoApellido(temp->getSegundoApellido());
        nodo->setFecha(temp->getFecha());
        nodo->setHoraIngreso(temp->getHoraIngreso());

        // Eliminar el predecesor en el subárbol izquierdo
        nodo->setIzquierda(eliminarRecursivo(nodo->getIzquierda(), temp->getPlaca()));
    }

    return nodo;
}

NodoVehiculo* ArbolParqueadero::encontrarMaximo(NodoVehiculo* nodo) {
    while (nodo->getDerecha() != nullptr) {
        nodo = nodo->getDerecha();
    }
    return nodo;
}

NodoVehiculo* ArbolParqueadero::buscarPorPlaca(const std::string& placa) {
    return buscarPorPlacaRecursivo(raiz, placa);
}

NodoVehiculo* ArbolParqueadero::buscarPorPlacaRecursivo(NodoVehiculo* nodo, const std::string& placa) {
    if (nodo == nullptr) {
        return nullptr;
    }
    if (placa == nodo->getPlaca()) {
        return nodo;
    }
    if (placa < nodo->getPlaca()) {
        return buscarPorPlacaRecursivo(nodo->getIzquierda(), placa);
    } else {
        return buscarPorPlacaRecursivo(nodo->getDerecha(), placa);
    }
}

void ArbolParqueadero::buscarPorNombre(const std::string& nombre) {
    std::cout << "=========================================" << std::endl;
    std::cout << "          RESULTADOS DE LA BUSQUEDA       " << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << left << setw(10) << "Puesto"
              << setw(10) << "Placa"
              << setw(15) << "Cedula"
              << setw(15) << "Nombre"
              << setw(15) << "Segundo Nombre"
              << setw(15) << "Apellido"
              << setw(15) << "Segundo Apellido"
              << setw(15) << "Fecha"
              << setw(15) << "Hora Ingreso"
              << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

    buscarPorNombreRecursivo(raiz, nombre);
}

void ArbolParqueadero::buscarPorNombreRecursivo(NodoVehiculo* nodo, const std::string& nombre) {
    if (nodo == nullptr) {
        return;
        cout<<"Vehículo con nombre "<<nombre<<" no encontrado."<<endl;
    }
    buscarPorNombreRecursivo(nodo->getIzquierda(), nombre);
    if (nodo->getNombre() == nombre) {
        std::cout << left << setw(10) << nodo->getPuesto()
                  << setw(10) << nodo->getPlaca()
                  << setw(15) << nodo->getCedula()
                  << setw(15) << nodo->getNombre()
                  << setw(15) << nodo->getSegundoNombre()
                  << setw(15) << nodo->getApellido()
                  << setw(15) << nodo->getSegundoApellido()
                  << setw(15) << nodo->getFecha()
                  << setw(15) << nodo->getHoraIngreso()
                  << std::endl;
    }
    buscarPorNombreRecursivo(nodo->getDerecha(), nombre);
}

void ArbolParqueadero::buscarPorCedula(const std::string& cedula) {
    std::cout << "=========================================" << std::endl;
    std::cout << "          RESULTADOS DE LA BUSQUEDA       " << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << left << setw(10) << "Puesto"
              << setw(10) << "Placa"
              << setw(15) << "Cedula"
              << setw(15) << "Nombre"
              << setw(15) << "Segundo Nombre"
              << setw(15) << "Apellido"
              << setw(15) << "Segundo Apellido"
              << setw(15) << "Fecha"
              << setw(15) << "Hora Ingreso"
              << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

    buscarPorCedulaRecursivo(raiz, cedula);
}

void ArbolParqueadero::buscarPorCedulaRecursivo(NodoVehiculo* nodo, const std::string& cedula) {
    if (nodo == nullptr) {
        cout<<"Vehículo con cedula "<<cedula<<" no encontrado."<<endl;
        return;
    }
    buscarPorCedulaRecursivo(nodo->getIzquierda(), cedula);
    if (nodo->getCedula() == cedula) {
        std::cout << left << setw(10) << nodo->getPuesto()
                  << setw(10) << nodo->getPlaca()
                  << setw(15) << nodo->getCedula()
                  << setw(15) << nodo->getNombre()
                  << setw(15) << nodo->getSegundoNombre()
                  << setw(15) << nodo->getApellido()
                  << setw(15) << nodo->getSegundoApellido()
                  << setw(15) << nodo->getFecha()
                  << setw(15) << nodo->getHoraIngreso()
                  << std::endl;
    }
    buscarPorCedulaRecursivo(nodo->getDerecha(), cedula);
}

void ArbolParqueadero::buscarPlaca(const std::string& placa) {
    std::cout << "=========================================" << std::endl;
    std::cout << "          RESULTADOS DE LA BUSQUEDA       " << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << left << setw(10) << "Puesto"
              << setw(10) << "Placa"
              << setw(15) << "Cedula"
              << setw(15) << "Nombre"
              << setw(15) << "Segundo Nombre"
              << setw(15) << "Apellido"
              << setw(15) << "Segundo Apellido"
              << setw(15) << "Fecha"
              << setw(15) << "Hora Ingreso"
              << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

    buscarPlacaRecursivo(raiz, placa);
}

void ArbolParqueadero::buscarPlacaRecursivo(NodoVehiculo* nodo, const std::string& placa) {
    if (nodo == nullptr) {
        std::cout << "Vehículo con placa " << placa << " no encontrado." << std::endl;
        return;
    }
    if (placa == nodo->getPlaca()) {
        std::cout << left << setw(10) << nodo->getPuesto()
                  << setw(10) << nodo->getPlaca()
                  << setw(15) << nodo->getCedula()
                  << setw(15) << nodo->getNombre()
                  << setw(15) << nodo->getSegundoNombre()
                  << setw(15) << nodo->getApellido()
                  << setw(15) << nodo->getSegundoApellido()
                  << setw(15) << nodo->getFecha()
                  << setw(15) << nodo->getHoraIngreso()
                  << std::endl;
        std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
        return;
    }
    if (placa < nodo->getPlaca()) {
        buscarPlacaRecursivo(nodo->getIzquierda(), placa);
    } else {
        buscarPlacaRecursivo(nodo->getDerecha(), placa);
    }
}

void ArbolParqueadero::graficarArbol(NodoVehiculo* nodo, int espacio, int incremento) {
    if (nodo == nullptr) return;

    espacio += incremento;

    graficarArbol(nodo->getDerecha(), espacio);

    cout << endl;
    for (int i = incremento; i < espacio; i++) {
        cout << " ";
    }
    cout << nodo->getPuesto() << "\n";

    graficarArbol(nodo->getIzquierda(), espacio);
}

int ArbolParqueadero::obtenerAltura(NodoVehiculo* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    int alturaIzquierda = obtenerAltura(nodo->getIzquierda());
    int alturaDerecha = obtenerAltura(nodo->getDerecha());
    return max(alturaIzquierda, alturaDerecha) + 1;
}

int ArbolParqueadero::obtenerNivel(NodoVehiculo* nodo) {
    return obtenerAltura(nodo) - 1;
}

int ArbolParqueadero::obtenerProfundidad(NodoVehiculo* nodo) {
    return obtenerAltura(nodo) - 1;
}
