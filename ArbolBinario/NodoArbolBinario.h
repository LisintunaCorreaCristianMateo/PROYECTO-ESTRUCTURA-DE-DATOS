#ifndef NODOARBOLBINARIO_H
#define NODOARBOLBINARIO_H

#include <iostream>
using namespace std;

// Clase Nodo que representa un nodo del �rbol binario
class Nodo {
private:
    int dato;
    Nodo* izquierda;
    Nodo* derecha;

public:
    // Constructor
    Nodo(int valor) : dato(valor), izquierda(nullptr), derecha(nullptr) {}

    // Getters y Setters
    int getDato() { return dato; }
    Nodo* getIzquierda() { return izquierda; }
    Nodo* getDerecha() { return derecha; }

	void setDato(int valor) {
    dato = valor;
}

    void setIzquierda(Nodo* nodo) { izquierda = nodo; }
    void setDerecha(Nodo* nodo) { derecha = nodo; }
};

// Clase ArbolBinario para manejar la l�gica del �rbol binario
class ArbolBinario {
private:
    Nodo* raiz;

public:
	    // M�todo para obtener la ra�z del �rbol
    Nodo* getRaiz() {
        return raiz;
    }
    
    // Funci�n auxiliar para insertar un nodo en el �rbol
    Nodo* insertar(Nodo* nodo, int valor) {
        if (nodo == nullptr) {
            return new Nodo(valor);
        }

        if (valor < nodo->getDato()) {
            nodo->setIzquierda(insertar(nodo->getIzquierda(), valor));
        } else {
            nodo->setDerecha(insertar(nodo->getDerecha(), valor));
        }

        return nodo;
    }

    // Funci�n auxiliar para encontrar el nodo m�nimo en un sub�rbol
    Nodo* encontrarMin(Nodo* nodo) {
        while (nodo->getIzquierda() != nullptr) {
            nodo = nodo->getIzquierda();
        }
        return nodo;
    }

    // Funci�n auxiliar para eliminar un nodo del �rbol
Nodo* eliminar(Nodo* nodo, int valor) {
    if (nodo == nullptr) {
        return nodo;
    }

    if (valor < nodo->getDato()) {
        nodo->setIzquierda(eliminar(nodo->getIzquierda(), valor));
    } else if (valor > nodo->getDato()) {
        nodo->setDerecha(eliminar(nodo->getDerecha(), valor));
    } else {
        if (nodo->getIzquierda() == nullptr) {
            Nodo* temp = nodo->getDerecha();
            delete nodo;
            return temp;
        } else if (nodo->getDerecha() == nullptr) {
            Nodo* temp = nodo->getIzquierda();
            delete nodo;
            return temp;
        }

        Nodo* temp = encontrarMin(nodo->getDerecha());
        nodo->setDato(temp->getDato());  // Usamos el setter aqu�
        nodo->setDerecha(eliminar(nodo->getDerecha(), temp->getDato()));
    }
    return nodo;
}


    // Funci�n auxiliar para imprimir el �rbol de forma gr�fica en consola
    void imprimirArbol(Nodo* nodo, int espacio = 0, int altura = 10) {
        const int COUNT = 10;

        if (nodo == nullptr) {
            return;
        }

        espacio += COUNT;

        imprimirArbol(nodo->getDerecha(), espacio);

        cout << endl;
        for (int i = COUNT; i < espacio; i++) {
            cout << " ";
        }
        cout << nodo->getDato() << "\n";

        imprimirArbol(nodo->getIzquierda(), espacio);
    }

    // Recorridos del �rbol
    void inorden(Nodo* nodo) {
        if (nodo == nullptr) return;
        inorden(nodo->getIzquierda());
        cout << nodo->getDato() << " ";
        inorden(nodo->getDerecha());
    }

    void preorden(Nodo* nodo) {
        if (nodo == nullptr) return;
        cout << nodo->getDato() << " ";
        preorden(nodo->getIzquierda());
        preorden(nodo->getDerecha());
    }

    void posorden(Nodo* nodo) {
        if (nodo == nullptr) return;
        posorden(nodo->getIzquierda());
        posorden(nodo->getDerecha());
        cout << nodo->getDato() << " ";
    }

public:
    // Constructor
    ArbolBinario() : raiz(nullptr) {}

    // Funci�n para insertar un valor en el �rbol
    void insertar(int valor) {
        raiz = insertar(raiz, valor);
    }

    // Funci�n para eliminar un valor del �rbol
    void eliminar(int valor) {
        raiz = eliminar(raiz, valor);
    }

    // Funci�n para mostrar el �rbol de forma gr�fica
    void mostrarArbol() {
        imprimirArbol(raiz);
    }

};

#endif

