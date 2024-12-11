#include "Manual.h"
#include <sstream>
#include <iostream>
#include <windows.h>
#include <cstring>
#include <vector>
#include <sstream>


bool Manual::claseRegistrada = false;
int offsetY = 0; // Controlar la posici�n de desplazamiento

LRESULT CALLBACK Manual::WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_SIZE: {
            // Forzar el redibujado
            RECT rect;
            GetClientRect(hwnd, &rect);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Limpiar la pantalla para evitar que se repitan las palabras
            RECT rect;
            GetClientRect(hwnd, &rect);  // Obtener las dimensiones del �rea cliente de la ventana
            FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1)); // Limpiar con el color de fondo

            // Contenido de las instrucciones
            const char* instrucciones =
                "Bienvenido al sistema de parqueadero de autos de la Espe.\n\n"
                "El programa permite registrar nuevos autos en el parqueadero.\n"
                "A continuacion se describen las opciones de los menus:\n\n"
                "1. Ver parqueadero\n"
                "Aqui se visualizan los lugares libres y ocupados de los autos.\n"
                "\n"
                "2. Ingresar vehiculo\n"
                "   - Ingresar Placa: Se ingresa la placa del vehiculo.\n"
                "   - Ingresar Cedula: Se agrega la cedula del chofer.\n"
                "   - Ingresar Primer Nombre: Ingresa el primer nombre del chofer.\n"
                "   - Ingresar Segundo Nombre: Ingresa el segundo nombre del chofer.\n"
                "   - Ingresar Primer Apellido: Ingresa el primer apellido del chofer.\n"
                "   - Ingresar Segundo Apellido: Ingresa el segundo apellido del chofer.\n"      
                "\n"
                "3. Retirar vehiculo\n"
                "   -Ingrese el numero del puesto a liberar: Se coloca el numero del puesto del parqueadero.\n"
                "\n"
                "4. Ver datos\n"
                "Nos aparecen todos los datos del chofer con la placa del vehiculo, ademas de la hora de ingreso y salida.\n"
                "\n"
                "5. Ver vehiculos\n"
                "Aqui aparecen las placas del vehiculo y aquien pertenece el vehiculo.\n"
                "\n"
                "6. Ver historial\n"
                "Se indica el puesto, placa, la hora de ingreso y el estado del vechiculo.\n"
                "\n"
                "7. Salir\n"
                "Termina la ejecuci�n del programa"
                "Si requiere mas ayuda, por favor comuniquese con los desarrolladores.";

            // Convertir el texto en l�neas
            std::vector<std::string> lineas;
            std::istringstream stream(instrucciones);
            std::string linea;
            while (std::getline(stream, linea)) {
                lineas.push_back(linea);
            }

            // Pintar el texto dentro del �rea visible
            int yPos = 10 - offsetY; // Modificar la posici�n en Y seg�n el desplazamiento

            for (const std::string& linea : lineas) {
                // Si el texto llega al borde inferior, detener la pintura
                if (yPos > rect.bottom) {
                    break;
                }

                TextOut(hdc, 10, yPos, linea.c_str(), linea.length());
                yPos += 20; // Espaciado entre l�neas
            }

            EndPaint(hwnd, &ps);
            break;
        }
        case WM_VSCROLL: {
            SCROLLINFO si;
            si.cbSize = sizeof(SCROLLINFO);
            si.fMask = SIF_ALL;
            GetScrollInfo(hwnd, SB_VERT, &si);

            int nPos = si.nPos;

            // Desplazamiento en funci�n de la acci�n del usuario
            switch (LOWORD(wParam)) {
                case SB_LINEUP: // Desplazar hacia arriba una l�nea
                    if (nPos > 0) {
                        nPos--;
                    }
                    break;
                case SB_LINEDOWN: // Desplazar hacia abajo una l�nea
                    if (nPos < si.nMax) {
                        nPos++;
                    }
                    break;
                case SB_PAGEUP: // Desplazar hacia arriba una p�gina
                    if (nPos > 0) {
                        nPos -= 10;  // Ajustar el tama�o del desplazamiento
                    }
                    break;
                case SB_PAGEDOWN: // Desplazar hacia abajo una p�gina
                    if (nPos < si.nMax) {
                        nPos += 10;  // Ajustar el tama�o del desplazamiento
                    }
                    break;
                case SB_THUMBTRACK: // Desplazamiento manual del thumb
                    nPos = si.nTrackPos;
                    break;
            }

            // Actualizar la posici�n de la barra de desplazamiento
            SetScrollPos(hwnd, SB_VERT, nPos, TRUE);

            // Calcular el desplazamiento en el texto
            offsetY = nPos * 20;  // Multiplicar por el tama�o de la l�nea (20 px por l�nea)

            InvalidateRect(hwnd, NULL, TRUE);  // Forzar redibujado
            break;
        }
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void Manual::mostrar() {
    const char* className = "Ayuda";

    if (!claseRegistrada) {
        WNDCLASS wc = {0};
        wc.lpfnWndProc = WindowProcedure; // Funci�n de manejo de eventos
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = className;

        if (!RegisterClass(&wc)) {
            MessageBox(NULL, "Error al registrar ", "Error", MB_OK | MB_ICONERROR);
            return;
        }
        claseRegistrada = true;
    }

    // Crear la ventana con barra de desplazamiento
    HWND hwnd = CreateWindowEx(
        0,                          // Estilo extendido
        className,                  // Nombre de la clase
        "Ayuda - Instrucciones",    // T�tulo de la ventana
        WS_OVERLAPPEDWINDOW | WS_VSCROLL,  // Barra de desplazamiento habilitada
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 400, // Posici�n y tama�o inicial
        NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Error al crear el manual", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    // Agregar la barra de desplazamiento
    SCROLLINFO si = {0};
    si.cbSize = sizeof(SCROLLINFO);
    si.fMask = SIF_PAGE | SIF_RANGE;
    si.nMin = 0;
    si.nMax = 100;  // Ajustar el rango seg�n el tama�o del contenido
    si.nPage = 10;  // Ajustar la p�gina (cantidad de texto visible)
    SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)){
    	TranslateMessage(&msg);
    	DispatchMessage(&msg);
	}
}
