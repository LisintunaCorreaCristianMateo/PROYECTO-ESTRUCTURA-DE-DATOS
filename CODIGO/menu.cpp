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
    string opciones[numOpciones] = {"Ver parqueadero", "Ingresar veh�culo", "Retirar veh�culo", "Salir"};
    int opcionSeleccionada = 0; // Inicializamos la opci�n seleccionada en 0

    while (true) {
        mostrarMenu(opcionSeleccionada, opciones, numOpciones);
        char tecla = _getch(); // Captura una tecla

        if (tecla == 13) { // Detecta Enter (c�digo ASCII 13)
            system("cls"); // Limpia la consola
            procesarSeleccion(opciones[opcionSeleccionada]); // Procesa la opci�n seleccionada
            if (opciones[opcionSeleccionada] == "Salir") {
                break; // Termina el programa si la opci�n es "Salir"
            }
        } else if (tecla == -32) { // Detecta teclas especiales (como flechas)
            tecla = _getch(); // Captura la segunda parte del c�digo de la tecla
            if (tecla == 72) { // Flecha arriba
                opcionSeleccionada = (opcionSeleccionada - 1 + numOpciones) % numOpciones;
            } else if (tecla == 80) { // Flecha abajo
                opcionSeleccionada = (opcionSeleccionada + 1) % numOpciones;
            }
        }
    }
}




// Funci�n para cambiar el color de la consola
void cambiarColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Funci�n para mostrar el men�
void mostrarMenu(int opcionSeleccionada, const string opciones[], int numOpciones) {
    system("cls"); // Limpia la consola
    cout << "===  MENU ===\n";
    for (int i = 0; i < numOpciones; ++i) {
        if (i == opcionSeleccionada) {
            cambiarColor(3); // Cambiar el color de la opci�n seleccionada (verde)
            cout << " " << opciones[i] << " \n"; // Opci�n seleccionada resaltada
            cambiarColor(7);  // Volver al color normal (blanco)
        } else {
            cambiarColor(7);  // Color normal para las otras opciones
            cout << "  " << opciones[i] << "\n";
        }
    }
}

// Funci�n para procesar la selecci�n de una opci�n
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
    
	else if (opcion == "Ingresar veh�culo") {
		
            string placa;
            cout << "Ingrese la placa del veh�culo: ";
            cin >> placa;
            parqueadero.ingresarVehiculo(placa);
        //manejadorArchivos.leerDesdeArchivo("estudiantes.txt",lista);
            	

        system("pause");
    	system("cls");
    
	}
	 else if (opcion == "Retirar veh�culo") {
	 	 int puesto;
        //manejadorArchivos.leerDesdeArchivo("estudiantes.txt",lista);
	        cout << "Ingrese el n�mero del puesto a liberar: ";
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

