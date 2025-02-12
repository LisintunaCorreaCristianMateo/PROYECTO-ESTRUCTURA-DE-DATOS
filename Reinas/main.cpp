#define _WIN32_WINNT 0x0601
#include <windows.h>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <iostream>
#include <algorithm>

using namespace std;

#define CELL_SIZE 80
#define QUEEN_RADIUS 30

// Variables globales
HINSTANCE hInst;
HWND hwnd;
HBITMAP hbmKnightBlack, hbmKnightWhite, hbmQueen;  // Imágenes del caballo y la reina
POINT knightPos = { -1, -1 };  // Posición del caballo (si se usa)
vector<POINT> queens;         // Posiciones de las reinas
vector<POINT> knightMoves;    // Movimientos válidos del caballo
int BOARD_SIZE = 0;           // Tamaño del tablero (definido en tiempo de ejecución)
ofstream logFile;             // Archivo de log
bool isAutoMode = false;      // Modo automático o manual
unsigned long long processCounter = 0;  // Contador de procesos (llamadas recursivas)

// Declaración de funciones (funciones gráficas y de lógica de N reinas)
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawBoard(HDC hdc);
void DrawQueens(HDC hdc);
void DrawKnightMoves(HDC hdc);
void DrawKnight(HDC hdc, int x, int y, bool isWhiteSquare);
void DrawQueen(HDC hdc, int x, int y, bool isWhiteSquare);
void FindKnightMoves(int x, int y);
bool IsMoveValid(int x, int y);
bool CheckQueens();
void ResetBoard();
bool SolveNQueens(int row);
void LogProcess(const string& message);
void StartAutoMode();
void StartManualMode();

// Declaración de funciones para el nuevo menú con flechas
void cambiarColor(int color);
void mostrarMenu(int opcionSeleccionada, const string opciones[], int numOpciones);
void procesarSeleccion(const string& opcion);
void menu();

// Función del hilo para el menú en consola (nuevo estilo)
DWORD __stdcall ConsoleMenuThread(LPVOID lpParam) {
    menu();
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    hInst = hInstance;
    // Registro de la clase de ventana
    WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
    wcex.style         = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc   = WndProc;
    wcex.hInstance     = hInstance;
    wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszClassName = TEXT("NQueensClass");

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL, TEXT("Fallo al registrar la clase de ventana"), TEXT("Error"), MB_OK);
        return 1;
    }

    // Creación de la ventana (tamaño inicial pequeño para el menú)
    hwnd = CreateWindow(
        TEXT("NQueensClass"), TEXT("N Queens"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        400, 300,
        NULL, NULL, hInstance, NULL
    );
    if (!hwnd) {
        MessageBox(NULL, TEXT("Fallo al crear la ventana"), TEXT("Error"), MB_OK);
        return 1;
    }

    // Cargar imágenes y verificar que se hayan cargado correctamente
    hbmKnightBlack = (HBITMAP)LoadImage(NULL, TEXT("resources/caballoNegro.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (!hbmKnightBlack) {
        MessageBox(hwnd, TEXT("Error al cargar 'resources/caballoNegro.bmp'"), TEXT("Error"), MB_OK);
    }
    hbmKnightWhite = (HBITMAP)LoadImage(NULL, TEXT("resources/caballoBlanco.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (!hbmKnightWhite) {
        MessageBox(hwnd, TEXT("Error al cargar 'resources/caballoBlanco.bmp'"), TEXT("Error"), MB_OK);
    }
    hbmQueen = (HBITMAP)LoadImage(NULL, TEXT("resources/Reinas.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (!hbmQueen) {
        MessageBox(hwnd, TEXT("Error al cargar 'resources/Reinas.bmp'"), TEXT("Error"), MB_OK);
    }

    // Abrir archivo de log
    logFile.open("log.txt");

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Crear el hilo para el menú en consola (nuevo estilo con flechas)
    CreateThread(NULL, 0, ConsoleMenuThread, NULL, 0, NULL);

    // Bucle de mensajes (PeekMessage para no bloquear)
    MSG msg;
    while (true) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        Sleep(1);
    }

    // Liberar recursos
    DeleteObject(hbmKnightBlack);
    DeleteObject(hbmKnightWhite);
    DeleteObject(hbmQueen);
    logFile.close();

    return (int)msg.wParam;
}

// Función que resuelve el problema de las N reinas mediante backtracking
bool SolveNQueens(int row) {
    processCounter++;
    if (row == BOARD_SIZE) {
        if (CheckQueens()) {
            LogProcess("SOLUCIÓN ENCONTRADA:");
            for (const auto& queen : queens) {
                LogProcess("Queen at (" + to_string(queen.x) + ", " + to_string(queen.y) + ")");
            }
            LogProcess("Total processes: " + to_string(processCounter));
            MessageBox(hwnd, TEXT("Solución encontrada"), TEXT("Éxito"), MB_OK);
            return true;
        }
        return false;
    }
    for (int col = 0; col < BOARD_SIZE; ++col) {
        LogProcess("Placing queen at (" + to_string(col) + ", " + to_string(row) + ")");
        POINT newQueen = { col, row };
        queens.push_back(newQueen);
        if (CheckQueens()) {
            if (SolveNQueens(row + 1)) {
                return true;
            }
        }
        LogProcess("Backtracking: Removing queen from (" + to_string(col) + ", " + to_string(row) + ")");
        queens.pop_back();
    }
    return false;
}

// Procedimiento de la ventana
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch(message) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            DrawBoard(hdc);
            DrawQueens(hdc);
            // Se dibuja el caballo y sus movimientos (si se usan)
            if (knightPos.x != -1 && knightPos.y != -1) {
                bool isWhiteSquare = ((knightPos.x + knightPos.y) % 2 == 0);
                DrawKnight(hdc, knightPos.x, knightPos.y, isWhiteSquare);
                DrawKnightMoves(hdc);
            }
            EndPaint(hwnd, &ps);
            break;
        }
        case WM_LBUTTONDOWN: {
            if (BOARD_SIZE != 0) {
                if (isAutoMode) {
                    MessageBox(hwnd, TEXT("Modo automático en ejecución."), TEXT("Aviso"), MB_OK);
                } else {
                    // Modo manual: se coloca o retira la reina al hacer clic
                    int xPos = LOWORD(lParam) / CELL_SIZE;
                    int yPos = HIWORD(lParam) / CELL_SIZE;
                    if (xPos < BOARD_SIZE && yPos < BOARD_SIZE) {
                        auto it = find_if(queens.begin(), queens.end(), [xPos, yPos](const POINT &p) {
                            return (p.x == xPos && p.y == yPos);
                        });
                        if (it != queens.end()) {
                            queens.erase(it);
                        } else {
                            POINT newQueen = { xPos, yPos };
                            queens.push_back(newQueen);
                            // Verificar inmediatamente si se colocó de forma incorrecta
                            if (!CheckQueens()) {
                                MessageBox(hwnd, TEXT("Ayy, lo siento, está mal"), TEXT("Error"), MB_OK);
                                queens.pop_back(); // Remover la reina inválida
                            }
                        }
                        InvalidateRect(hwnd, NULL, TRUE);
                        cout << "Reinas colocadas: " << queens.size() << endl;
                        // Si se retiran o añaden, no se espera a que se complete BOARD_SIZE
                    }
                }
            } else {
                MessageBox(hwnd, TEXT("Modo no iniciado."), TEXT("Aviso"), MB_OK);
            }
            break;
        }
        case WM_RBUTTONDOWN: {
            // Clic derecho para el caballo (solo en modo manual)
            if (BOARD_SIZE != 0 && !isAutoMode) {
                int xPos = LOWORD(lParam) / CELL_SIZE;
                int yPos = HIWORD(lParam) / CELL_SIZE;
                if (xPos < BOARD_SIZE && yPos < BOARD_SIZE) {
                    knightPos.x = xPos;
                    knightPos.y = yPos;
                    knightMoves.clear();
                    FindKnightMoves(xPos, yPos);
                    InvalidateRect(hwnd, NULL, TRUE);
                    TCHAR msg[64];
                    wsprintf(msg, TEXT("Movimientos posibles: %d"), (int)knightMoves.size());
                    MessageBox(hwnd, msg, TEXT("Caballo"), MB_OK);
                }
            } else {
                MessageBox(hwnd, TEXT("Modo Manual no iniciado."), TEXT("Aviso"), MB_OK);
            }
            break;
        }
        case WM_KEYDOWN: {
            if (wParam == 'N') {
                BOARD_SIZE = 0;
                ResetBoard();
                SetWindowPos(hwnd, NULL, 0, 0, 400, 300, SWP_NOMOVE | SWP_NOZORDER);
                InvalidateRect(hwnd, NULL, TRUE);
            }
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

// Funciones de dibujo
void DrawBoard(HDC hdc) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            RECT rect = { i * CELL_SIZE, j * CELL_SIZE, (i + 1) * CELL_SIZE, (j + 1) * CELL_SIZE };
            HBRUSH brush = CreateSolidBrush(((i + j) % 2 == 0) ? RGB(255, 255, 255) : RGB(0, 0, 0));
            FillRect(hdc, &rect, brush);
            DeleteObject(brush);
        }
    }
}

void DrawQueens(HDC hdc) {
    for (const auto& queen : queens) {
        DrawQueen(hdc, queen.x, queen.y, ((queen.x + queen.y) % 2 == 0));
    }
}

void DrawKnightMoves(HDC hdc) {
    for (const auto& move : knightMoves) {
        int centerX = move.x * CELL_SIZE + CELL_SIZE / 2;
        int centerY = move.y * CELL_SIZE + CELL_SIZE / 2;
        HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));  // Azul para los movimientos del caballo
        SelectObject(hdc, brush);
        Ellipse(hdc, centerX - QUEEN_RADIUS, centerY - QUEEN_RADIUS,
                centerX + QUEEN_RADIUS, centerY + QUEEN_RADIUS);
        DeleteObject(brush);
    }
}

void DrawKnight(HDC hdc, int x, int y, bool isWhiteSquare) {
    HDC hdcMem = CreateCompatibleDC(hdc);
    HBITMAP hbmOld;
    if (isWhiteSquare)
        hbmOld = (HBITMAP)SelectObject(hdcMem, hbmKnightWhite);
    else
        hbmOld = (HBITMAP)SelectObject(hdcMem, hbmKnightBlack);
    int startX = x * CELL_SIZE;
    int startY = y * CELL_SIZE;
    BITMAP bm;
    GetObject(hbmKnightWhite, sizeof(bm), &bm);
    BitBlt(hdc, startX, startY, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
    SelectObject(hdcMem, hbmOld);
    DeleteDC(hdcMem);
}

void DrawQueen(HDC hdc, int x, int y, bool isWhiteSquare) {
    HDC hdcMem = CreateCompatibleDC(hdc);
    HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmQueen);
    int startX = x * CELL_SIZE;
    int startY = y * CELL_SIZE;
    BITMAP bm;
    GetObject(hbmQueen, sizeof(bm), &bm);
    BitBlt(hdc, startX, startY, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
    SelectObject(hdcMem, hbmOld);
    DeleteDC(hdcMem);
}

void FindKnightMoves(int x, int y) {
    static int dx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    static int dy[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    for (int i = 0; i < 8; ++i) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        if (IsMoveValid(newX, newY))
            knightMoves.push_back({ newX, newY });
    }
}

bool IsMoveValid(int x, int y) {
    return (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE);
}

bool CheckQueens() {
    for (size_t i = 0; i < queens.size(); ++i) {
        for (size_t j = i + 1; j < queens.size(); ++j) {
            if (queens[i].x == queens[j].x ||
                queens[i].y == queens[j].y ||
                abs(queens[i].x - queens[j].x) == abs(queens[i].y - queens[j].y))
                return false;
        }
    }
    return true;
}

void ResetBoard() {
    queens.clear();
    knightPos = { -1, -1 };
    knightMoves.clear();
    InvalidateRect(hwnd, NULL, TRUE);
}

void LogProcess(const string& message) {
    logFile << message << endl;
}

// Funciones para iniciar los modos (se solicita el tamaño del tablero)
void StartAutoMode() {
    system("cls");
    cout << "=== MODO AUTOMATICO ===\nIngrese tamaño del tablero (4-12): ";
    int size;
    cin >> size;
    if (size < 4 || size > 12) {
        cout << "Tamaño inválido! Usando 8 por defecto\n";
        size = 8;
        Sleep(1000);
    }
    BOARD_SIZE = size;
    isAutoMode = true;
    RECT rc = { 0, 0, BOARD_SIZE * CELL_SIZE, BOARD_SIZE * CELL_SIZE };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    SetWindowPos(hwnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
                 SWP_NOMOVE | SWP_NOZORDER);
    ResetBoard();
    queens.clear();
    processCounter = 0;
    SolveNQueens(0);
}

void StartManualMode() {
    system("cls");
    cout << "=== MODO MANUAL ===\nIngrese tamaño del tablero (4-12): ";
    int size;
    cin >> size;
    if (size < 4 || size > 12) {
        cout << "Tamaño inválido! Usando 8 por defecto\n";
        size = 8;
        Sleep(1000);
    }
    BOARD_SIZE = size;
    isAutoMode = false;
    RECT rc = { 0, 0, BOARD_SIZE * CELL_SIZE, BOARD_SIZE * CELL_SIZE };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    SetWindowPos(hwnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
                 SWP_NOMOVE | SWP_NOZORDER);
    ResetBoard();
}

// NUEVO MENÚ CON FLECHAS (estilo plantilla)
// Cambia el color del texto en consola
void cambiarColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Muestra el menú con la opción actualmente seleccionada resaltada
void mostrarMenu(int opcionSeleccionada, const string opciones[], int numOpciones) {
    system("cls");
    cout << "=== MENÚ PRINCIPAL ===\n";
    for (int i = 0; i < numOpciones; ++i) {
        if (i == opcionSeleccionada) {
            cambiarColor(3);
            cout << " > " << opciones[i] << "\n";
            cambiarColor(7);
        } else {
            cambiarColor(7);
            cout << "   " << opciones[i] << "\n";
        }
    }
}

// Procesa la opción seleccionada del menú
void procesarSeleccion(const string& opcion) {
    if (opcion == "Modo Automático") {
        StartAutoMode();
    } else if (opcion == "Modo Manual") {
        StartManualMode();
    } else if (opcion == "Salir") {
        cout << "Saliendo del programa...\n";
    } else {
        cout << "Opción no válida.\n";
    }
    system("pause");
    system("cls");
}

// Función del menú interactivo utilizando flechas para navegar
void menu() {
    // Se asigna la consola para la interacción
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    const int numOpciones = 3;
    string opciones[numOpciones] = { "Modo Automático", "Modo Manual", "Salir" };
    int opcionSeleccionada = 0;

    while (true) {
        mostrarMenu(opcionSeleccionada, opciones, numOpciones);
        char tecla = _getch();
        if (tecla == 13) { // Enter
            system("cls");
            procesarSeleccion(opciones[opcionSeleccionada]);
            if (opciones[opcionSeleccionada] == "Salir") {
                exit(0);
            }
        } else if (tecla == -32) { // Teclas especiales
            tecla = _getch();
            if (tecla == 72) { // Flecha arriba
                opcionSeleccionada = (opcionSeleccionada - 1 + numOpciones) % numOpciones;
            } else if (tecla == 80) { // Flecha abajo
                opcionSeleccionada = (opcionSeleccionada + 1) % numOpciones;
            }
        }
    }
}
