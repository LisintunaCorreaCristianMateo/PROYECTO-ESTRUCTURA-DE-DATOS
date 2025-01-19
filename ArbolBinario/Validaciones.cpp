#include<iostream>
#include"Validaciones.h"
#include <conio.h>
#include <stdlib.h>
#include<string>

using namespace std;


int ingresar_entero(const char *mensaje) {
    char num[10]; // Buffer para almacenar el número
    char c;
    int i = 0;
    bool tiene_digito = false; // Bandera para verificar si se ingresó al menos un dígito
    bool tiene_signo = false; // Bandera para verificar si se ingresó el signo negativo
    int valor;

    cout << mensaje;

    while (true) {
        c = getch();

        if (c >= '0' && c <= '9') {
            if (i < 9) {
                cout << c;
                num[i++] = c;
                tiene_digito = true;
            }
        } else if (c == '-' && i == 0) {
            cout << c;
            num[i++] = c;
            tiene_signo = true;
        } else if (c == 8 && i > 0) {
            cout << "\b \b";
            i--;
            if (i == 0) {
                tiene_digito = false;
                tiene_signo = false;
            }
        } else if (c == 13) {
            if (tiene_digito) {
                break;
            } else {
                cout << '\a';
            }
        }
    }

    num[i] = '\0';
    valor = atoi(num);

    return valor;
}


