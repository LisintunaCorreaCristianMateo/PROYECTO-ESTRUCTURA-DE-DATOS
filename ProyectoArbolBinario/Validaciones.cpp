#include<iostream>
#include"Validaciones.h"
#include <conio.h>
#include <stdlib.h>
#include<string>

using namespace std;


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

float ingresar_float(const char* msj) {
    char cad[20]; 
    char c;
    int i = 0;
    bool decimal_point = false; 

    printf("%s", msj);

    while ((c = _getch()) != 13) { // Mientras no se presione Enter (ASCII 13)
        if ((c >= '0' && c <= '9') || (c == '.' && !decimal_point)) {
            if (c == '.') {
                decimal_point = true; // Marcar que se ingres� un punto decimal
            }
            printf("%c", c);       // Mostrar el car�cter ingresado
            cad[i++] = c;         // Guardarlo en el arreglo
        }
        else if (c == 8 && i > 0) { // Si se presiona Backspace y hay algo que borrar
            i--; // Reduce el �ndice para eliminar el �ltimo car�cter ingresado
            if (cad[i] == '.') {
                decimal_point = false; // Si se borr� un punto decimal, permitir otro
            }
            printf("\b \b"); // Retrocede, borra el car�cter en pantalla
        }
    }

    // Agregar .00 si no hay punto decimal
    if (!decimal_point) {
        cad[i++] = '.';
        cad[i++] = '0';
        cad[i++] = '0';
    }

    cad[i] = '\0'; // Cerrar la cadena con null terminator
    printf("\n"); // Salto de l�nea para mantener formato
    return atof(cad); 
}
string ingresar_string(const char* mensaje) {
    char cadena[100]; // Buffer para la cadena
    char c;
    int i = 0;
    bool tiene_letra = false; // Bandera para verificar si se ingres� al menos una letra

    cout << mensaje;

    while (true) {
        c = _getch();

        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ') {
            if (i < 99) { // Verificar que no exceda el tama�o del buffer
                cout << c; // Muestra el car�cter
                cadena[i++] = c; // Agrega el car�cter al arreglo
                if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                    tiene_letra = true; // Marca que se ingres� al menos una letra
                }
            }
        } else if (c == 8 && i > 0) { // Si se presiona Backspace y hay algo que borrar
            cout << "\b \b"; // Retrocede y borra el car�cter en pantalla
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
            i--; // Reduce el �ndice
        } else if (c == 13) { // Si se presiona Enter
            if (tiene_letra) { // Permitir Enter solo si se ingres� al menos una letra
                break;
            } else {
                cout << '\a'; // Beep para indicar error
            }
        }
    }

    cadena[i] = '\0'; // Termina la cadena con el null terminator
    cout << endl; // Salto de l�nea al finalizar

    return string(cadena); // Retorna como un objeto de tipo string
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


