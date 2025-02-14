#include "Closed_Hash.h"
#include "Node.h"
#include <sstream>
#include <iomanip>
template <typename T>
Closed_Hash<T>::Closed_Hash(int size, int method) : size(size), method(method) {
    table.resize(size, T(-1, "")); // Inicializar con objetos Node inválidos
    occupied.resize(size, false);
}

template <typename T>
int Closed_Hash<T>::primaryHash(T key) {
    return std::hash<int>{}(key.getIndex()) % size;
}

template <typename T>
int Closed_Hash<T>::secondaryHash(T key) {
    return 7 - (std::hash<int>{}(key.getIndex()) % 7);
}

template <typename T>
int Closed_Hash<T>::probe(int index, int attempt, T key) {
    if (method == 0) {
        return (index + attempt) % size;
    } else if (method == 1) {
        return (index + attempt * attempt) % size;
    } else if (method == 2) {
        return (index + attempt * secondaryHash(key)) % size;
    }
    return index;
}

template <typename T>
void Closed_Hash<T>::insert(T key) {
    int index = primaryHash(key);
    int attempt = 0;

    while (occupied[index]) {
        attempt++;
        index = probe(primaryHash(key), attempt, key);
        if (attempt >= size) {
            std::cout << "Error: Tabla llena, no se puede insertar " << key.getWord() << std::endl;
            return;
        }
    }

    table[index] = key;
    occupied[index] = true;
}

template <typename T>
void Closed_Hash<T>::display() {
    const int columns = 6;
    const int cellWidth = 20;
    const int recuadroWidth = 12;  // "[" + campo de 10 caracteres + "]"

    // Códigos ANSI para color celeste (índices) y reset
    const std::string colorIndex = "\033[1;36m"; // Celeste
    const std::string resetColor = "\033[0m";

    // Calcula el ancho total de la línea horizontal (considerando 3 espacios entre celdas)
    int totalWidth = columns * cellWidth + (columns - 1) * 3;
    std::string horizontalLine(totalWidth, '-');

    std::cout << "\n" << horizontalLine << std::endl;

    int rows = (size + columns - 1) / columns;

    for (int r = 0; r < rows; r++) {
        // Primera línea: recuadro con la palabra centrada
        for (int c = 0; c < columns; c++) {
            int index = r * columns + c;
            std::string cellStr;
            if (index < size) {
                std::ostringstream cell;
                int fieldWidth = 10; // Ancho del área para la palabra (se declara aquí para ambos casos)
                if (occupied[index]) {
                    std::string word = table[index].getWord();
                    int leftPadWord = (fieldWidth - static_cast<int>(word.size())) / 2;
                    int rightPadWord = fieldWidth - static_cast<int>(word.size()) - leftPadWord;
                    cell << "["
                         << std::string(leftPadWord, ' ')
                         << word
                         << std::string(rightPadWord, ' ')
                         << "]";
                } else {
                    std::string blank(fieldWidth, ' ');
                    cell << "[" << blank << "]";
                }
                cellStr = cell.str();
            } else {
                cellStr = "";
            }
            // Centra el recuadro en la celda (con cellWidth = 20 y recuadroWidth = 12, quedan 4 espacios a la izquierda)
            int leftPadding = (cellWidth - recuadroWidth) / 2;
            std::cout << std::string(leftPadding, ' ')
                      << cellStr
                      << std::string(cellWidth - leftPadding - recuadroWidth, ' ');
            if (c < columns - 1)
                std::cout << "   "; // separación entre celdas
        }
        std::cout << std::endl;

        // Segunda línea: muestra el índice centrado respecto al recuadro, en color celeste
        for (int c = 0; c < columns; c++) {
            int index = r * columns + c;
            std::string indexStr = (index < size) ? std::to_string(index) : "";
            int leftPadding = (cellWidth - recuadroWidth) / 2;
            std::cout << std::string(leftPadding, ' ');
            // Centra el índice dentro del recuadro
            int indexLeftPadding = (recuadroWidth - static_cast<int>(indexStr.size())) / 2;
            std::cout << std::string(indexLeftPadding, ' ');
            if (!indexStr.empty())
                std::cout << colorIndex << indexStr << resetColor;
            else
                std::cout << "";
            std::cout << std::string(recuadroWidth - indexLeftPadding - static_cast<int>(indexStr.size()), ' ');
            int remaining = cellWidth - leftPadding - recuadroWidth;
            std::cout << std::string(remaining, ' ');
            if (c < columns - 1)
                std::cout << "   ";
        }
        std::cout << std::endl;
        // Línea en blanco extra para separar filas
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    }
    std::cout << horizontalLine << std::endl;
}

template<typename T>
int Closed_Hash<T>::convert_string_to_int(std::string cad) {
    size_t hashValue = 0;
    for (auto it = cad.rbegin(); it != cad.rend(); ++it) {
        size_t temp = static_cast<size_t>(*it);
        temp = (temp + hashValue);
        if (it + 1 != cad.rend()) {
            temp = (temp << 4);
            hashValue = temp;
        } else {
            hashValue = temp;
        }
    }
    return static_cast<int>(hashValue);
}

// Instanciación explícita para evitar problemas con templates en archivos separados
template class Closed_Hash<Node>;
