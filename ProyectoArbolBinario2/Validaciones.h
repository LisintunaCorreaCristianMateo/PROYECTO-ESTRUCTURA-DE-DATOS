#ifndef VALIDACIONES_H
#define VALIDACIONES_H
#include<string>
#include<iostream>
using namespace std;

int ingresar_entero(const char  *);
float ingresar_float(const char  *);
string ingresar_string(const char* );
string ingresar_cedula(const char* );
bool validarCedulaEcuatoriana(const std::string& cedula);

#endif 
