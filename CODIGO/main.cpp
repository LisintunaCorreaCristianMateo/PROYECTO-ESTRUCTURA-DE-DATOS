#include "ListaCircularDoble.h"
#include "Nodo.h"
#include <iostream>


using namespace std;

// Funci�n principal
int main() {
    int totalPuestos = 100; 
    ListaCircularDoble parqueadero(totalPuestos);

    int opcion;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Dibujar parqueadero\n";
        cout << "2. Ver puestos libres\n";
        cout << "3. Ingresar veh�culo\n";
        cout << "4. Retirar veh�culo\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opci�n: ";
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
            cout << "Ingrese la placa del veh�culo: ";
            cin >> placa;
            parqueadero.ingresarVehiculo(placa);
            break;
        }
        case 4: {
            int puesto;
            cout << "Ingrese el n�mero del puesto a liberar: ";
            cin >> puesto;
            parqueadero.retirarVehiculo(puesto);
            break;
        }
        case 5:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opci�n inv�lida. Intente nuevamente." << endl;
        }
    } while (opcion != 5);

    return 0;
}

