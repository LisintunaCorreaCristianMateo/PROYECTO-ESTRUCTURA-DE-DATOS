#ifndef ARBOLPARQUEADERO_H
#define ARBOLPARQUEADERO_H

#include "NodoVehiculo.h"
#include <functional>
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;
class ArbolParqueadero {
private:
    NodoVehiculo* raiz;

    NodoVehiculo* insertarRecursivo(NodoVehiculo* nodo, NodoVehiculo* nuevoVehiculo);
    void recorrerPreOrdenRecursivo(NodoVehiculo* nodo, std::function<void(NodoVehiculo*)> func);
    void imprimirInordenRecursivo(NodoVehiculo* nodo);
    void liberarArbolRecursivo(NodoVehiculo* nodo);    
    NodoVehiculo*eliminarRecursivo(NodoVehiculo* nodo, std::string nombre);
    NodoVehiculo*encontrarMaximo(NodoVehiculo* nodo);
    NodoVehiculo* buscarPorPlacaRecursivo(NodoVehiculo* nodo, const std::string& placa);
    void buscarPorNombreRecursivo(NodoVehiculo* nodo, const std::string& nombre);
    void buscarPorCedulaRecursivo(NodoVehiculo* nodo, const std::string& cedula);
    void buscarPlacaRecursivo(NodoVehiculo* nodo, const std::string& placa);
    void imprimirPreordenRecursivo(NodoVehiculo* nodo);

public:
    ArbolParqueadero();
    ~ArbolParqueadero();
    NodoVehiculo* getRaiz();

    void insertar(NodoVehiculo* nuevaMascota);
    void imprimirInorden();
    void recorrerPreOrden(std::function<void(NodoVehiculo*)> func);
    void liberarArbol();
    bool estaVacio();
    void eliminar(string placa);
    NodoVehiculo* buscarPorPlaca(const std::string& placa);
    void buscarPorNombre(const std::string& nombre);
    void buscarPorCedula(const std::string& cedula);
    void buscarPlaca(const std::string& placa);
    void imprimirPreorden();
    
    bool puestoOcupado(int puesto, const std::unordered_set<int>& puestosOcupados);
    void obtenerPuestosOcupados(NodoVehiculo* nodo, std::unordered_set<int>& puestosOcupados);
    void graficarArbol(NodoVehiculo* nodo, int espacio = 0, int incremento = 10);

};

#endif
