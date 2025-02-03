#include "ArbolParqueadero.h"
#include "Historialtxt.h"
#include "menu.h"
#include"Validaciones.h"
#include "Archivostxt.h"
#include <iostream>
#include <conio.h>  // Para _getch()
#include <windows.h> // Para cambiar colores en la consola
#include <limits>
#include <ctime>
#include <regex>


using namespace std;


ArbolParqueadero arbol;
ArbolHistorial arbolHistorial;
Historialtxt manejadorArchivosHistorial;
Archivostxt manejadorArchivos;

void menu(){

	
	
	const int numOpciones = 14; // Número de opciones actualizado
    string opciones[numOpciones] = {"Ver Vehiculos Parqueados", "Insertar Coche", "Busqueda por Placa","Busqueda por Nombre",
                                    "Busqueda por Cedula","Liberar un Vehiculo","Imprimir Preorden","Imprimir Posorden","Ayuda","Mostrar Arbol","Imprimir Historial Inorden","Mostrar Arbol Historial","Mostrar Altura, Nivel y Profundidad del Arbol","Salir" };
    int opcionSeleccionada = 0; // Inicializamos la opción seleccionada en 0

    while (true) {
        mostrarMenu(opcionSeleccionada, opciones, numOpciones);
        char tecla = _getch(); // Captura una tecla

        if (tecla == 13) { // Detecta Enter (código ASCII 13)
            system("cls"); // Limpia la consola
            procesarSeleccion(opciones[opcionSeleccionada]); // Procesa la opción seleccionada
            if (opciones[opcionSeleccionada] == "Salir") {
                break; // Termina el programa si la opción es "Salir"
            }
        } else if (tecla == -32) { // Detecta teclas especiales (como flechas)
            tecla = _getch(); // Captura la segunda parte del código de la tecla
            if (tecla == 72) { // Flecha arriba
                opcionSeleccionada = (opcionSeleccionada - 1 + numOpciones) % numOpciones;
            } else if (tecla == 80) { // Flecha abajo
                opcionSeleccionada = (opcionSeleccionada + 1) % numOpciones;
            }
        }
    }
}




// Funci�n para cambiar el color de la consola
void cambiarColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Funci�n para mostrar el men�
void mostrarMenu(int opcionSeleccionada, const string opciones[], int numOpciones) {
    system("cls"); // Limpia la consola
    cout << "=== Parqueadero de Vehiculos ===\n";
    for (int i = 0; i < numOpciones; ++i) {
        if (i == opcionSeleccionada) {
            cambiarColor(3); // Cambiar el color de la opci�n seleccionada (verde)
            cout << " " << opciones[i] << " \n"; // Opci�n seleccionada resaltada
            cambiarColor(7);  // Volver al color normal (blanco)
        } else {
            cambiarColor(7);  // Color normal para las otras opciones
            cout << "  " << opciones[i] << "\n";
        }
    }
}
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

// Función para validar la hora ingresada
bool esHoraValida(const string& hora) {
    regex formatoHora("^(2[0-3]|[01]?[0-9]):([0-5]?[0-9]):([0-5]?[0-9])$");
    return regex_match(hora, formatoHora);
}

// Función para validar la fecha ingresada
bool esFechaValida(const string& fecha) {
    regex formatoFecha("^([0-2][0-9]|3[01])/(0[1-9]|1[0-2])/([0-9]{4})$");
    if (!regex_match(fecha, formatoFecha)) {
        return false;
    }

    int dia, mes, anio;
    sscanf(fecha.c_str(), "%d/%d/%d", &dia, &mes, &anio);

    // Obtener la fecha actual
    time_t tiempoActual = time(nullptr);
    tm* fechaLocal = localtime(&tiempoActual);
    int diaActual = fechaLocal->tm_mday;
    int mesActual = fechaLocal->tm_mon + 1;
    int anioActual = fechaLocal->tm_year + 1900;

    // Comparar la fecha ingresada con la fecha actual
    if (anio > anioActual || (anio == anioActual && mes > mesActual) || (anio == anioActual && mes == mesActual && dia > diaActual)) {
        return false;
    }

    return true;
}
string validarPlaca() {
    string placa;
    while (true) {
        cout << "Ingrese la placa del vehiculo (formato: ABC1234): ";
        cin >> placa;

        // Verificar longitud
        if (placa.length() != 7) {
            cout << "Placa inválida. Debe tener exactamente 7 caracteres.\n";
            continue;
        }

        // Validar que la placa comience con letras permitidas
        char primeraLetra = placa[0];
        string letrasPermitidas = "ABUCOEXHOWGILRMVNSPKQTZY";
        if (letrasPermitidas.find(primeraLetra) == string::npos) {
            cout << "Placa inválida. La primera letra debe ser una de las siguientes: "
                 << "A, B, U, C, X, H, O, E, W, G, I, L, R, M, V, N, S, P, K, Q, T, Z, Y.\n";
            continue;
        }

        // Validar formato: 3 letras seguidas de 4 números
        bool valido = true;
        for (int i = 0; i < 3; i++) {
            if (!isalpha(placa[i]) || !isupper(placa[i])) { // Las primeras 3 deben ser letras mayúsculas
                valido = false;
                break;
            }
        }
        for (int i = 3; i < 7; i++) {
            if (!isdigit(placa[i])) { // Las siguientes 4 deben ser números
                valido = false;
                break;
            }
        }

        if (valido) {
            break; // Placa válida, salir del bucle
        } else {
            cout << "Placa inválida. Debe tener 3 letras mayúsculas seguidas de 4 números (ejemplo: ABC1234).\n";
        }
    }
    return placa;
}


// Funci�n para procesar la selecci�n de una opci�n
void procesarSeleccion(const string& opcion) {
	 manejadorArchivos.leerDesdeArchivo("vehiculos.txt",arbol);
     manejadorArchivosHistorial.leerHistorialTxt("historial.txt",arbolHistorial);
    
	if(opcion=="Ver Vehiculos Parqueados"){
        arbol.imprimirInorden();

    }
    else if (opcion == "Insertar Coche") {
       
    	
        
                
                string fecha,horaIngreso,placa,cedula,nombre,segundoNombre,apellido,segundoApellido;

                fecha=obtenerFechaActual();
                horaIngreso=obtenerHoraActual();

                placa = validarPlaca();

                    // Verificar si la placa ya existe en el árbol de vehículos
                NodoVehiculo* nodoVehiculoExistente = arbol.buscarPorPlaca(placa);
                if (nodoVehiculoExistente != nullptr) {
                    std::cout << "El vehiculo ya esta parqueado." << std::endl;
                    system("pause");
                    return;
                }
                NodoHistorial* nodoHistorial = arbolHistorial.buscarEnHistorial( placa);

                if (nodoHistorial != nullptr) {
                    // La placa ya existe en el historial, pasar los atributos a NodoVehiculo
                    cedula = nodoHistorial->getCedula();
                    nombre = nodoHistorial->getNombre();
                    segundoNombre = nodoHistorial->getSegundoNombre();
                    apellido = nodoHistorial->getApellido();
                    segundoApellido = nodoHistorial->getSegundoApellido();

                } else {
                    // La placa no existe en el historial, continuar con la entrada de datos
                    cedula = ingresar_cedula("Ingrese la cedula del propietario: ");
                    nombre = ingresar_string("Ingrese el nombre del propietario: ");
                    segundoNombre = ingresar_string("Ingrese el segundo nombre del propietario: ");
                    apellido = ingresar_string("Ingrese el apellido del propietario: ");
                    segundoApellido = ingresar_string("Ingrese el segundo apellido del propietario: ");

                }
                    fecha = obtenerFechaActual();
                    horaIngreso = obtenerHoraActual();

                // Inicializar la semilla para la generación de números aleatorios
                std::srand(std::time(nullptr));

                // Obtener todos los puestos ocupados del árbol
                std::unordered_set<int> puestosOcupados;
                arbol.obtenerPuestosOcupados(arbol.getRaiz(), puestosOcupados);

                // Generar un número aleatorio entre 1 y 40 que no esté ocupado
                int puesto;
                bool puestoEncontrado = false;
                for (int intentos = 0; intentos < 40; ++intentos) {
                    puesto = std::rand() % 40 + 1;
                    if (!arbol.puestoOcupado(puesto, puestosOcupados)) {
                        puestoEncontrado = true;
                        break;
                    }
                }

                if (!puestoEncontrado) {
                    std::cout << "Todos los puestos están llenos." << std::endl;
                    return;
                }

                NodoVehiculo* nuevoVehiculo = new NodoVehiculo(puesto,placa,cedula,nombre,segundoNombre,apellido,segundoApellido,fecha,horaIngreso);
                
                arbol.insertar(nuevoVehiculo);
                        // Crear un nuevo nodo de historial con los datos actualizados
                NodoHistorial* nuevoHistorial = new NodoHistorial(puesto,placa,cedula,nombre,segundoNombre,apellido,segundoApellido,fecha,horaIngreso);
                arbolHistorial.insertar(nuevoHistorial);
                        
                cout<<"\nVehiculo parqueado con exito en el puesto: "<<puesto;
                cout<<endl;
            // Guarda en el txt
                manejadorArchivos.guardarEnArchivo("vehiculos.txt",arbol);
                manejadorArchivosHistorial.guardarHistorialTxt("historial.txt",arbolHistorial);
                
    } 
    
	else if (opcion == "Busqueda por Placa") {
		
        string placa;
        placa = validarPlaca();
 
        arbol.buscarPlaca(placa);

    
	}
	 else if (opcion == "Busqueda por Nombre") {
        
        string nombre=ingresar_string("Ingrese el nombre del propietario: ");
        arbol.buscarPorNombre(nombre);
		 
    } 
    else if(opcion == "Busqueda por Cedula"){
        string cedula;
 
        cedula=ingresar_cedula("\nIngrese la cedula del propietario: ");
        arbol.buscarPorCedula(cedula);

      

    }

    else if(opcion == "Liberar un Vehiculo"){
        arbol.imprimirInorden();
			
		string placa;
        cout<<"\nIngrese la plca del vehiculo a eliminar: ";
        cin >> placa;
        arbol.eliminar(placa);
		    
		manejadorArchivos.guardarEnArchivo("vehiculos.txt",arbol);
		 

      
    }
    else if(opcion=="Imprimir Preorden"){
        arbol.imprimirPreorden();


    }
    else if(opcion=="Imprimir Posorden"){
        arbol.imprimirPosorden();
    }

    else if(opcion=="Ayuda"){
         cout << "========================================" << endl;
         cout << "========================================" << endl;
         cout << "               (i)AYUDA                 " << endl;
         cout << "========================================" << endl;
         cout << "========================================" << endl;
         string archivo = "ayuda.html";
         string comando = "start " + archivo;
         system(comando.c_str());

    }
    else if (opcion == "Mostrar Arbol") {
        arbol.graficarArbol(arbol.getRaiz());
    }
    else if (opcion == "Imprimir Historial Inorden") {
        arbolHistorial.imprimirHistorialInorden();
    }
else if (opcion == "Mostrar Arbol Historial") {
    int espacio = 0; // Define el valor inicial para espacio
    int incremento = 10; // Define el valor para incremento
    arbolHistorial.graficarArbolHistorial(arbolHistorial.getRaiz(), espacio, incremento);
}

else if (opcion == "Mostrar Altura, Nivel y Profundidad del Arbol") {
    int altura = arbol.obtenerAltura(arbol.getRaiz());
    int nivel = arbol.obtenerNivel(arbol.getRaiz());
    int profundidad = arbol.obtenerProfundidad(arbol.getRaiz());
    cout << "Altura del arbol: " << altura << endl;
    cout << "Nivel del arbol: " << nivel << endl;
    cout << "Profundidad del arbol: " << profundidad << endl;
}

else if (opcion == "Salir") {
     cout << "Saliendo del programa...\n";
    }
    else {
        cout << "Opcion no valida.\n";
    }
    system("pause"); // Pausa para permitir que el usuario lea el mensaje
}


