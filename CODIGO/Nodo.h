#ifndef NODO_H
#define NODO_H
#include <string>
#include <iostream>
using namespace std;

// Clase Nodo que representa cada espacio del parqueadero
class Nodo {
private:
    int puesto;              // N�mero del puesto
    bool ocupado;            // Si el puesto est� ocupado o no
    string placa;            // Placa del veh�culo (si est� ocupado)
    string cedula;
    string nombre;
    string segundoNombre;
    string apellido;
    string segundoApellido;
    string fecha;
    string horaIngreso;
    string horaSalida;
    
    Nodo* siguiente;         // Apunta al siguiente nodo
    Nodo* anterior;          // Apunta al nodo anterior

public:
	//constructor 1
	Nodo(int _puesto, string _placa,string _cedula,string _nombre,string _segundoNombre, string _apellido, string _segundoApellido,string _fecha,string _horaIngreso,string _horaSalida);
	//constructor2
	Nodo(int puesto);
	//Destructor
	~Nodo();
    
        // Getters
    int getPuesto();

    bool isOcupado();

    string getPlaca();

    string gethoraIngreso();

    string gethoraSalida();

    Nodo* getSiguiente();

    Nodo* getAnterior();

    // Setters
    void setOcupado(bool value);

    void setPlaca( string value);

    void setSiguiente(Nodo* nodo);

    void setAnterior(Nodo* nodo);


};
#endif

