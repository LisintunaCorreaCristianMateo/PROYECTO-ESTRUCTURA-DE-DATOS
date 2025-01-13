#include <iostream>
#include "menu.h"
#include "NodoArbolBinario.h"
#include <conio.h> // Para _getch()

using namespace std;
void menu();

int main() {
	ArbolBinario arbol;  // Crear el árbol binario
    menu(arbol);         // Llamar al menú para interactuar con el árbol
	
    return 0;
}


