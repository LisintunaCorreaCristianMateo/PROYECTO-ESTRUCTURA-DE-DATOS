
#include "menu.h"
#include "Validaciones.h"
#include <iostream>
#include <conio.h>  // Para _getch()
#include <windows.h> // Para cambiar colores en la consola
#include <limits>


using namespace std;



void menu(ArbolBinario &arbol){

	
	
	const int numOpciones = 6;
    string opciones[numOpciones] = {"Insertar nodo", "Eliminar nodo", "Mostrar Inorden", "Mostrar Preorden","Mostrar Posorden","Salir"};
    int opcionSeleccionada = 0; // Inicializamos la opci�n seleccionada en 0

    while (true) {
        mostrarMenu(opcionSeleccionada, opciones, numOpciones);
        char tecla = _getch(); // Captura una tecla

        if (tecla == 13) { // Detecta Enter (c�digo ASCII 13)
            system("cls"); // Limpia la consola
            procesarSeleccion(opciones[opcionSeleccionada],arbol); // Procesa la opci�n seleccionada
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
    cout << "=== Arbol Binario ===\n";
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
void procesarSeleccion(const string& opcion,ArbolBinario &arbol) {

	
    if (opcion == "Insertar nodo") {
    	int valor, opcion;
				arbol.mostrarArbol();
                valor=ingresar_entero("Ingresar el valor del nodo: ");
                system("cls");
                arbol.insertar(valor);
                cout << "\n�rbol binario despu�s de insertar " << valor << ": \n";
                arbol.mostrarArbol();
    } 
    
	else if (opcion == "Eliminar nodo") {
		int valor, opcion;
				arbol.mostrarArbol();
                cout << "Ingresa el valor del nodo a eliminar: ";
                cin >> valor;
                arbol.eliminar(valor);
                cout << "\n�rbol binario despu�s de eliminar " << valor << ": \n";
                arbol.mostrarArbol();
    
	}
	 else if (opcion == "Mostrar Inorden") {
	 	arbol.mostrarArbol();
cout << "Recorrido Inorden: ";
        arbol.inorden(arbol.getRaiz()); // Usamos el m�todo getRaiz()
        cout << "\n";
    }
    else if (opcion=="Mostrar Preorden"){
    	arbol.mostrarArbol();
    	        cout << "Recorrido Preorden: ";
        arbol.preorden(arbol.getRaiz()); // Usamos el m�todo getRaiz()
        cout << "\n";
	}
	else if(opcion == "Mostrar Posorden"){
		arbol.mostrarArbol();
       cout << "Recorrido Posorden: ";
        arbol.posorden(arbol.getRaiz()); // Usamos el m�todo getRaiz()
        cout << "\n";
	}
	else if (opcion == "Salir") {
        cout << "Saliendo del programa...\n";
    } else {
        cout << "Opcion no valida.\n";
    }
    system("pause"); // Pausa para permitir que el usuario lea el mensaje
}

