#include "ListaCircularDoble.h"
#include "menu.h"
//#include"Validaciones.h"
//#include "Archivotxt.h"
#include <iostream>
#include <conio.h>  // Para _getch()
#include <windows.h> // Para cambiar colores en la consola
#include <limits>


using namespace std;

		
    int totalPuestos = 20; 
    ListaCircularDoble parqueadero(totalPuestos);

void menu(){

	
	
	const int numOpciones = 4;
    string opciones[numOpciones] = {"Ver parqueadero", "Ingresar vehículo", "Retirar vehículo", "Salir"};
    int opcionSeleccionada = 0; // Inicializamos la opción seleccionada en 0

    while (true) {
        mostrarMenu(opcionSeleccionada, opciones, numOpciones);
        char tecla = _getch(); // Captura una tecla

        if (tecla == 13) { // Detecta Enter (código ASCII 13)
            system("cls"); // Limpia la consola
            procesarSeleccion(opciones[opcionSeleccionada]); // Procesa la opción seleccionada
            if (opciones[opcionSeleccionada] == "Salir") {
                break; // Termina el programa si la opción es "Salir"
            }
        } else if (tecla == -32) { // Detecta teclas especiales (como flechas)
            tecla = _getch(); // Captura la segunda parte del código de la tecla
            if (tecla == 72) { // Flecha arriba
                opcionSeleccionada = (opcionSeleccionada - 1 + numOpciones) % numOpciones;
            } else if (tecla == 80) { // Flecha abajo
                opcionSeleccionada = (opcionSeleccionada + 1) % numOpciones;
            }
        }
    }
}




// Función para cambiar el color de la consola
void cambiarColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Función para mostrar el menú
void mostrarMenu(int opcionSeleccionada, const string opciones[], int numOpciones) {
    system("cls"); // Limpia la consola
    cout << "===  MENU ===\n";
    for (int i = 0; i < numOpciones; ++i) {
        if (i == opcionSeleccionada) {
            cambiarColor(3); // Cambiar el color de la opción seleccionada (verde)
            cout << " " << opciones[i] << " \n"; // Opción seleccionada resaltada
            cambiarColor(7);  // Volver al color normal (blanco)
        } else {
            cambiarColor(7);  // Color normal para las otras opciones
            cout << "  " << opciones[i] << "\n";
        }
    }
}

// Función para procesar la selección de una opción
void procesarSeleccion(const string& opcion) {

    
//	Archivotxt manejadorArchivos;
	
    if (opcion == "Ver parqueadero") {
    	
    	 parqueadero.dibujarParqueadero();
    	 cout<<endl;
    	 cout<<endl;
    	 parqueadero.mostrarPuestosLibres();
    	
        //manejadorArchivos.leerDesdeArchivo("estudiantes.txt",lista);

                
               
        //Guarda en el txt
    //	manejadorArchivos.guardarEnArchivo("estudiantes.txt",lista);
    } 
    
	else if (opcion == "Ingresar vehículo") {
		
            string placa;
            cout << "Ingrese la placa del vehículo: ";
            cin >> placa;
            parqueadero.ingresarVehiculo(placa);
        //manejadorArchivos.leerDesdeArchivo("estudiantes.txt",lista);
            	

        system("pause");
    	system("cls");
    
	}
	 else if (opcion == "Retirar vehículo") {
	 	 int puesto;
        //manejadorArchivos.leerDesdeArchivo("estudiantes.txt",lista);
	        cout << "Ingrese el número del puesto a liberar: ";
            cin >> puesto;
            parqueadero.retirarVehiculo(puesto);
			
	
		    
	//	manejadorArchivos.guardarEnArchivo("estudiantes.txt",lista);
		    
    } 
	else if (opcion == "Salir") {
        cout << "Saliendo del programa...\n";
    } else {
        cout << "Opcion no valida.\n";
    }
    system("pause"); // Pausa para permitir que el usuario lea el mensaje
}

