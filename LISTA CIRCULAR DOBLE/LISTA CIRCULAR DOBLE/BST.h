#pragma once
#include "BSTNode.h"
#include <iostream>
using namespace std;

template <typename T>
class BST {//Clase de arbol binario bst
private:
    BSTNode<T>* raiz;//atributo raiz

    //metodos privados para facilitar la recursividad
    void insert(BSTNode<T>*& node, T data);
    BSTNode<T>* buscar(BSTNode<T>* node, const std::string& key);
    void inorder(BSTNode<T>* node);
    void eliminar(BSTNode<T>*& node, const std::string& key);
    void mostrarInOrder(BSTNode<T>* node);
    BSTNode<T>* eliminarPorPlacaRec(BSTNode<T>* node, string placa);
    BSTNode<T>* minValueNode(BSTNode<T>* node);
    void BusquedaAvanzadaRec(BSTNode<T>* node, string criterio, string valorInicio, string valorFin, bool& encontrado);
    void GuardarArchivoRec(BSTNode<T>* node, std::ofstream& archivo);
    void GuardarPropietariosRec(BSTNode<T>* node, ofstream& archivo);
    void BusquedaAvanzadaPropietarioRec(BSTNode<T>* node, string criterio, string valorInicio, string valorFin, bool& encontrado);


public:
     BST(){
        raiz = nullptr;
     }

        // Método para obtener la raíz del árbol
    BSTNode<T>* getRaiz() const {
        return raiz;
    }

    // Métodos públicos
    void insertar(T data);    
    BSTNode<T>* buscar(const std::string& placa);
    void buscarPorPlaca(string placa);
    void BusquedaAvanzada(string criterio, string valorInicio, string valorFin);      
    void eliminarPorPlaca(string placa);
    void mostrar(BSTNode<T>* node);
    void CargarArchivo(string nombreArchivo);
    void GuardarArchivo(string nombreArchivo);
    void salirDelParqueadero(const std::string& placa);
    static std::string cifrarTexto(const std::string &texto); 
    static std::string descifrarTexto(const std::string &texto);
    bool estaVacia() const;
    void GuardarPropietarios(const std::string& nombreArchivo);
    void CargarPropietarios(const std::string& nombreArchivo);
    void BusquedaAvanzadaPropietario(string criterio, string valorInicio, string valorFin);


     void inorder();
};



#include "BST.cpp"