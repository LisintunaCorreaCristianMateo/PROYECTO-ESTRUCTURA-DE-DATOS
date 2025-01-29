#ifndef ARBOLHISTORIAL_H
#define ARBOLHISTORIAL_H
#include "NodoHistorial.h"
#include <functional>
#include <string>
#include <iostream>
#include <unordered_set>
using namespace std;
class ArbolHistorial {
private:
    NodoHistorial* raiz;

    NodoHistorial* insertarRecursivo(NodoHistorial* nodo, NodoHistorial* nuevoVehiculo);
     void recorrerPreOrdenRecursivo(NodoHistorial* nodo, std::function<void(NodoHistorial*)> func);
    void imprimirInordenRecursivo(NodoHistorial* nodo);
    void liberarArbolRecursivo(NodoHistorial* nodo);   

public:
    ArbolHistorial();
    ~ArbolHistorial();
    NodoHistorial* getRaiz();

    void insertar(NodoHistorial* nuevoVehiculo);
    void imprimirInorden();
    NodoHistorial* buscarEnHistorial(const std::string& placa);
    void recorrerPreOrden(std::function<void(NodoHistorial*)> func);
    void liberarArbol();
    bool estaVacio();

};

#endif