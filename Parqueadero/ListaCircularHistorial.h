#ifndef LISTACIRCULARHISTORIAL_H
#define LISTACIRCULARHISTORIAL_H
#include "Historial.h"
#include "ListaCircularDoble.h"
#include <string>
using namespace std;

class ListaCircularHistorial {

private:
    Historial* cabeza;  // Puntero único a la lista circular

public:
    // Constructor
    ListaCircularHistorial() : cabeza(nullptr) {}

    // Destructor
    ~ListaCircularHistorial();

    // Getter
    Historial* getCabeza() {
        return cabeza;
    }
    
    void setCabeza(Historial* _cabeza) {
    cabeza = _cabeza;
    }

   void limpiarLista() {
    if (!cabeza) {
        return; // La lista ya est� vac�a
    }

    Historial* actual = cabeza;
    do {
        Historial* siguiente = actual->getSiguiente(); // Almacenar el siguiente nodo
        delete actual; // Liberar memoria del nodo actual
        actual = siguiente; // Avanzar al siguiente nodo
    } while (actual != cabeza); // Repetir hasta volver a la cabeza

    cabeza = nullptr; // Despu�s de eliminar todos los nodos, la lista queda vac�a
}



    void ingresarVehiculo(int puesto,string placa, string cedula, string nombre, 
                          string nombre2, string apellido, string apellido2,string fecha, string horaIngreso);
    
    
    // Métodos para imprimir

    void mostrarHistorial();
    void cambiarFechaSalida(string placa, string hora );
    void agregarAlFinal(Historial* nuevo);
    void buscarPorFecha(const string& fechaBuscada);
    bool existeVehiculoHistorial(string placa,ListaCircularDoble &parqueadero);

   

};

#endif
