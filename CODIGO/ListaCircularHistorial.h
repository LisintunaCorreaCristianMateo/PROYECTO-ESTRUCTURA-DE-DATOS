#ifndef LISTACIRCULARHISTORIAL_H
#define LISTACIRCULARHISTORIAL_H
#include "Historial.h"
#include <string>
using namespace std;

class ListaCircularHistorial {

private:
    Historial* cabeza;  // Puntero Ãºnico a la lista circular

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

    void ingresarVehiculo(int puesto,string placa, string cedula, string nombre, 
                          string nombre2, string apellido, string apellido2,string fecha, string horaIngreso);
    
    
    // MÃ©todos para imprimir

    void mostrarHistorial();

    Historial* buscarPorHora(const string& hora) {
        Historial* actual = cabeza;
        do {
            if (actual->horaIngreso == hora) {
                return actual; // Retorna el nodo si la hora coincide
            }
            actual = actual->siguiente;
        } while (actual != cabeza);
        return nullptr; // Si no se encuentra ningún vehículo con esa hora
    }

};

#endif
