    #include "ListaCircularDoble.h"
	#include<iostream>
	#include <vector>
	#include <ctime>
	#include <iomanip>
	#include <string>
    #include <fstream>

	using namespace std;

	//constructor
	ListaCircularDoble::ListaCircularDoble(int puestosTotales)  {
    	totalPuestos=puestosTotales;
    	cabezaIzquierda=NULL;
		cabezaDerecha=NULL;
    	
        puestosPorLado = puestosTotales / 2; // La mitad de los puestos se asignan a cada lado

        // Crear los puestos de la fila izquierda
        for (int i = 1; i <= puestosPorLado; i++) {
            insertarNodo(i, true);
        }

        // Crear los puestos de la fila derecha
        for (int i = puestosPorLado + 1; i <= totalPuestos; i++) {
            insertarNodo(i, false);
        }
    }
	//destructor
    ListaCircularDoble::~ListaCircularDoble(){
    	
	}

    // Función para obtener la fecha actual
    string obtenerFechaActual() {
        time_t tiempoActual = time(nullptr);
        struct tm* fechaLocal = new tm();
        localtime_s(fechaLocal, &tiempoActual);
        char buffer[20]; // Buffer para almacenar la fecha
        strftime(buffer, sizeof(buffer), "%d/%m/%Y", fechaLocal);
        string fecha(buffer);
        delete fechaLocal;  // Importante liberar la memoria
        return fecha;
    }

    // Función para obtener la hora actual
    string obtenerHoraActual() {
        time_t tiempoActual = time(nullptr);
        struct tm* horaLocal = new tm();
        localtime_s(horaLocal, &tiempoActual);
        char buffer[20]; // Buffer para almacenar la hora
        strftime(buffer, sizeof(buffer), "%H:%M:%S", horaLocal);
        string hora(buffer);
        delete horaLocal;  // Importante liberar la memoria
        return hora;
    }

    // Funciï¿½n para insertar un nodo en la lista circular
void ListaCircularDoble::insertarNodo(int puesto, bool esIzquierda) {
    Nodo* nuevo = new Nodo(puesto,"","","","","","","","","");
    if (esIzquierda) {
        if (!cabezaIzquierda) { // Si la lista izquierda estÃ¡ vacÃ­a
            cabezaIzquierda = nuevo;
            cabezaIzquierda->setSiguiente(cabezaIzquierda);
            cabezaIzquierda->setAnterior(cabezaIzquierda);
        } else { // Agregar al final de la lista izquierda
            Nodo* ultimo = cabezaIzquierda->getAnterior();
            ultimo->setSiguiente(nuevo);
            nuevo->setAnterior(ultimo);
            nuevo->setSiguiente(cabezaIzquierda);
            cabezaIzquierda->setAnterior(nuevo);
        }
    } else {
        if (!cabezaDerecha) { // Si la lista derecha estÃ¡ vacÃ­a
            cabezaDerecha = nuevo;
            cabezaDerecha->setSiguiente(cabezaDerecha);
            cabezaDerecha->setAnterior(cabezaDerecha);
        } else { // Agregar al final de la lista derecha
            Nodo* ultimo = cabezaDerecha->getAnterior();
            ultimo->setSiguiente(nuevo);
            nuevo->setAnterior(ultimo);
            nuevo->setSiguiente(cabezaDerecha);
            cabezaDerecha->setAnterior(nuevo);
        }
    }
}


    // Funciï¿½n para dibujar el parqueadero en forma de anillo
void ListaCircularDoble::dibujarParqueadero() {
    Nodo* actualIzquierda = cabezaIzquierda;
    Nodo* actualDerecha = cabezaDerecha;

    cout << "\n----------- Estado del Parqueadero --------\n\n";

    // Dibujar la fila izquierda
    do {
        if (actualIzquierda->isOcupado()) {
            cout << "\033[1;31m"; // Rojo brillante
            cout << "[P" << setw(2) << actualIzquierda->getPuesto() 
                 << ": " << actualIzquierda->getPlaca() << "]  ";
            cout << "\033[0m"; // Restablecer color
        } else {
            cout << "[P" << setw(2) << actualIzquierda->getPuesto() << "]  ";
        }
        actualIzquierda = actualIzquierda->getSiguiente();
    } while (actualIzquierda != cabezaIzquierda);
    cout << endl;

    for (int i = 0; i < puestosPorLado; i++) {
        cout << "   ---   ";
    }
    cout << endl;

    // Dibujar la fila derecha
    do {
        if (actualDerecha->isOcupado()) {
            cout << "\033[1;31m";
            cout << "[P" << setw(2) << actualDerecha->getPuesto() 
                 << ": " << actualDerecha->getPlaca() << "]  ";
            cout << "\033[0m";
        } else {
            cout << "[P" << setw(2) << actualDerecha->getPuesto() << "]  ";
        }
        actualDerecha = actualDerecha->getSiguiente();
    } while (actualDerecha != cabezaDerecha);
    cout << endl;
}


    // Funciï¿½n para determinar los puestos vacï¿½os
void ListaCircularDoble::mostrarPuestosLibres() {
    Nodo* actual = cabezaIzquierda;
    cout << "Puestos Disponibles:\n\n ";
    do {
        if (!actual->isOcupado()) {
            cout << actual->getPuesto() << " ";
        }
        actual = actual->getSiguiente();
    } while (actual != cabezaIzquierda);
  

    actual = cabezaDerecha;
   // cout << "Puestos libres (Derecha): ";
    do {
        if (!actual->isOcupado()) {
            cout << actual->getPuesto() << " ";
        }
        actual = actual->getSiguiente();
    } while (actual != cabezaDerecha);
    cout << endl;
    cout<<endl;
    
}

    // Funciï¿½n para ingresar un vehï¿½culo en un puesto vacï¿½o aleatorio
void ListaCircularDoble::ingresarVehiculo(string placa, string cedula, string nombre, string segundoNombre, string apellido, string segundoApellido) {
    vector<Nodo*> puestosLibres;
    Nodo* actual = cabezaIzquierda;

    // Recopilar todos los puestos libres en la fila izquierda
    do {
        if (!actual->isOcupado()) {
            puestosLibres.push_back(actual);
        }
        actual = actual->getSiguiente();
    } while (actual != cabezaIzquierda);

    // Recopilar todos los puestos libres en la fila derecha
    actual = cabezaDerecha;
    do {
        if (!actual->isOcupado()) {
            puestosLibres.push_back(actual);
        }
        actual = actual->getSiguiente();
    } while (actual != cabezaDerecha);

    // Verificar si hay puestos disponibles
    if (puestosLibres.empty()) {
        cout << "No hay puestos disponibles." << endl;
        return;
    }

    // Seleccionar un puesto vacío aleatorio
    srand(time(0));
    int indiceAleatorio = rand() % puestosLibres.size();
    Nodo* puestoSeleccionado = puestosLibres[indiceAleatorio];

    // Actualizar los datos directamente en el nodo seleccionado
    puestoSeleccionado->setPlaca(placa);
    puestoSeleccionado->setCedula(cedula);
    puestoSeleccionado->setNombre(nombre);
    puestoSeleccionado->setSegundoNombre(segundoNombre);
    puestoSeleccionado->setApellido(apellido);
    puestoSeleccionado->setSegundoApellido(segundoApellido);
    puestoSeleccionado->setHoraIngreso(obtenerHoraActual());
    puestoSeleccionado->setFecha(obtenerFechaActual());
    //puestoSeleccionado->setHoraSalida(""); // Inicializar vacío
    puestoSeleccionado->setOcupado(true);

    // Confirmación de ingreso
    cout << "Vehículo con placa " << placa << " ingresado en el puesto " << puestoSeleccionado->getPuesto() << "." << endl;
}



    // Funciï¿½n para eliminar un vehï¿½culo
void ListaCircularDoble::retirarVehiculo(int puesto) {
    Nodo* actual = cabezaIzquierda;

    do {
        if (actual->getPuesto() == puesto) {
            if (actual->isOcupado()) {
                cout << "Vehiculo con placa " << actual->getPlaca() 
                     << " retirado del puesto " << puesto << "." << endl;
                actual->setOcupado(false);
                actual->setPlaca(string(""));
            } else {
                cout << "El puesto " << puesto << " esta¡ libre." << endl;
            }
            return;
        }
        actual = actual->getSiguiente();
    } while (actual != cabezaIzquierda);

    actual = cabezaDerecha;
    do {
        if (actual->getPuesto() == puesto) {
            if (actual->isOcupado()) {
                cout << "Vehiculo con placa " << actual->getPlaca() 
                     << " retirado del puesto " << puesto << "." << endl;
                actual->setOcupado(false);
                actual->setPlaca("");
            } else {
                cout << "El puesto " << puesto << " esta¡ libre." << endl;
            }
            return;
        }
        actual = actual->getSiguiente();
    } while (actual != cabezaDerecha);

    cout << "El puesto " << puesto << " no existe." << endl;
}
// metodos para la impresion


void ListaCircularDoble::mostrarDatos() {
    Nodo* actualIzquierda = cabezaIzquierda;
    Nodo* actualDerecha = cabezaDerecha;

    cout << "--- Datos de los Propietarios ---" << endl;

    if (!cabezaIzquierda && !cabezaDerecha) {
        cout << "No hay datos disponibles en el parqueadero." << endl;
        return;
    }

    // Establecer encabezados y anchos de las columnas
    cout << left << setw(15) << "Nombre" 
         << setw(20) << "Segundo Nombre" 
         << setw(15) << "Apellido" 
         << setw(20) << "Segundo Apellido" 
         << setw(15) << "Cédula" 
         << setw(10) << "Placa" << endl;
    cout << string(95, '-') << endl;

    // Recorrer todos los nodos en la fila izquierda
    do {
        if (actualIzquierda->isOcupado()) { // Verifica si el puesto está ocupado
            cout << left << setw(15) << actualIzquierda->getNombre()
                 << setw(20) << actualIzquierda->getSegundoNombre()
                 << setw(15) << actualIzquierda->getApellido()
                 << setw(20) << actualIzquierda->getSegundoApellido()
                 << setw(15) << actualIzquierda->getCedula()
                 << setw(10) << actualIzquierda->getPlaca() << endl;
        }
        actualIzquierda = actualIzquierda->getSiguiente();
    } while (actualIzquierda != cabezaIzquierda); // Continuar hasta dar la vuelta completa

    // Recorrer todos los nodos en la fila derecha
    do {
        if (actualDerecha->isOcupado()) { // Verifica si el puesto está ocupado
            cout << left << setw(15) << actualDerecha->getNombre()
                 << setw(20) << actualDerecha->getSegundoNombre()
                 << setw(15) << actualDerecha->getApellido()
                 << setw(20) << actualDerecha->getSegundoApellido()
                 << setw(15) << actualDerecha->getCedula()
                 << setw(10) << actualDerecha->getPlaca() << endl;
        }
        actualDerecha = actualDerecha->getSiguiente();
    } while (actualDerecha != cabezaDerecha); // Continuar hasta dar la vuelta completa

    cout << endl;
}


void ListaCircularDoble::mostrarAutos() {
    cout << "--- Autos Registrados en el Parqueadero ---" << endl;

    if (!cabezaIzquierda && !cabezaDerecha) { // Verifica si ambas listas están vacías
        cout << "No hay autos en el parqueadero." << endl;
        return;
    }

    bool autosEncontrados = false;

    // Establecer encabezados de columnas
    cout << left << setw(15) << "Placa" << setw(10) << "Puesto" << endl;
    cout << "-----------------------------" << endl;

    // Recorrer la lista izquierda
    if (cabezaIzquierda) {
        Nodo* actualIzquierda = cabezaIzquierda;
        do {
            if (actualIzquierda->isOcupado()) {
                cout << left << setw(15) << actualIzquierda->getPlaca() 
                     << setw(10) << actualIzquierda->getPuesto() << endl;
                autosEncontrados = true;
            }
            actualIzquierda = actualIzquierda->getSiguiente();
        } while (actualIzquierda != cabezaIzquierda);
    }

    // Recorrer la lista derecha
    if (cabezaDerecha) {
        Nodo* actualDerecha = cabezaDerecha;
        do {
            if (actualDerecha->isOcupado()) {
                cout << left << setw(15) << actualDerecha->getPlaca() 
                     << setw(10) << actualDerecha->getPuesto() << endl;
                autosEncontrados = true;
            }
            actualDerecha = actualDerecha->getSiguiente();
        } while (actualDerecha != cabezaDerecha);
    }

    if (!autosEncontrados) {
        cout << "No hay autos registrados en este momento." << endl;
    }

    cout << endl;
}



void ListaCircularDoble::mostrarHistorial() {
    cout << "--- Historial de Vehiculos ---" << endl;

    if (!cabezaIzquierda && !cabezaDerecha) { // Verifica si ambas listas están vacías
        cout << "No hay historial en el parqueadero." << endl;
        return;
    }

    // Encabezados de columnas
    cout << left << setw(10) << "Puesto" 
         << setw(15) << "Placa" 
         << setw(20) << "Hora Ingreso" 
         << setw(20) << "Hora Salida" << endl;
    cout << string(65, '-') << endl;

    bool historialEncontrado = false;

    // Recorrer la lista izquierda
    if (cabezaIzquierda) {
        Nodo* actualIzquierda = cabezaIzquierda;
        do {
            if (!actualIzquierda->gethoraIngreso().empty() || actualIzquierda->isOcupado()) {
                cout << setw(10) << actualIzquierda->getPuesto()
                     << setw(15) << actualIzquierda->getPlaca()
                     << setw(20) << actualIzquierda->gethoraIngreso();

                // Mostrar la hora de salida si existe, de lo contrario "Vehículo en uso"
                if (actualIzquierda->gethoraSalida().empty()) {
                    cout << setw(20) << "Vehículo parqueado";
                } else {
                    cout << setw(20) << actualIzquierda->gethoraSalida();
                }

                cout << endl;
                historialEncontrado = true;
            }
            actualIzquierda = actualIzquierda->getSiguiente();
        } while (actualIzquierda != cabezaIzquierda);
    }

    // Recorrer la lista derecha
    if (cabezaDerecha) {
        Nodo* actualDerecha = cabezaDerecha;
        do {
            if (!actualDerecha->gethoraIngreso().empty() || actualDerecha->isOcupado()) {
                cout << setw(10) << actualDerecha->getPuesto()
                     << setw(15) << actualDerecha->getPlaca()
                     << setw(20) << actualDerecha->gethoraIngreso();

                // Mostrar la hora de salida si existe, de lo contrario "Vehículo en uso"
                if (actualDerecha->gethoraSalida().empty()) {
                    cout << setw(20) << "Vehiculo parqueado";
                } else {
                    cout << setw(20) << actualDerecha->gethoraSalida();
                }

                cout << endl;
                historialEncontrado = true;
            }
            actualDerecha = actualDerecha->getSiguiente();
        } while (actualDerecha != cabezaDerecha);
    }

    if (!historialEncontrado) {
        cout << "No se ha registrado historial en el parqueadero." << endl;
    }
    cout << endl;
}
void ListaCircularDoble::guardarDatosSinPlaca() {
    ofstream archivo("DatosSinPlaca.txt");

    if (!archivo) {
        cout << "Error al abrir el archivo para guardar los datos sin placa." << endl;
        return;
    }

    Nodo* actualIzquierda = cabezaIzquierda;
    Nodo* actualDerecha = cabezaDerecha;

    // Recorrer la lista izquierda
    do {
        if (actualIzquierda->isOcupado()) {
            archivo << actualIzquierda->getNombre() << ","
                    << actualIzquierda->getSegundoNombre() << ","
                    << actualIzquierda->getApellido() << ","
                    << actualIzquierda->getSegundoApellido() << ","
                    << actualIzquierda->getCedula() << endl;
        }
        actualIzquierda = actualIzquierda->getSiguiente();
    } while (actualIzquierda != cabezaIzquierda);

    // Recorrer la lista derecha
    do {
        if (actualDerecha->isOcupado()) {
            archivo << actualDerecha->getNombre() << ","
                    << actualDerecha->getSegundoNombre() << ","
                    << actualDerecha->getApellido() << ","
                    << actualDerecha->getSegundoApellido() << ","
                    << actualDerecha->getCedula() << endl;
        }
        actualDerecha = actualDerecha->getSiguiente();
    } while (actualDerecha != cabezaDerecha);

    archivo.close();
    cout << "Datos sin placa guardados en 'DatosSinPlaca.txt'." << endl;
}
void ListaCircularDoble::guardarPlacas() {
    ofstream archivo("Placas.txt");

    if (!archivo) {
        cout << "Error al abrir el archivo para guardar las placas." << endl;
        return;
    }

    Nodo* actualIzquierda = cabezaIzquierda;
    Nodo* actualDerecha = cabezaDerecha;

    // Recorrer la lista izquierda
    do {
        if (actualIzquierda->isOcupado()) {
            archivo << actualIzquierda->getPlaca() << endl;
        }
        actualIzquierda = actualIzquierda->getSiguiente();
    } while (actualIzquierda != cabezaIzquierda);

    // Recorrer la lista derecha
    do {
        if (actualDerecha->isOcupado()) {
            archivo << actualDerecha->getPlaca() << endl;
        }
        actualDerecha = actualDerecha->getSiguiente();
    } while (actualDerecha != cabezaDerecha);

    archivo.close();
    cout << "Placas guardadas en 'Placas.txt'." << endl;
}
void ListaCircularDoble::guardarHistorial() {
    ofstream archivo("Historial.txt");

    if (!archivo) {
        cout << "Error al abrir el archivo para guardar el historial." << endl;
        return;
    }

    Nodo* actualIzquierda = cabezaIzquierda;
    Nodo* actualDerecha = cabezaDerecha;

    // Encabezados del historial
    archivo << "Puesto,Placa,Hora Ingreso,Hora Salida" << endl;

    // Recorrer la lista izquierda
    do {
        if (!actualIzquierda->gethoraIngreso().empty() || actualIzquierda->isOcupado()) {
            archivo << actualIzquierda->getPuesto() << ","
                    << actualIzquierda->getPlaca() << ","
                    << actualIzquierda->gethoraIngreso() << ",";
            if (actualIzquierda->gethoraSalida().empty()) {
                archivo << "Vehiculo parqueado" << endl;
            } else {
                archivo << actualIzquierda->gethoraSalida() << endl;
            }
        }
        actualIzquierda = actualIzquierda->getSiguiente();
    } while (actualIzquierda != cabezaIzquierda);

    // Recorrer la lista derecha
    do {
        if (!actualDerecha->gethoraIngreso().empty() || actualDerecha->isOcupado()) {
            archivo << actualDerecha->getPuesto() << ","
                    << actualDerecha->getPlaca() << ","
                    << actualDerecha->gethoraIngreso() << ",";
            if (actualDerecha->gethoraSalida().empty()) {
                archivo << "Vehiculo parqueado" << endl;
            } else {
                archivo << actualDerecha->gethoraSalida() << endl;
            }
        }
        actualDerecha = actualDerecha->getSiguiente();
    } while (actualDerecha != cabezaDerecha);

    archivo.close();
    cout << "Historial guardado en 'Historial.txt'." << endl;
}










