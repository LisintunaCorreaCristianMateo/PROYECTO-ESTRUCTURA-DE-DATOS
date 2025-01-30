#ifndef NODOVEHICULO_H
#define NODOVEHICULO_H

#include <iostream>
#include <string>
using namespace std;

class NodoVehiculo {
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

    NodoVehiculo* izquierda;
    NodoVehiculo* derecha;

public:
    NodoVehiculo(int _puesto, string _placa, string _cedula, string _nombre, string _segundoNombre, string _apellido, string _segundoApellido, string _fecha, string _horaIngreso);
    void setOcupado(bool estado);
    int getPuesto();
    bool isOcupado();
    string getPlaca();
    string getCedula();
    string getNombre();
    string getSegundoNombre();
    string getApellido();
    string getSegundoApellido();
    string getFecha();
    string getHoraIngreso();
    NodoVehiculo* getIzquierda();
    NodoVehiculo* getDerecha();
    
    void setPuesto(int _puesto);
    void setPlaca(string _placa);
    void setCedula(string _cedula);
    void setNombre(string _nombre);
    void setSegundoNombre(string _segundoNombre);
    void setApellido(string _apellido);
    void setSegundoApellido(string _segundoApellido);
    void setFecha(string _fecha);
    void setHoraIngreso(string _horaIngreso);
    void setIzquierda(NodoVehiculo* nodo);
    void setDerecha(NodoVehiculo* nodo);
    

};

#endif
