#include "Nodo.h"

template <typename T>
Nodo<T>::Nodo(T dato)
{
    this->dato = dato;
    this->siguiente = nullptr;
    this->anterior = nullptr;
}
T Nodo<T>::getDato()
    return dato;
void Nodo<T>::setDato(T dato)
void Nodo<T>::setSiguiente(Nodo<T> *siguiente)
    this->siguiente = siguiente;
Nodo<T> *Nodo<T>::getSiguiente()
    return this->siguiente;
void Nodo<T>::setAnterior(Nodo<T> *anterior)
    this->anterior = anterior;
Nodo<T> *Nodo<T>::getAnterior()
    return this->anterior;
