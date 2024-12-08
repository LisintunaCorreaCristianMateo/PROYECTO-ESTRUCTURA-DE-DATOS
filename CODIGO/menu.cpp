#include "ListaCircularDoble.h"
#include "menu.h"
//#include"Validaciones.h"
#include "Archivotxt.h"
#include <iostream>
#include <conio.h>  // Para _getch()
#include <windows.h> // Para cambiar colores en la consola
#include <limits>
#include <string>
#include <cctype>


using namespace std;

		
    int totalPuestos = 20; 
    ListaCircularDoble parqueadero(totalPuestos);
    Archivotxt manejadorArchivos;

void menu(){

	
	
	const int numOpciones = 7;
    string opciones[numOpciones] = {"Ver parqueadero", "Ingresar vehiculo", "Retirar vehiculo","Ver Datos","Ver Vehiculos","Ver Historial", "Salir"};
    int opcionSeleccionada = 0; // Inicializamos la opciï¿½n seleccionada en 0

    while (true) {
        mostrarMenu(opcionSeleccionada, opciones, numOpciones);
        char tecla = _getch(); // Captura una tecla

        if (tecla == 13) { // Detecta Enter (cï¿½digo ASCII 13)
            system("cls"); // Limpia la consola
            procesarSeleccion(opciones[opcionSeleccionada]); // Procesa la opciï¿½n seleccionada
            if (opciones[opcionSeleccionada] == "Salir") {
                break; // Termina el programa si la opciï¿½n es "Salir"
            }
        } else if (tecla == -32) { // Detecta teclas especiales (como flechas)
            tecla = _getch(); // Captura la segunda parte del cï¿½digo de la tecla
            if (tecla == 72) { // Flecha arriba
                opcionSeleccionada = (opcionSeleccionada - 1 + numOpciones) % numOpciones;
            } else if (tecla == 80) { // Flecha abajo
                opcionSeleccionada = (opcionSeleccionada + 1) % numOpciones;
            }
        }
    }
}




// Funciï¿½n para cambiar el color de la consola
void cambiarColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Funciï¿½n para mostrar el menï¿½
void mostrarMenu(int opcionSeleccionada, const string opciones[], int numOpciones) {
    system("cls"); // Limpia la consola
    cout << "===  MENU ===\n";
    for (int i = 0; i < numOpciones; ++i) {
        if (i == opcionSeleccionada) {
            cambiarColor(3); // Cambiar el color de la opciï¿½n seleccionada (verde)
            cout << " " << opciones[i] << " \n"; // Opciï¿½n seleccionada resaltada
            cambiarColor(7);  // Volver al color normal (blanco)
        } else {
            cambiarColor(7);  // Color normal para las otras opciones
            cout << "  " << opciones[i] << "\n";
        }
    }
}

string ingresar_cedula(const char* mensaje) {
    char cedula[11]; // Buffer para 10 d?gitos m?s el null terminator
    char c;
    int i = 0;

    cout << mensaje;

    while (true) {
        c = _getch();

        if (c >= '0' && c <= '9') { // Si es un n?mero
            if (i < 10) { // Permitir hasta 10 d?gitos
                cout << c; // Mostrar el car?cter en pantalla
                cedula[i++] = c; // Agregar al arreglo
            }
        } else if (c == 8 && i > 0) { // Si se presiona Backspace y hay algo que borrar
            cout << "\b \b"; // Retrocede y borra el car?cter en pantalla
            i--; // Reduce el ?ndice
        } else if (c == 13) { // Si se presiona Enter
            if (i == 10) { // Permitir Enter solo si se ingresaron 10 d?gitos
                break;
            } else {
                // Emitir un sonido para indicar que no se permite Enter
                cout << '\a'; // Beep para indicar error
            }
        }
    }

    cedula[i] = '\0'; // Termina la cadena con el null terminator
    cout << endl; // Salto de l?nea al finalizar

    return string(cedula); // Retorna como un objeto string
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

string ingresar_string(const char* mensaje) {
    char cadena[100]; // Buffer para la cadena
    char c;
    int i = 0;
    bool tiene_letra = false; // Bandera para verificar si se ingres? al menos una letra

    cout << mensaje;

    while (true) {
        c = _getch();

        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ') {
            if (i < 99) { // Verificar que no exceda el tama?o del buffer
                cout << c; // Muestra el car?cter
                cadena[i++] = c; // Agrega el car?cter al arreglo
                if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                    tiene_letra = true; // Marca que se ingres? al menos una letra
                }
            }
        } else if (c == 8 && i > 0) { // Si se presiona Backspace y hay algo que borrar
            cout << "\b \b"; // Retrocede y borra el car?cter en pantalla
            if ((cadena[i - 1] >= 'A' && cadena[i - 1] <= 'Z') || 
                (cadena[i - 1] >= 'a' && cadena[i - 1] <= 'z')) {
                tiene_letra = false; // Puede ser necesario revisar si quedan letras
                for (int j = 0; j < i - 1; j++) {
                    if ((cadena[j] >= 'A' && cadena[j] <= 'Z') || 
                        (cadena[j] >= 'a' && cadena[j] <= 'z')) {
                        tiene_letra = true;
                        break;
                    }
                }
            }
            i--; // Reduce el ?ndice
        } else if (c == 13) { // Si se presiona Enter
            if (tiene_letra) { // Permitir Enter solo si se ingres? al menos una letra
                break;
            } else {
                cout << '\a'; // Beep para indicar error
            }
        }
    }

    cadena[i] = '\0'; // Termina la cadena con el null terminator
    cout << endl; // Salto de l?nea al finalizar

    return string(cadena); // Retorna como un objeto de tipo string
}

// Funciï¿½n para procesar la selecciï¿½n de una opciï¿½n
void procesarSeleccion(const string& opcion) {

    
//	Archivotxt manejadorArchivos;
	
    if (opcion == "Ver parqueadero") {
    	
    	 parqueadero.dibujarParqueadero();
    	 cout<<endl;
    	 cout<<endl;
    	 parqueadero.mostrarPuestosLibres();
    	

    } 
    
	else if (opcion == "Ingresar vehiculo") {
		
			string placa = validarPlaca();
			
            //string nombre,nombre2,apellido,apellido2;
            //cout << "Ingrese la placa del vehiculo: ";
            //cin >> placa;
            
            string cedula = ingresar_cedula("Ingrese la cedula (10 dígitos): ");
            //cout << "Ingrese la cedula: ";
            //cin>>cedula;
            
            string nombre = ingresar_string("Ingrese Primer Nombre: ");
            //cout<<"Ingrese el primer nombre: ";
            //cin>>nombre;
            
            string nombre2 = ingresar_string("Ingrese Segundo Nombre: ");
            
            //cout<<"Ingrese el Segundo nombre: ";
            //cin>>nombre2;
            
            string apellido = ingresar_string("Ingrese Primer Apellido: ");
            //cout<<"Ingrese el primer Apellido: ";
            //cin>>apellido;
            
            string apellido2 = ingresar_string("Ingrese Segundo Apellido: ");
            //cout<<"Ingrese el Segundo Apellido: ";
            //cin>>apellido2;

			
            parqueadero.ingresarVehiculo(placa,cedula,nombre,nombre2,apellido,apellido2);
            
            //metodos de txt
            
        	manejadorArchivos.guardarDatos(parqueadero);
        	manejadorArchivos.guardarPlacas(parqueadero);
            manejadorArchivos.guardarHistorial(parqueadero);	

        system("pause");
    	system("cls");
    
	}
	 else if (opcion == "Retirar vehiculo") {
	 	 int puesto;
        //manejadorArchivos.leerDesdeArchivo("estudiantes.txt",lista);
	        cout << "Ingrese el numero del puesto a liberar: ";
            cin >> puesto;
            parqueadero.retirarVehiculo(puesto);
		    
    }
    else if(opcion =="Ver Datos"){
        parqueadero.mostrarDatos();

    }
    else if(opcion=="Ver Vehiculos"){
        parqueadero.mostrarAutos();

    }
    else if(opcion=="Ver Historial"){
         parqueadero.mostrarHistorial();
    }

	else if (opcion == "Salir") {
        cout << "Saliendo del programa...\n";
    } else {
        cout << "Opcion no valida.\n";
    }
    system("pause"); // Pausa para permitir que el usuario lea el mensaje
}

