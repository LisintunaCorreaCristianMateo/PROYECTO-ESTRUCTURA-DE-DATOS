#include <iostream>
#include "menu.h"
#include "NodoArbolBinario.h"
#include <conio.h> // Para _getch()

using namespace std;
void menu();

int main() {
	ArbolBinario arbol;  // Crear el �rbol binario
    menu(arbol);         // Llamar al men� para interactuar con el �rbol
	
    return 0;
}


