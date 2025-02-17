#include <windows.h>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <sstream>

#define ID_BUTTON_CHECK 1

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CreateTriangle(HWND hwnd);
bool IsMagicTriangle(const std::vector<int>& numbers);
int GetTriangleSize();

int triangleSize = 3;  // Tamaño mínimo por defecto
std::vector<HWND> editControls;

int GetTriangleSize() {
    int size = 0;
    char buffer[256];
    
    while (size < 3) {
        // Mostrar un cuadro de diálogo simple
        if (MessageBox(NULL, 
            "Desea ingresar el tamaño del triangulo?\nPresione Si para continuar, No para usar tamaño por defecto (3)", 
            "Tamaño del Triangulo", 
            MB_YESNO | MB_ICONQUESTION) == IDYES) {
            
            // Crear un cuadro de diálogo personalizado
            HWND hwndDlg = CreateWindow(
                "EDIT", "", 
                WS_BORDER | WS_VISIBLE | ES_NUMBER,
                0, 0, 100, 20,
                NULL, NULL, NULL, NULL
            );
            
            if (hwndDlg != NULL) {
                SetFocus(hwndDlg);
                MSG msg;
                while (GetMessage(&msg, NULL, 0, 0)) {
                    if (msg.message == WM_CHAR && msg.wParam == VK_RETURN) {
                        GetWindowText(hwndDlg, buffer, sizeof(buffer));
                        size = atoi(buffer);
                        DestroyWindow(hwndDlg);
                        break;
                    }
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
            
            if (size < 3) {
                MessageBox(NULL, "El tamaño debe ser al menos 3", "Error", MB_OK | MB_ICONERROR);
            }
        } else {
            size = 3; // Usar tamaño por defecto
            break;
        }
    }
    return size;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Magic Triangle Window Class";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClassW(&wc);

    // Obtener el tamaño del triángulo antes de crear la ventana
    triangleSize = GetTriangleSize();

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Magic Triangle Game",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        400 + (triangleSize-3)*50, 400 + (triangleSize-3)*50,  // Ajustar tamaño de ventana
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (hwnd == nullptr) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        CreateTriangle(hwnd);

        HWND hwndButton = CreateWindowW(
            L"BUTTON",
            L"Check Magic Triangle",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            150, 250, 200, 30,
            hwnd, (HMENU)ID_BUTTON_CHECK,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            nullptr
        );
    }
                  return 0;

    case WM_COMMAND: {
        if (LOWORD(wParam) == ID_BUTTON_CHECK) {
            std::vector<int> numbers;
            for (HWND editControl : editControls) {
                wchar_t buffer[10];
                GetWindowTextW(editControl, buffer, 10);
                int number = _wtoi(buffer);
                numbers.push_back(number);
            }

            if (IsMagicTriangle(numbers)) {
                MessageBox(hwnd, "Exito: Es un triangulo magico!", "Resultado", MB_OK | MB_ICONINFORMATION);
            } else {
                MessageBox(hwnd, "Error: No es un triangulo magico!", "Resultado", MB_OK | MB_ICONERROR);
            }
        }
    }
    return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

void CreateTriangle(HWND hwnd) {
    int startX = 150, startY = 50, size = 40, padding = 10;
    
    // Crear casillas solo en los laterales
    for (int row = 0; row < triangleSize; row++) {
        for (int col = 0; col <= row; col++) {
            // Solo crear casillas si están en los bordes
            if (row == triangleSize - 1 || col == 0 || col == row) {
                int x = startX + (col - row/2.0) * (size + padding);
                int y = startY + row * (size + padding);
                
                HWND hwndEdit = CreateWindowExW(
                    0, L"EDIT", L"",
                    WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                    x, y, size, size,
                    hwnd,
                    nullptr,
                    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                    nullptr
                );
                editControls.push_back(hwndEdit);
            }
        }
    }
}

bool IsMagicTriangle(const std::vector<int>& numbers) {
    if (numbers.empty()) return false;
    
    int n = triangleSize; // tamaño del triángulo
    // Se espera: 1 (fila 0) + 2*(n-2) (filas intermedias) + n (última fila) = 3*n - 3 controles
    int expectedControls = (n == 1) ? 1 : (1 + 2 * (n - 2) + n);
    if (numbers.size() != expectedControls) {
        MessageBox(NULL, "Error: Número incorrecto de valores", "Error", MB_OK | MB_ICONERROR);
        return false;
    }
    
    int sumLeft = 0, sumRight = 0, sumBase = 0;
    int offset = 0; // índice inicial de cada fila en el vector "numbers"
    
    for (int row = 0; row < n; row++) {
        int rowCount = 0;
        if (row == 0) {
            rowCount = 1;          // Solo la cima
        } else if (row == n - 1) {
            rowCount = n;          // La base completa
        } else {
            rowCount = 2;          // Bordes izquierdo y derecho
        }
        
        // Sumar borde izquierdo: siempre es el primer elemento de la fila
        sumLeft += numbers[offset];
        
        // Sumar borde derecho
        if (row == 0) {
            // Para la cima, es el mismo número
            sumRight += numbers[offset];
        } else if (row == n - 1) {
            // Para la base, el borde derecho es el último elemento
            sumRight += numbers[offset + rowCount - 1];
        } else {
            // Para filas intermedias, el segundo control es el derecho
            sumRight += numbers[offset + 1];
        }
        
        // Sumar la base completa (última fila)
        if (row == n - 1) {
            for (int i = 0; i < rowCount; i++) {
                sumBase += numbers[offset + i];
            }
        }
        
        offset += rowCount; // Avanzamos al comienzo de la siguiente fila
    }
    
    // Mostrar sumas para depuración
    char debug[256];
    sprintf(debug, "Base: %d\nIzquierda: %d\nDerecha: %d", sumBase, sumLeft, sumRight);
    MessageBox(NULL, debug, "Sumas", MB_OK);
    
    return (sumLeft == sumRight && sumRight == sumBase && sumBase > 0);
}
