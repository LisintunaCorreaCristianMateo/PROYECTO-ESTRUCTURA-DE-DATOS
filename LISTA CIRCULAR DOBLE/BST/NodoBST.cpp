#include "NodoBST.h"

NodoAVL::NodoAVL(int distancia) {
    this->distancia = distancia;
    this->izquierdo = nullptr;
    this->derecho = nullptr;
    this->altura = 1;  
}