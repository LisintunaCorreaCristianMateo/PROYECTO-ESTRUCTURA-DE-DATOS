#ifndef MANUAL_H
#define MANUAL_H

#include <windows.h>

class Manual {
public:
    // Método público para mostrar la ventana de ayuda
    void mostrar();

private:
    // Método estático para manejar eventos de la ventana
    static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    // Variable estática para rastrear si la clase de ventana ya fue registrada
    static bool claseRegistrada;
};

#endif
