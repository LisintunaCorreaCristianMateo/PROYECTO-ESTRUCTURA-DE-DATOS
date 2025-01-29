#include "NodoVehiculo.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

NodoVehiculo::NodoVehiculo(int _puesto, string _placa, string _cedula, string _nombre, string _segundoNombre, string _apellido, string _segundoApellido, string _fecha, string _horaIngreso) {
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
void NodoVehiculo::setOcupado(bool estado) {
    ocupado = estado;
}

int NodoVehiculo::getPuesto() {
    return puesto;
}

bool NodoVehiculo::isOcupado() {
    return ocupado;
}

string NodoVehiculo::getPlaca() {
    return placa;
}

string NodoVehiculo::getCedula() {
    return cedula;
}

string NodoVehiculo::getNombre() {
    return nombre;
}

string NodoVehiculo::getSegundoNombre() {
    return segundoNombre;
}

string NodoVehiculo::getApellido() {
    return apellido;
}

string NodoVehiculo::getSegundoApellido() {
    return segundoApellido;
}

string NodoVehiculo::getFecha() {
    return fecha;
}

string NodoVehiculo::getHoraIngreso() {
    return horaIngreso;
}


NodoVehiculo* NodoVehiculo::getIzquierda() {
    return izquierda;
}

NodoVehiculo* NodoVehiculo::getDerecha() {
    return derecha;
}


void NodoVehiculo::setPuesto(int _puesto) { puesto = _puesto; }
void NodoVehiculo::setPlaca(string _placa) { placa = _placa; }
void NodoVehiculo::setCedula(string _cedula) { cedula = _cedula; }
void NodoVehiculo::setNombre(string _nombre) { nombre = _nombre; }
void NodoVehiculo::setSegundoNombre(string _segundoNombre) { segundoNombre = _segundoNombre; }
void NodoVehiculo::setApellido(string _apellido) { apellido = _apellido; }
void NodoVehiculo::setSegundoApellido(string _segundoApellido) { segundoApellido = _segundoApellido; }
void NodoVehiculo::setFecha(string _fecha) { fecha = _fecha; }
void NodoVehiculo::setHoraIngreso(string _horaIngreso) { horaIngreso = _horaIngreso; }
void NodoVehiculo::setIzquierda(NodoVehiculo* nodo) { izquierda = nodo; }
void NodoVehiculo::setDerecha(NodoVehiculo* nodo) { derecha = nodo; }