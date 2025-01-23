#include <iostream>
#include "Coche.h"
#include "Menu.h"
#include "Propietario.h"
#include "ValidacionPlaca.h"
#include "Validaciones.h"
#include <string> 
#include <vector>
#include <cstdlib>

using namespace std;

Coche::Coche()
{
    this->placa = "";
    this->marca = "";
    this->modelo = "";
    this->color = "";
}

Coche::Coche(string placa, string modelo, string color, string marca, int anio)
    : placa(placa), modelo(modelo), color(color), marca(marca), anio(anio), horaIngreso(chrono::system_clock::now()) {}

Coche::Coche(string placa, string modelo, string color, string marca,
             chrono::system_clock::time_point horaIngreso, chrono::system_clock::time_point horaSalida )
    : placa(placa), modelo(modelo), color(color), marca(marca), anio(0), horaIngreso(horaIngreso), horaSalida(horaSalida) {}


void Coche::setHoraSalida(chrono::system_clock::time_point hora)
{
    horaSalida = hora;
}

void Coche::setPlaca(const string &placa)
{
    this->placa = placa;
}

void Coche::setModelo(const string &modelo)
{
    this->modelo = modelo;
}

void Coche::setMarca(const string &marca)
{
    this->marca = marca;
}

void Coche::setColor(const string &color)
{
    this->color = color;
}

chrono::system_clock::time_point Coche::getHoraSalida() const
{
    return horaSalida;
}

string Coche::getPlaca() const
{
    return placa;
}

string Coche::getMarca() const
{
    return marca;
}

string Coche::getModelo() const
{
    return modelo;
}

string Coche::getColor() const
{
    return color;
}

int Coche::getAnio() const
{
    return anio;
}

chrono::system_clock::time_point Coche::getHora() const
{
    return horaIngreso;
}



ostream &operator<<(ostream &os, const Coche &coche)
{
    os << "Placa: " << coche.placa << "\nMarca: " << coche.marca
       << "\nModelo: " << coche.modelo << "\nColor: " << coche.color
       << "\n----------------------------------------" << endl;

    time_t tiempoIngreso = chrono::system_clock::to_time_t(coche.horaIngreso);
    os << "\nHora de Ingreso: " << ctime(&tiempoIngreso)
       << "\n----------------------------------------" << endl;

    if (coche.horaSalida == chrono::system_clock::time_point())
    {
        os << "\nHora de Salida: N/A" << endl;
    }
    else
    {
        time_t tiempoSalida = chrono::system_clock::to_time_t(coche.horaSalida);
        os << "\nHora de Salida: " << ctime(&tiempoSalida)
           << "\n----------------------------------------" << endl;
    }

    return os;
}


Coche Coche::InsertarDatos(BST<Coche> &arbol, BST<Coche> &arbolHistorial, BST<Propietario> &arbolPropietarios)
{
    Validaciones validaciones;
    Placa<Coche> validador;

    string placa, modelo, color, marca, cedula;
    int anio = 0;

    BSTNode<Propietario>* propietarioNodo = nullptr;
    bool propietarioEncontrado = false;

    while (!propietarioEncontrado)
    {
        cedula = validaciones.ingresarCedula("Ingrese el numero de cedula del propietario: ");
        propietarioNodo = arbolPropietarios.buscar(cedula);

        if (propietarioNodo != nullptr) {
            propietarioEncontrado = true;
        } else {
            cout << "No se encontro un propietario con esa cedula. Por favor, intente de nuevo." << endl;
        }
    }

    while (true)
    {
        placa = validador.ingresarPlaca(arbol.buscar(placa));

        BSTNode<Coche>* temp = arbol.buscar(placa);
        bool placaDuplicada = false;

        if (temp != nullptr && temp->getData().getHoraSalida() == chrono::system_clock::time_point())
        {
            cout << "\nEl coche con la placa " << placa << " ya esta en el parqueadero. Ingrese una placa nueva." << endl;
            placaDuplicada = true;
        }

        if (!placaDuplicada)
        {
            break;
        }
    }

    BSTNode<Coche>* tempHistorial = arbolHistorial.buscar(placa);
    if (tempHistorial != nullptr)
    {
        cout << "\nLa placa " << placa << " fue encontrada en el historial. Recuperando datos..." << endl;
        modelo = tempHistorial->getData().getModelo();
        color = tempHistorial->getData().getColor();
        marca = tempHistorial->getData().getMarca();

        cout << "Marca: " << marca << "\nColor: " << color << "\nModelo: " << modelo << "\n";

        vector<string> opciones = {"Si", "No"};
        int seleccion = menuInteractivo(opciones, "Auto encontrado en el sistema.\n¿Desea sobreescribir los datos del historial?");

        if (seleccion == 0)
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "        Datos Recuperados Exitosamente  " << endl;
            cout << "========================================" << endl;
            cout << "\nMarca:    " << marca << endl;
            cout << "Modelo:   " << modelo << endl;
            cout << "Color:    " << color << endl;
            cout << "Placa:    " << placa << endl;

            Propietario propietarioActualizado(propietarioNodo->getData().getNombre(),
                                               propietarioNodo->getData().getApellido(),
                                               propietarioNodo->getData().getCedula(),
                                               propietarioNodo->getData().getCorreo(),
                                               propietarioNodo->getData().getPlacas());
            propietarioActualizado.agregarPlaca(placa);

            propietarioNodo->getData() = propietarioActualizado;

            arbolPropietarios.insertar(propietarioActualizado);

            return Coche(placa, modelo, color, marca, anio);
        }
        else
        {
            system("cls");
            cout << "\nPor favor, ingrese los datos manualmente:" << endl;
        }
    }

    marca = validaciones.ingresarString("Ingrese la marca: ");
    color = validaciones.ingresarString("Ingrese el color: ");
    modelo = validaciones.ingresarString("Ingrese el modelo: ");

    Propietario propietarioActualizado(propietarioNodo->getData().getNombre(),
                                       propietarioNodo->getData().getApellido(),
                                       propietarioNodo->getData().getCedula(),
                                       propietarioNodo->getData().getCorreo(),
                                       propietarioNodo->getData().getPlacas());
    propietarioActualizado.agregarPlaca(placa);

    propietarioNodo->getData() = propietarioActualizado;

    arbolPropietarios.insertar(propietarioActualizado);

    return Coche(placa, modelo, color, marca, anio);
}
#include "BSTNode.cpp"