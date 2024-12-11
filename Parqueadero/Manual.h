#ifndef MANUAL_H
#define MANUAL_H

#include <windows.h>

class Manual {
public:
    // M�todo p�blico para mostrar la ventana de ayuda
    void mostrar();

private:
    // M�todo est�tico para manejar eventos de la ventana
    static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    // Variable est�tica para rastrear si la clase de ventana ya fue registrada
    static bool claseRegistrada;
};

#endif
