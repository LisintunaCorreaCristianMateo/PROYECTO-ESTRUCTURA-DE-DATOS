#pragma once

#include <string>
#include <cstring>

using namespace std;

class Validation {
public:
    char ingresarChar(const char* msj);
    int ingresarInt(const char* msj);
    float ingresarFloat(const char* msj);
    double ingresarDouble(const char* msj);
    string ingresarString(const char* msj);
    string ingresarStringConEspacios(const char* msj);
};


