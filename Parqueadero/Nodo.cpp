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
Nodo::~Nodo(){
	
}

        // Getters
    int Nodo::getPuesto() {
     return puesto; }

    bool Nodo::isOcupado()  {
     return ocupado; }

    string Nodo::getPlaca()  {
     return placa; }

    string Nodo::gethoraIngreso()  {
     return horaIngreso; }

    string Nodo::gethoraSalida()  {
     return horaSalida; }

    string Nodo::getNombre(){
    return nombre;
    }

    string Nodo::getSegundoNombre(){
    return segundoNombre;
    }

    string Nodo::getApellido(){
    return apellido;
    }
    
    string Nodo::getSegundoApellido(){
    return segundoApellido;
    }

    string Nodo::getCedula(){
    return cedula;
    }
    string Nodo::getFecha(){
    return fecha;
    }

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

    void Nodo::setCedula(string _cedula ){
        cedula=_cedula;
    }
    void Nodo::setNombre(string _nombre){
        nombre=_nombre;
    }

    void Nodo::setSegundoNombre(string _segundoNombre){
        segundoNombre=_segundoNombre;
    }

    void Nodo::setApellido(string _apellido){
        apellido=_apellido;
    }

    void Nodo::setSegundoApellido(string _segundoApellido){
        segundoApellido=_segundoApellido;
    }

    void Nodo::setHoraIngreso(string _horaIngreso){
        horaIngreso=_horaIngreso;
    }
    void Nodo::setHoraSalida(string _horaSalida){
       horaSalida=_horaSalida;
      
    }

    void Nodo::setFecha(string _fecha){
        fecha=_fecha;
    }