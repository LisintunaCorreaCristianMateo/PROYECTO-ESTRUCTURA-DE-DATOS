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

std::vector<HWND> editControls;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Magic Triangle Window Class";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Magic Triangle Game",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 400,
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

            int sumLeft = numbers[0] + numbers[1] + numbers[3];    // Lado izquierdo
            int sumRight = numbers[0] + numbers[2] + numbers[5];   // Lado derecho
            int sumBottom = numbers[3] + numbers[4] + numbers[5];  // Base

            std::wstringstream ss;
            ss << L"Suma lado izquierdo: " << sumLeft << L"\n";
            ss << L"Suma lado derecho: " << sumRight << L"\n";
            ss << L"Suma base: " << sumBottom << L"\n\n";

            if (IsMagicTriangle(numbers)) {
                ss << L"Felicitaciones! Es un triangulo magico.";
                MessageBox(hwnd, "Exito: Es un triangulo magico!", "Resultado", MB_OK | MB_ICONINFORMATION);
            }
            else {
                ss << L"No es un triangulo magico.\nTodos los lados deben sumar igual.";
                MessageBox(hwnd, "Error: No es un triangulo magico!", "Resultado", MB_OK | MB_ICONERROR);
            }

            // Mostrar las sumas en un mensaje separado
            char sumMessage[256];
            sprintf(sumMessage, "Suma lado izquierdo: %d\nSuma lado derecho: %d\nSuma base: %d",
                    sumLeft, sumRight, sumBottom);
            MessageBox(hwnd, sumMessage, "Sumas de los lados", MB_OK | MB_ICONINFORMATION);
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

    // Fila 1 (1 celda)
    HWND hwndEdit1 = CreateWindowExW(
        0, L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
        startX, startY, size, size,
        hwnd,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        nullptr
    );
    editControls.push_back(hwndEdit1);

    // Fila 2 (2 celdas)
    HWND hwndEdit2 = CreateWindowExW(
        0, L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
        startX - size / 2 - padding / 2, startY + size + padding, size, size,
        hwnd,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        nullptr
    );
    editControls.push_back(hwndEdit2);

    HWND hwndEdit3 = CreateWindowExW(
        0, L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
        startX + size / 2 + padding / 2, startY + size + padding, size, size,
        hwnd,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        nullptr
    );
    editControls.push_back(hwndEdit3);

    // Fila 3 (3 celdas)
    HWND hwndEdit4 = CreateWindowExW(
        0, L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
        startX - size - padding, startY + 2 * (size + padding), size, size,
        hwnd,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        nullptr
    );
    editControls.push_back(hwndEdit4);

    HWND hwndEdit5 = CreateWindowExW(
        0, L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
        startX, startY + 2 * (size + padding), size, size,
        hwnd,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        nullptr
    );
    editControls.push_back(hwndEdit5);

    HWND hwndEdit6 = CreateWindowExW(
        0, L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
        startX + size + padding, startY + 2 * (size + padding), size, size,
        hwnd,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        nullptr
    );
    editControls.push_back(hwndEdit6);
}

bool IsMagicTriangle(const std::vector<int>& numbers) {
    if (numbers.size() != 6) return false;

    // Calcular las sumas de los tres lados
    int sumLeft = numbers[0] + numbers[1] + numbers[3];    // Lado izquierdo
    int sumRight = numbers[0] + numbers[2] + numbers[5];   // Lado derecho
    int sumBottom = numbers[3] + numbers[4] + numbers[5];  // Base

    // Verificar que todos los lados sumen igual
    return (sumLeft == sumRight && sumRight == sumBottom && sumLeft > 0);
}
