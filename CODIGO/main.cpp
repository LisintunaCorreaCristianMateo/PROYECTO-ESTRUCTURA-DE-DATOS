#include "ListaCircularDoble.h"
#include "Nodo.h"
#include <iostream>


using namespace std;

// Función principal
int main() {
    int totalPuestos = 100; 
    ListaCircularDoble parqueadero(totalPuestos);

    int opcion;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Dibujar parqueadero\n";
        cout << "2. Ver puestos libres\n";
        cout << "3. Ingresar vehículo\n";
        cout << "4. Retirar vehículo\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            parqueadero.dibujarParqueadero();
            break;
        case 2:
            parqueadero.mostrarPuestosLibres();
            break;
        case 3: {
            string placa;
            cout << "Ingrese la placa del vehículo: ";
            cin >> placa;
            parqueadero.ingresarVehiculo(placa);
            break;
        }
        case 4: {
            int puesto;
            cout << "Ingrese el número del puesto a liberar: ";
            cin >> puesto;
            parqueadero.retirarVehiculo(puesto);
            break;
        }
        case 5:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opción inválida. Intente nuevamente." << endl;
        }
    } while (opcion != 5);

    return 0;
}

