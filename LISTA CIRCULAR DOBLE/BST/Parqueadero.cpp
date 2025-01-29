#include "Parqueadero.h"

Parqueadero::Parqueadero() {
}


void Parqueadero::agregarCoche(Coche coche) {
    int espacioLibre = estacionamiento.obtenerEspacioAleatorio();  

   
    estacionamiento.ocuparEspacio(espacioLibre, coche);  

   
    arbolCoches.agregarDistancia(espacioLibre);

}


void Parqueadero::mostrarEstadoParqueadero() {
    std::cout << "Estado del Parqueadero:" << std::endl;
    estacionamiento.mostrarEstacionamiento();  
}


void Parqueadero::mostrarCoches() {
    std::cout << "Coches estacionados:" << std::endl;
    arbolCoches.mostrarDistancias();  
}

void Parqueadero::cargarYAsignarParqueadero(ListaCircularDoble<Coche>& listaCoches, ArbolAVL& arbolCoches) {
    estacionamiento.vaciarEstacionamiento();
    arbolCoches.vaciarArbol();

    
    Nodo<Coche>* nodoActual = listaCoches.getPrimero();

    if (nodoActual == nullptr) {
        std::cerr << "La lista de coches está vacía." << std::endl;
        return;
    }

    do {
        Coche coche = nodoActual->getDato(); 

       
        int posicionAleatoria = estacionamiento.obtenerEspacioAleatorio();

      
        estacionamiento.ocuparEspacio(posicionAleatoria, coche);  

       
        arbolCoches.agregarDistancia(posicionAleatoria);

       
        nodoActual = nodoActual->getSiguiente();
    } while (nodoActual != listaCoches.getPrimero());  
}

void Parqueadero::inicializarSemilla() {
    std::srand(0);  
}