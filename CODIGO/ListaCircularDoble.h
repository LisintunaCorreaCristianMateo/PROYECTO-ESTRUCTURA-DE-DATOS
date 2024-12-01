#ifndef LISTACIRCULARDOBLE_H
#define LISTACIRCULARDOBLE_H
#include "Nodo.h"
#include <string>

// Clase ListaCircularDoble para el manejo del parqueadero
class ListaCircularDoble {
	
private:
    Nodo* cabezaIzquierda;    // Cabeza de la fila izquierda
    Nodo* cabezaDerecha;      // Cabeza de la fila derecha
    int totalPuestos;         // Número total de puestos (incluye ambos lados)
    int puestosPorLado;       // Número de puestos en cada lado

public:
	//Constructor
	ListaCircularDoble(int puestosTotales);
	
	//Destructor
	~ListaCircularDoble();
	
	//Metodos
	void insertarNodo(int puesto, bool esIzquierda);
	void dibujarParqueadero();
	void mostrarPuestosLibres();
	void ingresarVehiculo(string placa);
	void retirarVehiculo(int puesto);
    
};

#endif

