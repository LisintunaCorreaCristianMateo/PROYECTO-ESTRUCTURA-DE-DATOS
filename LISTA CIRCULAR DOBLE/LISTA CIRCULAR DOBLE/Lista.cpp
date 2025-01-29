#include "Propietario.h"
#include "Lista.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include "Coche.h"
#include <algorithm>
#include <cctype>
#include <regex>
#include <fstream>
#include <sstream>
#include <iomanip>
//SI METES AQUI EL MENU.H SE DAÑA TODITO 

using namespace std;
template <typename T>
ListaCircularDoble<T>::ListaCircularDoble()
{
    primero = nullptr;
    ultimo = nullptr;
}
void ListaCircularDoble<T>::insertar(T dato )
    Nodo<T> *nuevoCarro = new Nodo<T>(dato);
    if (primero == nullptr)
        primero = nuevoCarro;
        primero->setSiguiente(primero);
        primero->setAnterior(primero);
        ultimo = primero;
    else
        ultimo->setSiguiente(nuevoCarro);
        nuevoCarro->setAnterior(ultimo);
        ultimo = nuevoCarro;
void ListaCircularDoble<T>::buscarPorPlaca(string placa)
        cout << "La lista está vacia." << endl;
        return;
    Nodo<T> *aux = primero;
    do
            cout << "========================================" << endl;
            cout << "   AUTOMOVIL REGISTRADO" << endl;
            cout << aux->getDato() << endl;
        aux = aux->getSiguiente();
    } while (aux != primero);
    cout << "El coche con la placa " << placa << " no esta en el parqueadero." << endl;
void ListaCircularDoble<T>::mostrar(Nodo<T> *primero)
        std::cout << "La lista esta vacia." << std::endl;
    cout << "AUTOMOVIL REGISTRADO" << endl;
    while (aux != primero)
void ListaCircularDoble<T>::eliminarPorPlaca(string placa)
    Nodo<T> *anterior = nullptr;
    auto horaEliminacion = std::chrono::system_clock::now();
    std::time_t tiempoEliminacion = std::chrono::system_clock::to_time_t(horaEliminacion);
        delete primero;
        cout << "El coche con la placa " << placa << " ha sido eliminado." << endl;
        GuardarArchivo("autos.txt");
                primero = primero->getSiguiente();
            else if (aux == ultimo)
                ultimo = ultimo->getAnterior();
                anterior = aux->getAnterior();
                anterior->setSiguiente(aux->getSiguiente());
                aux->getSiguiente()->setAnterior(anterior);
            delete aux;
    cout << "El coche con la placa " << placa << " no se encontro en el parqueadero." << endl;
void ListaCircularDoble<T>::BusquedaAvanzada(string criterio, string valorInicio, string valorFin)
        cout << "La lista esta vacia." << endl;
        transform(valorInicio.begin(), valorInicio.end(), valorInicio.begin(), ::tolower);
    bool encontrado = false;
            string marca = aux->getDato().getMarca();
                cout << "   AUTOMOVIL REGISTRADO POR MARCA" << endl;
                encontrado = true;
            string modelo = aux->getDato().getModelo();
                cout << "   AUTOMOVIL REGISTRADO POR MODELO" << endl;
            string color = aux->getDato().getColor();
                cout << "   AUTOMOVIL REGISTRADO POR COLOR" << endl;
            chrono::system_clock::time_point horaIngreso = aux->getDato().getHora();
            time_t tiempo = chrono::system_clock::to_time_t(horaIngreso);
            tm *tm = localtime(&tiempo);
            char horaActual[9];
            strftime(horaActual, sizeof(horaActual), "%H:%M:%S", tm);
            auto estaEnIntervalo = [&valorInicio, &valorFin, &horaActual]()
                return valorInicio <= horaActual && horaActual <= valorFin;
            };
                cout << "   AUTOMOVIL REGISTRADO POR HORA" << endl;
        cout << "No se encontro ningun automovil con el criterio de busqueda: " << criterio <<endl;
void ListaCircularDoble<T>::CargarArchivo(std::string nombreArchivo)
    std::ifstream archivo(nombreArchivo);
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << ". Creando archivo vacío..." << std::endl;
        std::ofstream nuevoArchivo(nombreArchivo); 
            std::cerr << "Error: No se pudo crear el archivo " << nombreArchivo << std::endl;
        nuevoArchivo.close(); 
    std::string linea;
        std::istringstream ss(linea);
        std::string placa, modelo, color, marca, fechaIngreso, horaSalida;
            std::getline(ss, modelo, ',') &&
            placa = descifrarTexto(placa);
            std::tm tm = {};
            std::istringstream ssFecha(fechaIngreso);
            ssFecha >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
                std::cerr << "Error en el formato de la fecha de ingreso: " << fechaIngreso << std::endl;
                continue;
            auto horaIngreso = std::chrono::system_clock::from_time_t(std::mktime(&tm));
            std::chrono::system_clock::time_point horaSalidaParsed;
                horaSalidaParsed = std::chrono::system_clock::time_point();
                std::tm tmSalida = {};
                std::istringstream ssHoraSalida(horaSalida);
                ssHoraSalida >> std::get_time(&tmSalida, "%a %b %d %H:%M:%S %Y");
                    std::cerr << "Error en el formato de la hora de salida: " << horaSalida << std::endl;
                    horaSalidaParsed = std::chrono::system_clock::from_time_t(std::mktime(&tmSalida));
            T coche(placa, modelo, color, marca, horaIngreso, horaSalidaParsed);
            this->insertar(coche);
            std::cerr << "Error: Formato de línea inválido: " << linea << std::endl;
    archivo.close();
void ListaCircularDoble<T>::GuardarArchivo(std::string nombreArchivo)
    std::ofstream archivo(nombreArchivo);
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << ". Creando archivo nuevo..." << std::endl;
    std::cout << "Abriendo archivo para guardar los datos..." << std::endl;
    Nodo<T> *actual = primero;
        T coche = actual->getDato();
        std::string placaCifrada = cifrarTexto(coche.getPlaca());
        auto horaIngreso = coche.getHora();
        std::time_t horaIngresoTime = std::chrono::system_clock::to_time_t(horaIngreso);
        std::tm tmHoraIngreso = *std::localtime(&horaIngresoTime);
        auto horaSalida = coche.getHoraSalida();
        std::ostringstream horaSalidaStream;
            std::time_t horaSalidaTime = std::chrono::system_clock::to_time_t(horaSalida);
            std::tm tmHoraSalida = *std::localtime(&horaSalidaTime);
            horaSalidaStream << std::put_time(&tmHoraSalida, "%a %b %d %H:%M:%S %Y");
            horaSalidaStream << "N/A";
        archivo << placaCifrada << ","
                << coche.getModelo() << ","
                << coche.getColor() << ","
                << coche.getMarca() << ","
                << std::put_time(&tmHoraIngreso, "%a %b %d %H:%M:%S %Y") << ","
                << horaSalidaStream.str() << std::endl;
        actual = actual->getSiguiente();
string ListaCircularDoble<T>::cifrarTexto(const std::string &texto)
    std::string textoCifrado = texto;
    for (char &c : textoCifrado)
            c = ((c - '0' + 2) % 10) + '0';
    return textoCifrado;
string ListaCircularDoble<T>::descifrarTexto(const std::string &texto)
    std::string textoDescifrado = texto;
    return textoDescifrado;
bool ListaCircularDoble<T>::estaVacia() const
    return primero == nullptr;
void ListaCircularDoble<T>::salirDelParqueadero(const std::string &placa)
            auto ahora = std::chrono::system_clock::now();
            coche.setHoraSalida(ahora);
            actual->setDato(coche);
            std::cout << "El coche con placa " << placa << " ha salido del parqueadero." << std::endl;
        std::cerr << "Coche con placa " << placa << " no encontrado en el parqueadero." << std::endl;
void ListaCircularDoble<T>::GuardarPropietarios(const std::string& nombreArchivo)
    ofstream archivo(nombreArchivo);
        cerr << "No se pudo abrir el archivo para escritura: " << nombreArchivo << endl;
    Nodo<T>* actual = primero;
    do {
        archivo << actual->getDato().getNombre() << ","
                << actual->getDato().getApellido() << ","
        vector<string> placas = actual->getDato().getPlacas();
            archivo << placas[i];
                archivo << ",";
        archivo << endl;
void ListaCircularDoble<T>::CargarPropietarios(const std::string& nombreArchivo)
    ifstream archivo(nombreArchivo);
        cerr << "No se pudo abrir el archivo para lectura: " << nombreArchivo << endl;
    string linea;
        stringstream ss(linea);
        string nombre, apellido, cedula, correo, placasStr;
        getline(ss, nombre, ',');
        vector<string> placas;
        stringstream ssPlacas(placasStr);
        string placa;
            placas.push_back(placa);
        T propietario(nombre, apellido, cedula, correo);
            propietario.agregarPlaca(p);
void ListaCircularDoble<T>::BusquedaAvanzadaPropietario(string criterio, string valorInicio, string valorFin)
            string cedula = aux->getDato().getCedula();
                cout << "   PROPIETARIO REGISTRADO POR CEDULA" << endl;
            string correo = aux->getDato().getCorreo();
                cout << "   PROPIETARIO REGISTRADO POR CORREO" << endl;
            string nombre = aux->getDato().getNombre();
                cout << "   PROPIETARIO REGISTRADO POR NOMBRE" << endl;
            string apellido = aux->getDato().getApellido();
                cout << "   PROPIETARIO REGISTRADO POR APELLIDO" << endl;
        cout << "No se encontro ningun propietario con el criterio de busqueda: " << criterio << endl;
