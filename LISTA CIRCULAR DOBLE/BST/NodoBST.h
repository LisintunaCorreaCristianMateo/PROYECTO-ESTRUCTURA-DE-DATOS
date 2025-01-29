#pragma once

class NodoAVL {
public:
    int distancia;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

    NodoAVL(int distancia);  
};