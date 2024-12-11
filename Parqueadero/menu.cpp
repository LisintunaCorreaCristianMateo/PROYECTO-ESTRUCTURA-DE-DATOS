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
	
		
		
		const int numOpciones = 9; // Incrementar el n�mero de opciones
		string opciones[numOpciones] = {"Ver parqueadero", "Ingresar vehiculo", "Retirar vehiculo", "Ver Datos", "Ver Vehiculos", "Ver Historial", "Busqueda por fecha", "Busqueda por horas", "Salir"};
	    int opcionSeleccionada = 0; // Inicializamos la opci�n seleccionada en 0
	
	    while (true) {
	        mostrarMenu(opcionSeleccionada, opciones, numOpciones);
	        char tecla = _getch(); // Captura una tecla
	
	        if (tecla == 13) { // Detecta Enter (c�digo ASCII 13)
	            system("cls"); // Limpia la consola
	            procesarSeleccion(opciones[opcionSeleccionada]); // Procesa la opci�n seleccionada
	            if (opciones[opcionSeleccionada] == "Salir") {
	                break; // Termina el programa si la opci�n es "Salir"
	            }
	        } else if (tecla == -32) { // Detecta teclas especiales (como flechas)
	            tecla = _getch(); // Captura la segunda parte del c�digo de la tecla
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
	    cout << "===  MENU ===\n";
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
	
	// Declaraci�n e implementaci�n de validarCedulaEcuatoriana
	bool validarCedulaEcuatoriana(const std::string& cedula) {
	    // Verificar que la longitud sea exactamente 10
	    if (cedula.length() != 10) return false;
	
	    // Verificar que los primeros dos d�gitos (c�digo de provincia) est�n en el rango 01-24
	    int provincia = stoi(cedula.substr(0, 2));
	    if (provincia < 1 || provincia > 24) return false;
	
	    // Algoritmo de validaci�n del d�gito verificador
	    int suma = 0;
	    for (int i = 0; i < 9; ++i) {
	        int num = cedula[i] - '0';
	        if (i % 2 == 0) { // Si el �ndice es par
	            num *= 2;
	            if (num > 9) num -= 9;
	        }
	        suma += num;
	    }
	
	    // C�lculo del d�gito verificador
	    int digitoVerificador = (10 - (suma % 10)) % 10;
	
	    // Comparar con el �ltimo d�gito de la c�dula
	    return (cedula[9] - '0') == digitoVerificador;
	}
	
	// Funci�n ingresar_cedula que usa validarCedulaEcuatoriana
	string ingresar_cedula(const char* mensaje) {
	    char cedula[11]; // Buffer para 10 d�gitos m�s el null terminator
	    char c;
	    int i = 0;
	
	    while (true) {
	        i = 0; // Reiniciar �ndice
	        cout << mensaje;
	
	        // Capturar los 10 d�gitos de la c�dula
	        while (true) {
	            c = _getch();
	
	            if (c >= '0' && c <= '9') { // Si es un n�mero
	                if (i < 10) { // Permitir hasta 10 d�gitos
	                    cout << c; // Mostrar el car�cter en pantalla
	                    cedula[i++] = c; // Agregar al arreglo
	                }
	            } else if (c == 8 && i > 0) { // Si se presiona Backspace y hay algo que borrar
	                cout << "\b \b"; // Retrocede y borra el car�cter en pantalla
	                i--; // Reduce el �ndice
	            } else if (c == 13) { // Si se presiona Enter
	                if (i == 10) { // Permitir Enter solo si se ingresaron 10 d�gitos
	                    break;
	                } else {
	                    // Emitir un sonido para indicar que no se permite Enter
	                    cout << '\a'; // Beep para indicar error
	                }
	            }
	        }
	
	        cedula[i] = '\0'; // Termina la cadena con el null terminator
	        cout << endl; // Salto de l�nea al finalizar
	
	        // Validar la c�dula ecuatoriana
	        if (validarCedulaEcuatoriana(cedula)) {
	            return string(cedula); // Si la c�dula es v�lida, retornarla
	        } else {
	            cout << "C�dula inv�lida. Por favor, intente nuevamente.\n";
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
	            cout << "Placa inv�lida. Debe tener exactamente 7 caracteres.\n";
	            continue;
	        }
	
	        // Validar que la placa comience con letras permitidas
	        char primeraLetra = placa[0];
	        string letrasPermitidas = "ABUCOEXHOWGILRMVNSPKQTZY";
	        if (letrasPermitidas.find(primeraLetra) == string::npos) {
	            cout << "Placa inv�lida. La primera letra debe ser una de las siguientes: "
	                 << "A, B, U, C, X, H, O, E, W, G, I, L, R, M, V, N, S, P, K, Q, T, Z, Y.\n";
	            continue;
	        }
	
	        // Validar formato: 3 letras seguidas de 4 n�meros
	        bool valido = true;
	        for (int i = 0; i < 3; i++) {
	            if (!isalpha(placa[i]) || !isupper(placa[i])) { // Las primeras 3 deben ser letras may�sculas
	                valido = false;
	                break;
	            }
	        }
	        for (int i = 3; i < 7; i++) {
	            if (!isdigit(placa[i])) { // Las siguientes 4 deben ser n�meros
	                valido = false;
	                break;
	            }
	        }
	
	        if (valido) {
	            break; // Placa v�lida, salir del bucle
	        } else {
	            cout << "Placa inv�lida. Debe tener 3 letras may�sculas seguidas de 4 n�meros (ejemplo: ABC1234).\n";
	        }
	    }
	    return placa;
	}
	int ingresar_entero(const char *mensaje) {
	    char num[10]; // Buffer para almacenar el n�mero
	    char c;
	    int i = 0;
	    bool tiene_digito = false; // Bandera para verificar si se ingres� al menos un d�gito
	    int valor;
	
	    cout << mensaje;
	
	    while (true) {
	        c = getch();
	
	        if (c >= '0' && c <= '9') { // Si es un n�mero
	            if (i < 9) { // Verifica que no exceda el tama�o del buffer
	                cout << c; // Muestra el car�cter
	                num[i++] = c; // Agrega al arreglo
	                tiene_digito = true; // Marca que se ingres� al menos un d�gito
	            }
	        } else if (c == 8 && i > 0) { // Si se presiona Backspace y hay algo que borrar
	            cout << "\b \b"; // Retrocede, borra el car�cter en pantalla
	            i--; // Reduce el �ndice para eliminar el �ltimo car�cter ingresado
	            if (i == 0) {
	                tiene_digito = false; // Si no quedan caracteres, resetea la bandera
	            }
	        } else if (c == 13) { // Si se presiona Enter
	            if (tiene_digito) { // Permitir Enter solo si se ingres� al menos un d�gito
	                break;
	            } else {
	                cout << '\a'; // Beep para indicar error
	            }
	        }
	    }
	
	    num[i] = '\0'; // Termina la cadena
	    valor = atoi(num); // Convierte la cadena a entero
	
	    return valor;
	}
	
	
	bool ListaCircularDoble::existePlaca(const string& placa) {
	    Nodo* actual = cabezaIzquierda;
	
	    // Verificar en la fila izquierda
	    do {
	        if (actual->getPlaca() == placa) {
	            return true; // Placa encontrada
	        }
	        actual = actual->getSiguiente();
	    } while (actual != cabezaIzquierda);
	
	    // Verificar en la fila derecha
	    actual = cabezaDerecha;
	    do {
	        if (actual->getPlaca() == placa) {
	            return true; // Placa encontrada
	        }
	        actual = actual->getSiguiente();
	    } while (actual != cabezaDerecha);
	
	    return false; // Placa no encontrada
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
	
	
	// Funci�n para procesar la selecci�n de una opci�n
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
			
				
	         while (true) {
	            string placa = validarPlaca();
	
	             // Validar que la placa no exista en el parqueadero
	             if (parqueadero.existePlaca(placa)) {
	            cout << "La placa " << placa << " ya está registrada en el parqueadero. Intente con otra.\n";
	            }
	             else {
	
	                    bool existePlaca=false;
	                    existePlaca=Historial.existeVehiculoHistorial(placa,parqueadero);
	
	                    if(existePlaca==false){
	                        string cedula = ingresar_cedula("Ingrese la cedula (10 d�gitos): ");
	                        string nombre = ingresar_string("Ingrese Primer Nombre: ");
	                            // Hacer el segundo nombre opcional
	                        cout << "Ingrese Segundo Nombre (opcional, presione Enter para omitir): ";
	                        cin.ignore(); // Limpiar el buffer de entrada
	                        string nombre2;
	                        getline(cin, nombre2); // Leer l�nea completa
	                        if (nombre2.empty()) {
	                            nombre2 = ""; // Si est� vac�o, asignar un valor en blanco
	                        }
	                        
	                        string apellido = ingresar_string("Ingrese Primer Apellido: ");
	                            // Hacer el segundo apellido opcional
	                        cout << "Ingrese Segundo Apellido (opcional, presione Enter para omitir): ";
	                        cin.ignore(); // Limpiar el buffer de entrada
	                        string apellido2;
	                        getline(cin, apellido2); // Leer l�nea completa
	
	                        if (apellido2.empty()) {
	                            apellido2 = ""; // Si est� vac�o, asignar un valor en blanco
	                        }
	                            
	                            
	                            parqueadero.ingresarVehiculo(placa,cedula,nombre,nombre2,apellido,apellido2);
	
	                        
	                            // Salir del bucle una vez que se haya ingresado el vehículo
	                                    
	                    }
	
	
	                
	                            manejadorArchivos.guardarDatos(parqueadero);
	                            manejadorArchivos.guardarPlacas(parqueadero);
	                 break;
	             }
	
	            
	    
		
	        }
	        	
	    }
	
	
	
	
		 else if (opcion == "Retirar vehiculo") {
	        
		 	 
	            int puesto=ingresar_entero( "Ingrese el numero del puesto a liberar: ");
	
	
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
	    else if(opcion=="Busqueda por fecha"){
	         string fechaBuscada;
	        cout << "Ingrese la fecha que desea buscar (formato: dd/mm/aaaa): ";
	        cin >> fechaBuscada;
	
	    // Buscar historial por fecha
	    Historial.buscarPorFecha(fechaBuscada);
	    }else if (opcion == "Busqueda por horas") {
	    string horaInicio, horaFin;
	    cout << "Ingrese la hora de inicio (formato HH:MM): ";
	    cin >> horaInicio;
	    cout << "Ingrese la hora de fin (formato HH:MM): ";
	    cin >> horaFin;
	
	    // Buscar historial por rango de horas
	    Historial.buscarPorHoras(horaInicio, horaFin);
	}
	
		else if (opcion == "Salir") {
	        cout << "Saliendo del programa...\n";
	    } else {
	        cout << "Opcion no valida.\n";
	    }
	    system("pause"); // Pausa para permitir que el usuario lea el mensaje
	}

