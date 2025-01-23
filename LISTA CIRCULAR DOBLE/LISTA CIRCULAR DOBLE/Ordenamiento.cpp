#include <iostream>
#include <vector>
#include <algorithm>
#include "Coche.h"
#include <functional>
template <typename T>
void inorderTraversal(BSTNode<T>* node, std::vector<T>& lista) {
    if (node == nullptr) {
        return;
    }
    inorderTraversal(node->left, lista);
    lista.push_back(node->data);
    inorderTraversal(node->right, lista);
}

template <typename T>
void preorderTraversal(BSTNode<T>* node, std::vector<T>& lista) {
    if (node == nullptr) {
        return;
    }
    lista.push_back(node->data);
    preorderTraversal(node->left, lista);
    preorderTraversal(node->right, lista);
}

template <typename T>
void postorderTraversal(BSTNode<T>* node, std::vector<T>& lista) {
    if (node == nullptr) {
        return;
    }
    postorderTraversal(node->left, lista);
    postorderTraversal(node->right, lista);
    lista.push_back(node->data);
}

template <typename T>
std::vector<T> obtenerElementosEnOrden(BST<T>& arbol, const std::string& tipoRecorrido) {
    std::vector<T> lista;
    if (tipoRecorrido == "inorden") {
        inorderTraversal(arbol.getRaiz(), lista);
    } else if (tipoRecorrido == "preorden") {
        preorderTraversal(arbol.getRaiz(), lista);
    } else if (tipoRecorrido == "posorden") {
        postorderTraversal(arbol.getRaiz(), lista);
    }
    return lista;
}