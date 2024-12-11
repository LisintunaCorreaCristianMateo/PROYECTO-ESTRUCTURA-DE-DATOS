    #include "ListaCircularDoble.h"
    #include "ListaCircularHistorial.h"
    #include "Archivotxt2.h"
	#include<iostream>
	#include <vector>
	#include <ctime>
	#include <iomanip>
	#include <string>
    #include <fstream>

	using namespace std;

    ListaCircularHistorial historial;
    Archivotxt2 manejadorArchivosHistorial2;


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
    // Funci�n para obtener la fecha actual
string obtenerFechaActual() {
    time_t tiempoActual = time(nullptr);
    tm* fechaLocal = localtime(&tiempoActual);

    char buffer[20]; // Buffer para almacenar la fecha
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", fechaLocal);

    return string(buffer);
}
// Funci�n para obtener la hora actual
string obtenerHoraActual() {
    time_t tiempoActual = time(nullptr);
    tm* horaLocal = localtime(&tiempoActual);

    char buffer[20]; // Buffer para almacenar la hora
    strftime(buffer, sizeof(buffer), "%H:%M:%S", horaLocal);

    return string(buffer);
}

    // Funci�n para insertar un nodo en la lista circular
void ListaCircularDoble::insertarNodo(int puesto, bool esIzquierda) {
    Nodo* nuevo = new Nodo(puesto,"","","","","","","","","");
    if (esIzquierda) {
        if (!cabezaIzquierda) { // Si la lista izquierda está vacía
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
        if (!cabezaDerecha) { // Si la lista derecha está vacía
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


    // Funci�n para dibujar el parqueadero en forma de anillo
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


    // Funci�n para determinar los puestos vac�os
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

    // Funci�n para ingresar un veh�culo en un puesto vac�o aleatorio
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

    // Seleccionar un puesto vac�o aleatorio
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
    string fecha =obtenerFechaActual();
    string horaIngreso=obtenerHoraActual();


    puestoSeleccionado->setHoraIngreso(horaIngreso);
    puestoSeleccionado->setFecha(fecha);
    //puestoSeleccionado->setHoraSalida(""); // Inicializar vac�o
    puestoSeleccionado->setOcupado(true);

    //Guardar copia de los datos en el historial
    historial.ingresarVehiculo(puestoSeleccionado->getPuesto() ,placa,cedula,nombre,segundoNombre,apellido,segundoApellido,fecha,horaIngreso);

    manejadorArchivosHistorial2.guardarHistorial(historial);
    // Confirmaci�n de ingreso
    cout << "Vehiculo con placa " << placa << " ingresado en el puesto " << puestoSeleccionado->getPuesto() << "." << endl;
}



    // Funci�n para eliminar un veh�culo
void ListaCircularDoble::retirarVehiculo(int puesto) {
    Nodo* actual = cabezaIzquierda;
	string placa;
    
    do {
        if (actual->getPuesto() == puesto) {
            if (actual->isOcupado()) {
                cout << "Vehiculo con placa " << actual->getPlaca() 
                     << " retirado del puesto " << puesto << "." << endl;

                //extraer placa
                placa=actual->getPlaca();
                
               
                
                historial.cambiarFechaSalida(placa,obtenerHoraActual());
                manejadorArchivosHistorial2.guardarHistorial(historial);
                //cout<<"\nLa placa que fue enviada a comparar es : "<<placa<<"A las : "<<obtenerHoraActual()<<endl;

                actual->setOcupado(false);
                actual->setPlaca(string(""));


            } else {
                cout << "El puesto " << puesto << " esta� libre." << endl;
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

                //extraer placa
                placa=actual->getPlaca();
                
                manejadorArchivosHistorial2.leerHistorial(historial);
                historial.cambiarFechaSalida(placa,obtenerHoraActual());
                 manejadorArchivosHistorial2.guardarHistorial(historial);

                actual->setOcupado(false);
                actual->setPlaca("");
            } else {
                cout << "El puesto " << puesto << " esta� libre." << endl;
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
         << setw(15) << "Cedula" 
         << setw(10) << "Placa" << endl;
    cout << string(95, '-') << endl;

    // Recorrer todos los nodos en la fila izquierda
    do {
        if (actualIzquierda->isOcupado()) { // Verifica si el puesto est� ocupado
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
        if (actualDerecha->isOcupado()) { // Verifica si el puesto est� ocupado
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

    if (!cabezaIzquierda && !cabezaDerecha) { // Verifica si ambas listas est�n vac�as
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


