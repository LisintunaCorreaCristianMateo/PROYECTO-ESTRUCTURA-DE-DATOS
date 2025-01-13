#ifndef MENU_H
#define MENU_H
#include "NodoArbolBinario.h"
#include <string>
using namespace std;

// Prototipos de funciones
void menu(ArbolBinario &arbol);
void mostrarMenu(int opcionSeleccionada, const string opciones[], int numOpciones);
void procesarSeleccion(const string& opcion,ArbolBinario &arbol);
void cambiarColor(int color); // Nueva función para cambiar el color del texto

#endif

