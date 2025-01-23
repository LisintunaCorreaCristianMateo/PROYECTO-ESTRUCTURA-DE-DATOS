#pragma once

#include <iostream>
#include <string>
#include "BSTNode.h"
#include "BST.h"

using namespace std;

template <typename T>
class Placa
{
public:
    string ingresarPlaca(BSTNode<T> *aux);

private:
    void convertirAMayusculas(string &placa);
};

#include "ValidacionPlaca.cpp"