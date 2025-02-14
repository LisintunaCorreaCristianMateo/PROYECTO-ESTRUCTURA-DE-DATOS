#include "Menu.h"
#include <iostream>
#include <conio.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <functional>
#include "Validation.h"
#include "Closed_Hash.h"
using namespace std;
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#undef byte
#define CLEAR() system("cls")
#else
#include <cstdlib>
#define CLEAR() system("clear")
#endif

Menu::Menu() : selectedIndex(0), title("") {}

void Menu::addOption(const string &option)
{
    options.push_back(option);
}

void Menu::addTitle(const string &title)
{
    this->title = title;
}

void Menu::displayMenu()
{
    bool running = true;

    while (running)
    {
        CLEAR();
        if (!title.empty())
        {
            cout << title << "\n";
        }
        cout << "\n";
        for (size_t i = 0; i < options.size(); ++i)
        {
            if (static_cast<int>(i) == selectedIndex)
            {
                cout << "==> " << options[i] << " \n";
            }
            else
            {
                cout << "  " << options[i] << "\n";
            }
        }
        int key = _getch();
        switch (key)
        {
        case 72: // Flecha arriba
            selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
            break;
        case 80: // Flecha abajo
            selectedIndex = (selectedIndex + 1) % options.size();
            break;
        case 13: // Enter
            running = false;
            break;
        }
    }
}

int Menu::getSelectedOption()
{
    return selectedIndex;
}
//------------------------------------------------------------------------------------------------------------------------
void Menu::principal_menu()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    bool running = true;
    Validation validation;

    // Declaración de las tablas hash para cada combinación:
    Closed_Hash<Node> hashTableLInt(29, 0);
    Closed_Hash<Node> hashTableLString(29, 0);
    Closed_Hash<Node> hashTableCInt(29, 1);
    Closed_Hash<Node> hashTableCString(29, 1);
    Closed_Hash<Node> hashTableDInt(29, 2);
    Closed_Hash<Node> hashTableDString(29, 2);

    while (running)
    {
        // MENÚ PRINCIPAL: Elección de tipo de dato
        options.clear();
        addTitle("\tElija el tipo de dato:");
        addOption("Entero");
        addOption("String");
        addOption("Salir");
        displayMenu();

        int dataTypeOption = getSelectedOption();

        if (dataTypeOption == 2) // Opción "Salir"
        {
            running = false;
            break;
        }

        // SUBMENÚ: Elección del método de hash
        bool submenuRunning = true;
        while (submenuRunning)
        {
            options.clear();
            addTitle("\tElija el método de hash:");
            addOption("Lineal");
            addOption("Cuadrático");
            addOption("Doble");
            addOption("Volver");
            displayMenu();

            int hashTypeOption = getSelectedOption();
            if (hashTypeOption == 3) // Opción "Volver" al menú principal
            {
                submenuRunning = false;
                continue;
            }

            // Procesamos según la combinación de tipo de dato y método de hash
            if (dataTypeOption == 0) // Entero
            {
                switch (hashTypeOption)
                {
                case 0:
                {
                    cout << "Hash cerrado lineal en enteros" << endl;
                    int num = validation.ingresarInt("Inserte el número:\t");
                    Node node(num, to_string(num));
                    hashTableLInt.insert(node);
                    hashTableLInt.display();
                    system("pause");
                    break;
                }
                case 1:
                {
                    cout << "Hash cerrado cuadrático en enteros" << endl;
                    int num = validation.ingresarInt("Inserte el número:\t");
                    Node node(num, to_string(num));
                    hashTableCInt.insert(node);
                    hashTableCInt.display();
                    system("pause");
                    break;
                }
                case 2:
                {
                    cout << "Hash cerrado doble en enteros" << endl;
                    int num = validation.ingresarInt("Inserte el número:\t");
                    Node node(num, to_string(num));
                    hashTableDInt.insert(node);
                    hashTableDInt.display();
                    system("pause");
                    break;
                }
                }
            }
            else if (dataTypeOption == 1) // String
            {
                switch (hashTypeOption)
                {
                case 0:
                {
                    cout << "Hash cerrado lineal en strings" << endl;
                    string palabra = validation.ingresarString("Inserte la letra o palabra:\t");
                    int num = hashTableLString.convert_string_to_int(palabra);
                    Node node(num, palabra);
                    hashTableLString.insert(node);
                    hashTableLString.display();
                    system("pause");
                    break;
                }
                case 1:
                {
                    cout << "Hash cerrado cuadrático en strings" << endl;
                    string palabra = validation.ingresarString("Inserte la letra o palabra:\t");
                    int num = hashTableCString.convert_string_to_int(palabra);
                    Node node(num, palabra);
                    hashTableCString.insert(node);
                    hashTableCString.display();
                    system("pause");
                    break;
                }
                case 2:
                {
                    cout << "Hash cerrado doble en strings" << endl;
                    string palabra = validation.ingresarString("Inserte la letra o palabra:\t");
                    int num = hashTableDString.convert_string_to_int(palabra);
                    Node node(num, palabra);
                    hashTableDString.insert(node);
                    hashTableDString.display();
                    system("pause");
                    break;
                }
                }
            }
        } // Fin del submenú
    } // Fin del menú principal
}
