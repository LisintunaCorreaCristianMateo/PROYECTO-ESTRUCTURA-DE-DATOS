#include <windows.h>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <sstream>

#define ID_BUTTON_CHECK 1
#define ID_BUTTON_DIMENSION 2
#define ID_EDIT_DIMENSION 3

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CreateGrid(HWND hwnd, int dimension);
bool IsMagicCube(const std::vector<int>& numbers, int dimension);

std::vector<HWND> editControls;
HWND hwndDimensionInput;
int dimension = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)  {
    const wchar_t CLASS_NAME[] = L"Magic Cube Window Class";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Magic Cube Game",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
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
        hwndDimensionInput = CreateWindowExW(
            0, L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
            150, 50, 200, 30,
            hwnd, (HMENU)ID_EDIT_DIMENSION,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            nullptr
        );

        HWND hwndDimensionButton = CreateWindowW(
            L"BUTTON",
            L"Set Dimension",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            150, 100, 200, 30,
            hwnd, (HMENU)ID_BUTTON_DIMENSION,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            nullptr
        );
    }
                  return 0;

    case WM_COMMAND: {
        if (LOWORD(wParam) == ID_BUTTON_DIMENSION) {
            wchar_t buffer[10];
            GetWindowTextW(hwndDimensionInput, buffer, 10);
            dimension = _wtoi(buffer);

            if (dimension >= 3) {
                ShowWindow(hwndDimensionInput, SW_HIDE);
                ShowWindow(GetDlgItem(hwnd, ID_BUTTON_DIMENSION), SW_HIDE);
                CreateGrid(hwnd, dimension);

                HWND hwndButton = CreateWindowW(
                    L"BUTTON",
                    L"Check Magic Cube",
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    150, 300 + (dimension > 4 ? (dimension - 4) * 40 : 0), 200, 30,
                    hwnd, (HMENU)ID_BUTTON_CHECK,
                    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                    nullptr
                );
            }
            else {
                MessageBoxW(hwnd, L"Please enter a dimension of 3 or greater.", L"Invalid Dimension", MB_OK | MB_ICONERROR);
            }
        }
        else if (LOWORD(wParam) == ID_BUTTON_CHECK) {
            std::vector<int> numbers;
            for (HWND editControl : editControls) {
                wchar_t buffer[10];
                GetWindowTextW(editControl, buffer, 10);
                int number = _wtoi(buffer);
                numbers.push_back(number);
            }

            if (IsMagicCube(numbers, dimension)) {
                MessageBoxW(hwnd, L"Congratulations! It's a magic cube.", L"Success", MB_OK | MB_ICONINFORMATION);
            }
            else {
                MessageBoxW(hwnd, L"Sorry, it's not a magic cube.", L"Try Again", MB_OK | MB_ICONERROR);
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

void CreateGrid(HWND hwnd, int dimension) {
    int startX = 50, startY = 150, size = 40, padding = 10;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            HWND hwndEdit = CreateWindowExW(
                0, L"EDIT", L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                startX + j * (size + padding),
                startY + i * (size + padding),
                size, size,
                hwnd,
                nullptr,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                nullptr
            );
            editControls.push_back(hwndEdit);
        }
    }
}

bool IsMagicCube(const std::vector<int>& numbers, int dimension) {
    int n = dimension;
    int magicSum = 0;
    

    for (int i = 0; i < dimension; i++) {
        magicSum += numbers[i];
    }
    std::wstringstream results;
    results << L"El resultado esperado de la suma magica es: " << magicSum << L"\n\n";
    

    for (int i = 0; i < dimension; i++) {
        int rowSum = 0;
        for (int j = 0; j < dimension; j++) {
            rowSum += numbers[i * dimension + j];
        }
        results << L"Suma de la fila " << i + 1 << L": " << rowSum << L"\n";
    }
    results << L"\n";

    for (int j = 0; j < dimension; j++) {
        int colSum = 0;
        for (int i = 0; i < dimension; i++) {
            colSum += numbers[i * dimension + j];
        }
        results << L"Suma de la columna " << j + 1 << L": " << colSum << L"\n";
    }
    results << L"\n";

    int diag1Sum = 0, diag2Sum = 0;
    for (int i = 0; i < dimension; i++) {
        diag1Sum += numbers[i * dimension + i];
        diag2Sum += numbers[i * dimension + (dimension - i - 1)];
    }
    results << L"Suma de la primera diagonal: " << diag1Sum << L"\n";
    results << L"Suma de la segunda diagonal: " << diag2Sum << L"\n\n";

    MessageBoxW(NULL, results.str().c_str(), L"Resultados de las sumas", MB_OK | MB_ICONINFORMATION);

    if (diag1Sum != magicSum || diag2Sum != magicSum) return false;
    for (int i = 0; i < dimension; i++) {
        int rowSum = 0, colSum = 0;
        for (int j = 0; j < dimension; j++) {
            rowSum += numbers[i * dimension + j];
            colSum += numbers[j * dimension + i];
        }
        if (rowSum != magicSum || colSum != magicSum) return false;
    }
    return true;
}

