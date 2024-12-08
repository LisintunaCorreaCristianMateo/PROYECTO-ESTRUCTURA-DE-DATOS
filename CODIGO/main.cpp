#include "ListaCircularDoble.h"
#include "Nodo.h"
#include "Menu.h"
#include <iostream>
#include "Manual.h"
#include <thread>

using namespace std;

// Funci�n principal
int main() {
	
	
    Manual manual;
    
    thread manualThread(&Manual::mostrar, &manual);
    

	menu();
	
	
	
   if (manualThread.joinable()) {
        manualThread.join();
    }

    return 0;
}

