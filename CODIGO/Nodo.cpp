#include "Nodo.h"
#include <iostream>
using namespace std;

Nodo::Nodo(int _puesto, string _placa,string _cedula,string _nombre,string _segundoNombre, string _apellido, string _segundoApellido,string _fecha,string _horaIngreso,string _horaSalida){
	puesto=_puesto;
	ocupado=false;
	placa=_placa;
	cedula=_cedula;
    nombre=_nombre;
    segundoNombre=_segundoNombre;
    apellido=_apellido;
    segundoApellido=_segundoApellido;
    fecha=_fecha;
    horaIngreso=_horaIngreso;
    horaSalida=_horaSalida;

	siguiente=NULL;
	anterior=NULL;
}
Nodo::Nodo(int _puesto){
    puesto=_puesto;
}
Nodo::~Nodo(){
	
}

        // Getters
    int Nodo::getPuesto() {
         return puesto; }

    bool Nodo::isOcupado()  {
         return ocupado; }

    string Nodo::getPlaca()  {
         return placa; }

    Nodo* Nodo::getSiguiente()  {
         return siguiente; }

    Nodo* Nodo::getAnterior()  {
         return anterior; }

    // Setters
    void Nodo::setOcupado(bool value) {
         ocupado = value; }

    void Nodo::setPlaca( string value) {
         placa = value; }

    void Nodo::setSiguiente(Nodo* nodo) { 
        siguiente = nodo; }
        
    void Nodo::setAnterior(Nodo* nodo) { 
        anterior = nodo; }
