#ifndef MENU_H
#define MENU_H

#include <string>
using namespace std;

// Prototipos de funciones
void menu();
void mostrarMenu(int opcionSeleccionada, const string opciones[], int numOpciones);
void procesarSeleccion(const string& opcion);
void cambiarColor(int color); // Nueva funci�n para cambiar el color del texto

#endif

