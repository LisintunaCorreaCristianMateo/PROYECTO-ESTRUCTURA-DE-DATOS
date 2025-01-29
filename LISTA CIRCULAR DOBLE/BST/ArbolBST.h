#pragma once

#include "NodoBST.h"
#include <string>
#include <SFML/Graphics.hpp>

class ArbolAVL {
private:
    NodoAVL* raiz;

  
    int obtenerAltura(NodoAVL* nodo);
    int obtenerFactorBalance(NodoAVL* nodo);
    NodoAVL* rotarDerecha(NodoAVL* y);
    NodoAVL* rotarIzquierda(NodoAVL* x);
    NodoAVL* insertar(NodoAVL* nodo, int distancia);
    void recorridoInorden(NodoAVL* nodo);
    void dibujarNodo(NodoAVL* nodo, sf::RenderWindow &ventana, sf::Font &fuente, float x, float y, float offset);


public:
    ArbolAVL();
     NodoAVL* obtenerRaiz();
    void agregarDistancia(int distancia);
    void mostrarDistancias();  
    void mostrarArbol(sf::RenderWindow& ventana, sf::Font& fuente);  
    void vaciarArbol();
};
