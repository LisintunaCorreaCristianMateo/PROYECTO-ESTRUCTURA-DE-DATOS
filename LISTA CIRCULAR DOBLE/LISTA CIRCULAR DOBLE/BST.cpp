// BST.cpp
#include "BST.h"
#include "Propietario.h"
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

using namespace std;
template <typename T>
void BST<T>::insert(BSTNode<T>*& node, T data) {  // Método privado
    if (node == nullptr) {
        node = new BSTNode<T>(data);
    } else if (data.getPlaca() < node->data.getPlaca()) {
        insert(node->left, data);  // Llamada recursiva a 'insert'
    } else {
    }
void BST<T>::insertar(T data) {  // Método público
BSTNode<T>* BST<T>::buscar(BSTNode<T>* node, const std::string& key) {
        return node;
        return buscar(node->left, key);
void BST<T>::inorder(BSTNode<T>* node) {
        inorder(node->left);
        std::cout << node->data << std::endl;
void BST<T>::buscarPorPlaca(string placa)
{
    BSTNode<T>* aux = raiz;
    while (aux != nullptr)
            cout << "========================================" << endl;
            cout << "   AUTOMOVIL REGISTRADO" << endl;
            cout << aux->data << endl;
            return;
        else if (placa < aux->data.getPlaca())
            aux = aux->left;
        else
            aux = aux->right;
    cout << "El coche con la placa " << placa << " no esta en el parqueadero." << endl;
void BST<T>::mostrar(BSTNode<T>* node)
        std::cout << "El arbol esta vacio." << std::endl;
        mostrar(node->left);
    cout << "AUTOMOVIL REGISTRADO" << endl;
    cout << node->data << endl;
void BST<T>::eliminarPorPlaca(string placa)
    raiz = eliminarPorPlacaRec(raiz, placa);
BSTNode<T>* BST<T>::eliminarPorPlacaRec(BSTNode<T>* node, string placa)
        cout << "El coche con la placa " << placa << " no se encontro en el parqueadero." << endl;
        node->left = eliminarPorPlacaRec(node->left, placa);
        node->right = eliminarPorPlacaRec(node->right, placa);
            BSTNode<T>* temp = node->right;
            delete node;
            cout << "El coche con la placa " << placa << " ha sido eliminado." << endl;
            return temp;
            BSTNode<T>* temp = node->left;
        BSTNode<T>* temp = minValueNode(node->right);
        node->data = temp->data;
BSTNode<T>* BST<T>::minValueNode(BSTNode<T>* node)
    BSTNode<T>* current = node;
        current = current->left;
    return current;
void BST<T>::BusquedaAvanzada(string criterio, string valorInicio, string valorFin)
        cout << "El arbol esta vacio." << endl;
        transform(valorInicio.begin(), valorInicio.end(), valorInicio.begin(), ::tolower);
    bool encontrado = false;
    BusquedaAvanzadaRec(raiz, criterio, valorInicio, valorFin, encontrado);
        cout << "No se encontro ningun automovil con el criterio de busqueda: " << criterio << endl;
void BST<T>::BusquedaAvanzadaRec(BSTNode<T>* node, string criterio, string valorInicio, string valorFin, bool& encontrado)
        string marca = node->data.getMarca();
            cout << "   AUTOMOVIL REGISTRADO POR MARCA" << endl;
            encontrado = true;
        string modelo = node->data.getModelo();
            cout << "   AUTOMOVIL REGISTRADO POR MODELO" << endl;
        string color = node->data.getColor();
            cout << "   AUTOMOVIL REGISTRADO POR COLOR" << endl;
        chrono::system_clock::time_point horaIngreso = node->data.getHora();
        time_t tiempo = chrono::system_clock::to_time_t(horaIngreso);
        tm* tm = localtime(&tiempo);
        char horaActual[9];
        strftime(horaActual, sizeof(horaActual), "%H:%M:%S", tm);
        auto estaEnIntervalo = [&valorInicio, &valorFin, &horaActual]()
            return valorInicio <= horaActual && horaActual <= valorFin;
        };
            cout << "   AUTOMOVIL REGISTRADO POR HORA" << endl;
void BST<T>::CargarArchivo(std::string nombreArchivo)
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
void BST<T>::GuardarArchivo(std::string nombreArchivo)
    std::ofstream archivo(nombreArchivo);
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << ". Creando archivo nuevo..." << std::endl;
    std::cout << "Abriendo archivo para guardar los datos..." << std::endl;
    GuardarArchivoRec(raiz, archivo);
void BST<T>::GuardarArchivoRec(BSTNode<T>* node, std::ofstream& archivo)
    T coche = node->data;
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
std::string BST<T>::cifrarTexto(const std::string &texto)
    std::string textoCifrado = texto;
    for (char &c : textoCifrado)
            c = ((c - '0' + 2) % 10) + '0';
    return textoCifrado;
std::string BST<T>::descifrarTexto(const std::string &texto)
    std::string textoDescifrado = texto;
    return textoDescifrado;
bool BST<T>::estaVacia() const
    return raiz == nullptr;
void BST<T>::salirDelParqueadero(const std::string &placa)
    BSTNode<T>* actual = raiz;
        T coche = actual->data;
                    actual = actual->left;
                    actual = actual->right;
            auto ahora = std::chrono::system_clock::now();
            coche.setHoraSalida(ahora);
            actual->data = coche;
            std::cout << "El coche con placa " << placa << " ha salido del parqueadero." << std::endl;
            break;
        GuardarArchivo("autos_historial.txt");
        std::cerr << "Coche con placa " << placa << " no encontrado en el parqueadero." << std::endl;
void BST<T>::GuardarPropietarios(const std::string& nombreArchivo)
    ofstream archivo(nombreArchivo);
        cerr << "No se pudo abrir el archivo para escritura: " << nombreArchivo << endl;
    GuardarPropietariosRec(root, archivo);
void BST<T>::GuardarPropietariosRec(BSTNode<T>* node, ofstream& archivo)
    archivo << node->data.getNombre() << ","
            << node->data.getApellido() << ","
            << node->data.getCedula() << ","
            << node->data.getCorreo() << ",";
    vector<string> placas = node->data.getPlacas();
        archivo << placas[i];
            archivo << ",";
    archivo << endl;
void BST<T>::CargarPropietarios(const std::string& nombreArchivo)
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
void BST<T>::BusquedaAvanzadaPropietario(string criterio, string valorInicio, string valorFin)
    BusquedaAvanzadaPropietarioRec(raiz, criterio, valorInicio, valorFin, encontrado);
        cout << "No se encontro ningun propietario con el criterio de busqueda: " << criterio << endl;
void BST<T>::BusquedaAvanzadaPropietarioRec(BSTNode<T>* node, string criterio, string valorInicio, string valorFin, bool& encontrado)
        string cedula = node->data.getCedula();
            cout << "   PROPIETARIO REGISTRADO POR CEDULA" << endl;
        string correo = node->data.getCorreo();
            cout << "   PROPIETARIO REGISTRADO POR CORREO" << endl;
        string nombre = node->data.getNombre();
            cout << "   PROPIETARIO REGISTRADO POR NOMBRE" << endl;
        string apellido = node->data.getApellido();
            cout << "   PROPIETARIO REGISTRADO POR APELLIDO" << endl;
