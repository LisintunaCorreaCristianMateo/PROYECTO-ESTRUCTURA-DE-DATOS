#include "NodoHistorial.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

NodoHistorial::NodoHistorial(int _puesto, string _placa, string _cedula, string _nombre, string _segundoNombre, string _apellido, string _segundoApellido, string _fecha, string _horaIngreso) {
    puesto = _puesto;
    placa = _placa;
    cedula = _cedula;
    nombre = _nombre;
    segundoNombre = _segundoNombre;
    apellido = _apellido;
    segundoApellido = _segundoApellido;
    fecha = _fecha;
    horaIngreso = _horaIngreso;



    ocupado = false;
    izquierda = nullptr;
    derecha = nullptr;
}

// Métodos de acceso y modificación de atributos
void NodoHistorial::setOcupado(bool estado) {
    ocupado = estado;
}

int NodoHistorial::getPuesto() {
    return puesto;
}

bool NodoHistorial::isOcupado() {
    return ocupado;
}

string NodoHistorial::getPlaca() {
    return placa;
}

string NodoHistorial::getCedula() {
    return cedula;
}

string NodoHistorial::getNombre() {
    return nombre;
}

string NodoHistorial::getSegundoNombre() {
    return segundoNombre;
}

string NodoHistorial::getApellido() {
    return apellido;
}

string NodoHistorial::getSegundoApellido() {
    return segundoApellido;
}

string NodoHistorial::getFecha() {
    return fecha;
}

string NodoHistorial::getHoraIngreso() {
    return horaIngreso;
}


NodoHistorial* NodoHistorial::getIzquierda() {
    return izquierda;
}

NodoHistorial* NodoHistorial::getDerecha() {
    return derecha;
}

void NodoHistorial::setIzquierda(NodoHistorial* nodo) {
    izquierda = nodo;
}
void NodoHistorial::setDerecha(NodoHistorial* nodo) {
    derecha = nodo;
}
