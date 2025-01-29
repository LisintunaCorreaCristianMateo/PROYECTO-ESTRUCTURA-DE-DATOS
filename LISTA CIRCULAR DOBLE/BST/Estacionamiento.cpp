#include "Estacionamiento.h"

Estacionamiento::Estacionamiento() {
    std::srand(0);
}

void Estacionamiento::ocuparEspacio(int espacio, Coche& coche) {
    if (espacio >= 0 && espacio < TAMANIO && !espacioOcupado(espacio)) {
        espaciosOcupados[espacio] = coche;  
       

    } else {
        std::cout << "Espacio no válido o ya ocupado." << std::endl;
    }
}

void Estacionamiento::liberarEspacio(const std::string& placa) {
    try {
        
        int espacio = obtenerEspacioPorPlaca(placa); 
        
       
        if (espacioOcupado(espacio)) {
            espaciosOcupados.erase(espacio);  
            std::cout << "Espacio " << espacio << " liberado." << std::endl;
        } else {
            std::cout << "Espacio no ocupado." << std::endl;
        }
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl; 
    }
}

int Estacionamiento::obtenerEspacioPorPlaca(const std::string& placa) {
   
   std::cout << "=== DEBUG: Contenido de espaciosOcupados ===" << std::endl;
if (espaciosOcupados.empty()) {
    std::cout << "El mapa está vacío, no hay coches almacenados." << std::endl;
} else {
    for (const auto& pair : espaciosOcupados) {
        std::cout << "Espacio: " << pair.first << " | Placa: " << pair.second.getPlaca() << std::endl;
    }
}
std::cout << "==========================================" << std::endl;
    for (const auto& pair : espaciosOcupados) {
        const Coche& coche = pair.second;
        std::cout << "  Comparando con placa: " << coche.getPlaca() 
                  << " en espacio " << pair.first << std::endl;

        if (coche.getPlaca() == placa) {
            std::cout << "  -> Coche encontrado en el espacio " << pair.first << std::endl;
            return pair.first;
        }
    }

    std::cout << "  -> Coche NO encontrado." << std::endl;
    throw std::invalid_argument("Coche no encontrado en el estacionamiento.");
}



void Estacionamiento::mostrarEstacionamiento() {
    std::cout << "Estado del Parqueadero:\n";
    
   
    
   
    for (int i = 0; i < TAMANIO; ++i) {
       
        if (espacioOcupado(i)) {
            std::cout << "[X] ";  
        } else {
            std::cout << "[ ] ";  
        }

        if ((i + 1) % 5 == 0) {
            std::cout << "   "; 
        }

        
        if ((i + 1) % 10 == 0) {
            std::cout << std::endl;
        }
    }

    std::cout << std::endl;
}

int Estacionamiento::obtenerEspacioAleatorio() {
    int espacio = rand() % TAMANIO;  
    
    while (espacioOcupado(espacio)) {  
        espacio = rand() % TAMANIO;  
    }
    
    return espacio;  
}

int Estacionamiento::getNumeroEspacios() const {
    return TAMANIO; 
}

bool Estacionamiento::espacioOcupado(int espacio) {
    return espaciosOcupados.find(espacio) != espaciosOcupados.end();  
}

Coche Estacionamiento::obtenerCocheEnEspacio(int espacio) {
    if (espacioOcupado(espacio)) {
        return espaciosOcupados[espacio];  
    } else {
        throw std::invalid_argument("El espacio no está ocupado.");
    }
}

void Estacionamiento::vaciarEstacionamiento() {
    espaciosOcupados.clear();  
    std::cout << "Estacionamiento vaciado correctamente." << std::endl;
}