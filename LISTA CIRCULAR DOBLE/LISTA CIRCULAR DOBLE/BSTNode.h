#pragma once

template <typename T>
class BSTNode {

private:
    T data;
    BSTNode* left; //izquierda
    BSTNode* right; //derecha


public:
    
    
    //constructor
    BSTNode(T dato);

    //getters
    T getData();
    BSTNode *getLeft();
    BSTNode *getRight();

     //setters
    
    void setData(T dato);
    void setLeft(BSTNode *left);
    void setRight(BSTNode *rigth);
    
};
#include "BSTNode.cpp"
