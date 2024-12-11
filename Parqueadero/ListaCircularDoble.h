#ifndef LISTACIRCULARDOBLE_H
#define LISTACIRCULARDOBLE_H
#include "Nodo.h"
#include <string>

// Clase ListaCircularDoble para el manejo del parqueadero
class ListaCircularDoble {
	
private:
    Nodo* cabezaIzquierda;    // Cabeza de la fila izquierda
    Nodo* cabezaDerecha;      // Cabeza de la fila derecha
    int totalPuestos;         // N�mero total de puestos (incluye ambos lados)
    int puestosPorLado;       // N�mero de puestos en cada lado

public:
	//Constructor
	ListaCircularDoble(int puestosTotales);
	
	//Destructor
	~ListaCircularDoble();

	//geter

	Nodo* getCabezaIzquierda(){
		return cabezaIzquierda;
	}
	
	Nodo* getCabezaDerecha(){
		return cabezaDerecha;
	}

	
	//Metodos
	void insertarNodo(int puesto, bool esIzquierda);
	void dibujarParqueadero();
	void mostrarPuestosLibres();
	void ingresarVehiculo(string placa,string cedula,string nombre,string nombre2,string apellido,string apellido2);
	void retirarVehiculo(int puesto);
    //Metodos para imprimir
	void mostrarDatos();
	void mostrarAutos();
	bool existePlaca(const string& placa);
	

};

#endif

