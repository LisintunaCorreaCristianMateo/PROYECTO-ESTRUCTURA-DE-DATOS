#ifndef LISTACIRCULARHISTORIAL_H
#define LISTACIRCULARHISTORIAL_H
#include "Historial.h"
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

    void ingresarVehiculo(int puesto,string placa, string cedula, string nombre, 
                          string nombre2, string apellido, string apellido2,string fecha, string horaIngreso);
    
    
    // Métodos para imprimir

    void mostrarHistorial();

   

};

#endif
