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
    void imprimirHistorialInordenRecursivo(NodoHistorial* nodo);
    void graficarArbolHistorialRecursivo(NodoHistorial* nodo, int espacio, int incremento);

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
    void imprimirHistorialInorden();
    void graficarArbolHistorial(NodoHistorial* nodo, int espacio = 0, int incremento = 10);

};

#endif