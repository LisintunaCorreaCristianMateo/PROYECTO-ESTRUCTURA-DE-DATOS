#ifndef NODOHISTORIAl_H
#define NODOHISTORIAl_H

#include <iostream>
#include <string>
using namespace std;

class NodoHistorial {
private:
    int puesto;
    bool ocupado;
    string placa;
    string cedula;
    string nombre;
    string segundoNombre;
    string apellido;
    string segundoApellido;
    string fecha;
    string horaIngreso;
    //string horaSalida;

    NodoHistorial* izquierda;
    NodoHistorial* derecha;

public:

    NodoHistorial(int _puesto, string _placa, string _cedula, string _nombre, string _segundoNombre, string _apellido, string _segundoApellido, string _fecha, string _horaIngreso);
    int getPuesto();
    void setOcupado(bool estado);
    bool isOcupado();
    string getPlaca();
    string getCedula();
    string getNombre();
    string getSegundoNombre();
    string getApellido();
    string getSegundoApellido();
    string getFecha();
    string getHoraIngreso();
    NodoHistorial* getIzquierda();
    NodoHistorial* getDerecha();

    void setIzquierda(NodoHistorial* nodo);
    void setDerecha(NodoHistorial* nodo);
    
};


#endif
