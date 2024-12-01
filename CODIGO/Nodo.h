#ifndef NODO_H
#define NODO_H
#include <string>
#include <iostream>
using namespace std;

// Clase Nodo que representa cada espacio del parqueadero
class Nodo {
public:
    int puesto;              // Número del puesto
    bool ocupado;            // Si el puesto está ocupado o no
    string placa;            // Placa del vehículo (si está ocupado)
    Nodo* siguiente;         // Apunta al siguiente nodo
    Nodo* anterior;          // Apunta al nodo anterior

	//constructor
	Nodo(int);
	//Destructor
	~Nodo();
    
};
#endif

