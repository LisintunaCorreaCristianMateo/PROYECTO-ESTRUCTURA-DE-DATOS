#include "BSTNode.h"
//constructor
template <typename T>
BSTNode<T>::BSTNode(T dato)
{
    this->data = dato;
    this->left = nullptr;
    this->right = nullptr;
}

//getters

template <typename T>
T BSTNode<T>::getData(){
    return dato;
}

template <typename T>
BSTNode<T> *BSTNode<T>::getLeft(){
    return this->left;
}

template <typename T>
BSTNode<T> *BSTNode<T>::getRight()
{
    return this->right;
}
//setters


template <typename T>
void BSTNode<T>::setData(T dato)
{
    this->data = dato;
}

template <typename T>
void BSTNode<T>::setLeft(BSTNode<T> *left)
{
    this->left =left;
}


template <typename T>
void BSTNode<T>::setRight(BSTNode<T> *right)
{
    this->right = right;
}

