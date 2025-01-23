#include <iostream>
#include "Menu.h"

int main() {

 BST<Propietario> arbolPropietarios;
    arbolPropietarios.CargarPropietarios("propietarios.txt");
    BST<Coche> arbolCochesHistorial;
    arbolCochesHistorial.CargarArchivo("autos_historial.txt");

    BST<Coche> arbolCoches;
    arbolCoches.CargarArchivo("autos.txt");

    menu(arbolCoches, arbolCochesHistorial, arbolPropietarios);

    return 0;
}

