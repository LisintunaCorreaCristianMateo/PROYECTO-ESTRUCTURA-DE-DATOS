#include "Nodo.h"
#include <iostream>
using namespace std;

Nodo::Nodo(int _puesto){
	puesto=_puesto;
	ocupado=false;
	placa="";
	siguiente=NULL;
	anterior=NULL;
}
Nodo::~Nodo(){
	
}

