#pragma once
#include <iostream>
#include <vector>
#include "BST.h"
#include "Propietario.h"
#include "Coche.h"

using namespace std;

void menu(BST<Coche> &arbol, BST<Coche> &arbolHistorial, BST<Propietario> &arbolPropietarios);
int menuInteractivo(const vector<string> &opciones, const string &titulo = "Menu Interactivo");
void menuBusquedaAvanzada(BST<Coche> &arbol, BST<Coche> &arbolHistorial);
void menuGestionPropietarios(BST<Propietario> &arbolPropietarios);
void menuOrdenar(BST<Coche> &arbol, BST<Coche> &arbolHistorial, BST<Propietario> &arbolPropietarios);
void menuBusquedaAvanzadaPropietario(BST<Propietario> &arbolPropietarios);
void menuMostrarCoches(BST<Coche> &arbol, BST<Coche> &arbolHistorial);