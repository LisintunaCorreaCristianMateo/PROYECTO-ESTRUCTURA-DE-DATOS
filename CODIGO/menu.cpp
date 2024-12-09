#include "ListaCircularDoble.h"
#include "ListaCircularHistorial.h"
#include "menu.h"
//#include"Validaciones.h"
#include "Archivotxt.h"
#include "Archivotxt2.h"
#include <iostream>
#include <conio.h>  // Para _getch()
#include <windows.h> // Para cambiar colores en la consola
#include <limits>
#include <string>
#include <cctype>


using namespace std;

		
    int totalPuestos = 20; 
    ListaCircularDoble parqueadero(totalPuestos);
    ListaCircularHistorial Historial;
    Archivotxt manejadorArchivos;
    Archivotxt2 manejadorArchivosHistorial;

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

// Declaración e implementación de validarCedulaEcuatoriana
bool validarCedulaEcuatoriana(const std::string& cedula) {
    // Verificar que la longitud sea exactamente 10
    if (cedula.length() != 10) return false;

    // Verificar que los primeros dos dígitos (código de provincia) estén en el rango 01-24
    int provincia = stoi(cedula.substr(0, 2));
    if (provincia < 1 || provincia > 24) return false;

    // Algoritmo de validación del dígito verificador
    int suma = 0;
    for (int i = 0; i < 9; ++i) {
        int num = cedula[i] - '0';
        if (i % 2 == 0) { // Si el índice es par
            num *= 2;
            if (num > 9) num -= 9;
        }
        suma += num;
    }

    // Cálculo del dígito verificador
    int digitoVerificador = (10 - (suma % 10)) % 10;

    // Comparar con el último dígito de la cédula
    return (cedula[9] - '0') == digitoVerificador;
}

// Función ingresar_cedula que usa validarCedulaEcuatoriana
string ingresar_cedula(const char* mensaje) {
    char cedula[11]; // Buffer para 10 dígitos más el null terminator
    char c;
    int i = 0;

    while (true) {
        i = 0; // Reiniciar índice
        cout << mensaje;

        // Capturar los 10 dígitos de la cédula
        while (true) {
            c = _getch();

            if (c >= '0' && c <= '9') { // Si es un número
                if (i < 10) { // Permitir hasta 10 dígitos
                    cout << c; // Mostrar el carácter en pantalla
                    cedula[i++] = c; // Agregar al arreglo
                }
            } else if (c == 8 && i > 0) { // Si se presiona Backspace y hay algo que borrar
                cout << "\b \b"; // Retrocede y borra el carácter en pantalla
                i--; // Reduce el índice
            } else if (c == 13) { // Si se presiona Enter
                if (i == 10) { // Permitir Enter solo si se ingresaron 10 dígitos
                    break;
                } else {
                    // Emitir un sonido para indicar que no se permite Enter
                    cout << '\a'; // Beep para indicar error
                }
            }
        }

        cedula[i] = '\0'; // Termina la cadena con el null terminator
        cout << endl; // Salto de línea al finalizar

        // Validar la cédula ecuatoriana
        if (validarCedulaEcuatoriana(cedula)) {
            return string(cedula); // Si la cédula es válida, retornarla
        } else {
            cout << "Cédula inválida. Por favor, intente nuevamente.\n";
        }
    }
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

            //metodos para la lectura txt
            manejadorArchivos.leerPlacas(parqueadero);
            manejadorArchivos.leerDatos(parqueadero);
           manejadorArchivosHistorial.leerHistorial(Historial);
            

	
    if (opcion == "Ver parqueadero") {
    	    //metodos para la lectura txt

    	 parqueadero.dibujarParqueadero();
    	 cout<<endl;
    	 cout<<endl;
    	 parqueadero.mostrarPuestosLibres();
    	

    } 
    
	else if (opcion == "Ingresar vehiculo") {
		
			


			string placa = validarPlaca();

            string cedula = ingresar_cedula("Ingrese la cedula (10 dï¿½gitos): ");
            
            string nombre = ingresar_string("Ingrese Primer Nombre: ");
            
            string nombre2 = ingresar_string("Ingrese Segundo Nombre: ");
            
            string apellido = ingresar_string("Ingrese Primer Apellido: ");

            string apellido2 = ingresar_string("Ingrese Segundo Apellido: ");
     
           parqueadero.ingresarVehiculo(placa,cedula,nombre,nombre2,apellido,apellido2);
           // Historial.ingresarVehiculo(placa,cedula,nombre,nombre2,apellido,apellido2)
            //metodos de txt para guardar en el txt
            
        	manejadorArchivos.guardarDatos(parqueadero);
        	manejadorArchivos.guardarPlacas(parqueadero);
            //manejadorArchivos.guardarHistorial(parqueadero);
        


        system("pause");
    	system("cls");
    
	}
	 else if (opcion == "Retirar vehiculo") {

	 	 int puesto;
        //manejadorArchivos.leerDesdeArchivo("estudiantes.txt",lista);
	        cout << "Ingrese el numero del puesto a liberar: ";
            cin >> puesto;
            parqueadero.retirarVehiculo(puesto);
		                
        	manejadorArchivos.guardarDatos(parqueadero);
        	manejadorArchivos.guardarPlacas(parqueadero);
            //manejadorArchivos.guardarHistorial(parqueadero);
    }
    else if(opcion =="Ver Datos"){

        parqueadero.mostrarDatos();

    }
    else if(opcion=="Ver Vehiculos"){


        parqueadero.mostrarAutos();

    }
    else if(opcion=="Ver Historial"){
    	
         Historial.mostrarHistorial();
    }

	else if (opcion == "Salir") {
        cout << "Saliendo del programa...\n";
    } else {
        cout << "Opcion no valida.\n";
    }
    system("pause"); // Pausa para permitir que el usuario lea el mensaje
}

