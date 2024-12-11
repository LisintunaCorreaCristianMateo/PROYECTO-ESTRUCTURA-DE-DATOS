#include "Historial.h"
#include <iostream>

using namespace std;

Historial::Historial(int _puesto, string _placa,string _cedula,string _nombre,string _segundoNombre, string _apellido, string _segundoApellido,string _fecha,string _horaIngreso,string _horaSalida){
	puesto=_puesto;
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
Historial::~Historial(){
	
}

        // Getters
    int Historial::getPuesto() {
     return puesto; }

    string Historial::getPlaca()  {
     return placa; }

    string Historial::gethoraIngreso()  {
     return horaIngreso; }

    string Historial::gethoraSalida()  {
     return horaSalida; }

    string Historial::getNombre(){
    return nombre;
    }

    string Historial::getSegundoNombre(){
    return segundoNombre;
    }

    string Historial::getApellido(){
    return apellido;
    }
    
    string Historial::getSegundoApellido(){
    return segundoApellido;
    }

    string Historial::getCedula(){
    return cedula;
    }
    string Historial::getFecha(){
    return fecha;
    }

    Historial* Historial::getSiguiente()  {
     return siguiente; }

    Historial* Historial::getAnterior()  {
     return anterior; }

    // Setters

    void Historial::setPlaca( string value) {
         placa = value; }

    void Historial::setSiguiente(Historial* nodo) { 
        siguiente = nodo; }
        
    void Historial::setAnterior(Historial* nodo) { 
        anterior = nodo; }

    void Historial::setCedula(string _cedula ){
        cedula=_cedula;
    }
    void Historial::setNombre(string _nombre){
        nombre=_nombre;
    }

    void Historial::setSegundoNombre(string _segundoNombre){
        segundoNombre=_segundoNombre;
    }

    void Historial::setApellido(string _apellido){
        apellido=_apellido;
    }

    void Historial::setSegundoApellido(string _segundoApellido){
        segundoApellido=_segundoApellido;
    }

    void Historial::setHoraIngreso(string _horaIngreso){
        horaIngreso=_horaIngreso;
    }
    void Historial::setHoraSalida(string _horaSalida){
       horaSalida=_horaSalida;
      
    }

    void Historial::setFecha(string _fecha){
        fecha=_fecha;
    }