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
#include <algorithm>
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
        insert(node->right, data);  // Llamada recursiva a 'insert'
    }
}


template <typename T>
void BST<T>::insertar(T data) {  // Método público
    insert(raiz, data);  // Llama al método privado 'insert'
}

template <typename T>
BSTNode<T>* BST<T>::buscar(BSTNode<T>* node, const std::string& key) {
    if (node == nullptr || node->data.getPlaca() == key) {
        return node;
    } else if (key < node->data.getPlaca()) {
        return buscar(node->left, key);
    } else {
        return buscar(node->right, key);
    }
}

template <typename T>
BSTNode<T>* BST<T>::buscar(const std::string& key) {
    return buscar(raiz, key);
}

template <typename T>
void BST<T>::inorder(BSTNode<T>* node) {
    if (node != nullptr) {
        inorder(node->left);
        std::cout << node->data << std::endl;
        inorder(node->right);
    }
}

template <typename T>
void BST<T>::inorder() {
    inorder(raiz);
}


template <typename T>
void BST<T>::buscarPorPlaca(string placa)
{
    BSTNode<T>* aux = raiz;
    while (aux != nullptr)
    {
        if (aux->data.getPlaca() == placa)
        {
            cout << "========================================" << endl;
            cout << "   AUTOMOVIL REGISTRADO" << endl;
            cout << "========================================" << endl;
            cout << aux->data << endl;
            return;
        }
        else if (placa < aux->data.getPlaca())
        {
            aux = aux->left;
        }
        else
        {
            aux = aux->right;
        }
    }

    cout << "El coche con la placa " << placa << " no esta en el parqueadero." << endl;
}

template <typename T>
void BST<T>::mostrar(BSTNode<T>* node)
{
    if (node == nullptr)
    {
        std::cout << "El arbol esta vacio." << std::endl;
        return;
    }

    if (node->left != nullptr)
    {
        mostrar(node->left);
    }

    cout << "AUTOMOVIL REGISTRADO" << endl;
    cout << "========================================" << endl;
    cout << node->data << endl;

    if (node->right != nullptr)
    {
        mostrar(node->right);
    }
}

template <typename T>
void BST<T>::eliminarPorPlaca(string placa)
{
    raiz = eliminarPorPlacaRec(raiz, placa);
}

template <typename T>
BSTNode<T>* BST<T>::eliminarPorPlacaRec(BSTNode<T>* node, string placa)
{
    if (node == nullptr)
    {
        cout << "El coche con la placa " << placa << " no se encontro en el parqueadero." << endl;
        return node;
    }

    if (placa < node->data.getPlaca())
    {
        node->left = eliminarPorPlacaRec(node->left, placa);
    }
    else if (placa > node->data.getPlaca())
    {
        node->right = eliminarPorPlacaRec(node->right, placa);
    }
    else
    {
        if (node->left == nullptr)
        {
            BSTNode<T>* temp = node->right;
            delete node;
            cout << "El coche con la placa " << placa << " ha sido eliminado." << endl;
            return temp;
        }
        else if (node->right == nullptr)
        {
            BSTNode<T>* temp = node->left;
            delete node;
            cout << "El coche con la placa " << placa << " ha sido eliminado." << endl;
            return temp;
        }

        BSTNode<T>* temp = minValueNode(node->right);
        node->data = temp->data;
        node->right = eliminarPorPlacaRec(node->right, temp->data.getPlaca());
    }

    return node;
}

template <typename T>
BSTNode<T>* BST<T>::minValueNode(BSTNode<T>* node)
{
    BSTNode<T>* current = node;
    while (current && current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

template <typename T>
void BST<T>::BusquedaAvanzada(string criterio, string valorInicio, string valorFin)
{
    if (raiz == nullptr)
    {
        cout << "El arbol esta vacio." << endl;
        return;
    }

    if (criterio != "hora")
    {
        transform(valorInicio.begin(), valorInicio.end(), valorInicio.begin(), ::tolower);
    }

    bool encontrado = false;
    BusquedaAvanzadaRec(raiz, criterio, valorInicio, valorFin, encontrado);

    if (!encontrado)
    {
        cout << "No se encontro ningun automovil con el criterio de busqueda: " << criterio << endl;
    }
}

template <typename T>
void BST<T>::BusquedaAvanzadaRec(BSTNode<T>* node, string criterio, string valorInicio, string valorFin, bool& encontrado)
{
    if (node == nullptr)
    {
        return;
    }

    BusquedaAvanzadaRec(node->left, criterio, valorInicio, valorFin, encontrado);

    if (criterio == "marca")
    {
        string marca = node->data.getMarca();
        transform(marca.begin(), marca.end(), marca.begin(), ::tolower);
        if (marca == valorInicio)
        {
            cout << "========================================" << endl;
            cout << "   AUTOMOVIL REGISTRADO POR MARCA" << endl;
            cout << "========================================" << endl;
            cout << node->data << endl;
            encontrado = true;
        }
    }
    else if (criterio == "modelo")
    {
        string modelo = node->data.getModelo();
        transform(modelo.begin(), modelo.end(), modelo.begin(), ::tolower);
        if (modelo == valorInicio)
        {
            cout << "========================================" << endl;
            cout << "   AUTOMOVIL REGISTRADO POR MODELO" << endl;
            cout << "========================================" << endl;
            cout << node->data << endl;
            encontrado = true;
        }
    }
    else if (criterio == "color")
    {
        string color = node->data.getColor();
        transform(color.begin(), color.end(), color.begin(), ::tolower);
        if (color == valorInicio)
        {
            cout << "========================================" << endl;
            cout << "   AUTOMOVIL REGISTRADO POR COLOR" << endl;
            cout << "========================================" << endl;
            cout << node->data << endl;
            encontrado = true;
        }
    }
    else if (criterio == "hora")
    {
        chrono::system_clock::time_point horaIngreso = node->data.getHora();
        time_t tiempo = chrono::system_clock::to_time_t(horaIngreso);
        tm* tm = localtime(&tiempo);

        char horaActual[9];
        strftime(horaActual, sizeof(horaActual), "%H:%M:%S", tm);

        auto estaEnIntervalo = [&valorInicio, &valorFin, &horaActual]()
        {
            return valorInicio <= horaActual && horaActual <= valorFin;
        };

        if (estaEnIntervalo())
        {
            cout << "========================================" << endl;
            cout << "   AUTOMOVIL REGISTRADO POR HORA" << endl;
            cout << "========================================" << endl;
            cout << node->data << endl;
            encontrado = true;
        }
    }

    BusquedaAvanzadaRec(node->right, criterio, valorInicio, valorFin, encontrado);
}

template <typename T>
void BST<T>::CargarArchivo(std::string nombreArchivo)
{
    std::ifstream archivo(nombreArchivo);

    if (!archivo.is_open())
    {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << ". Creando archivo vacío..." << std::endl;
        std::ofstream nuevoArchivo(nombreArchivo); 
        if (!nuevoArchivo.is_open())
        {
            std::cerr << "Error: No se pudo crear el archivo " << nombreArchivo << std::endl;
            return;
        }
        nuevoArchivo.close(); 
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea))
    {
        std::istringstream ss(linea);
        std::string placa, modelo, color, marca, fechaIngreso, horaSalida;

        if (std::getline(ss, placa, ',') &&
            std::getline(ss, modelo, ',') &&
            std::getline(ss, color, ',') &&
            std::getline(ss, marca, ',') &&
            std::getline(ss, fechaIngreso, ',') &&
            std::getline(ss, horaSalida, ','))
        {
            placa = descifrarTexto(placa);

            std::tm tm = {};
            std::istringstream ssFecha(fechaIngreso);
            ssFecha >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
            if (ssFecha.fail())
            {
                std::cerr << "Error en el formato de la fecha de ingreso: " << fechaIngreso << std::endl;
                continue;
            }
            auto horaIngreso = std::chrono::system_clock::from_time_t(std::mktime(&tm));

            std::chrono::system_clock::time_point horaSalidaParsed;
            if (horaSalida == "N/A" || horaSalida.empty())
            {
                horaSalidaParsed = std::chrono::system_clock::time_point();
            }
            else
            {
                std::tm tmSalida = {};
                std::istringstream ssHoraSalida(horaSalida);
                ssHoraSalida >> std::get_time(&tmSalida, "%a %b %d %H:%M:%S %Y");
                if (ssHoraSalida.fail())
                {
                    std::cerr << "Error en el formato de la hora de salida: " << horaSalida << std::endl;
                    horaSalidaParsed = std::chrono::system_clock::time_point();
                }
                else
                {
                    horaSalidaParsed = std::chrono::system_clock::from_time_t(std::mktime(&tmSalida));
                }
            }

            T coche(placa, modelo, color, marca, horaIngreso, horaSalidaParsed);

            this->insertar(coche);
        }
        else
        {
            std::cerr << "Error: Formato de línea inválido: " << linea << std::endl;
        }
    }

    archivo.close();
}

template <typename T>
void BST<T>::GuardarArchivo(std::string nombreArchivo)
{
    std::ofstream archivo(nombreArchivo);

    if (!archivo.is_open())
    {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << ". Creando archivo nuevo..." << std::endl;
        std::ofstream nuevoArchivo(nombreArchivo); 
        if (!nuevoArchivo.is_open())
        {
            std::cerr << "Error: No se pudo crear el archivo " << nombreArchivo << std::endl;
            return;
        }
        nuevoArchivo.close(); 
        return;
    }

    std::cout << "Abriendo archivo para guardar los datos..." << std::endl;

    GuardarArchivoRec(raiz, archivo);

    archivo.close();
}

template <typename T>
void BST<T>::GuardarArchivoRec(BSTNode<T>* node, std::ofstream& archivo)
{
    if (node == nullptr)
    {
        return;
    }

    GuardarArchivoRec(node->left, archivo);

    T coche = node->data;

    std::string placaCifrada = cifrarTexto(coche.getPlaca());
    auto horaIngreso = coche.getHora();
    std::time_t horaIngresoTime = std::chrono::system_clock::to_time_t(horaIngreso);
    std::tm tmHoraIngreso = *std::localtime(&horaIngresoTime);

    auto horaSalida = coche.getHoraSalida();
    std::ostringstream horaSalidaStream;

    if (horaSalida != std::chrono::system_clock::time_point())
    {
        std::time_t horaSalidaTime = std::chrono::system_clock::to_time_t(horaSalida);
        std::tm tmHoraSalida = *std::localtime(&horaSalidaTime);
        horaSalidaStream << std::put_time(&tmHoraSalida, "%a %b %d %H:%M:%S %Y");
    }
    else
    {
        horaSalidaStream << "N/A";
    }

    archivo << placaCifrada << ","
            << coche.getModelo() << ","
            << coche.getColor() << ","
            << coche.getMarca() << ","
            << std::put_time(&tmHoraIngreso, "%a %b %d %H:%M:%S %Y") << ","
            << horaSalidaStream.str() << std::endl;

    GuardarArchivoRec(node->right, archivo);
}
template <typename T>
std::string BST<T>::cifrarTexto(const std::string &texto)
{
    std::string textoCifrado = texto;

    for (char &c : textoCifrado)
    {
        if (isdigit(c))
        {
            c = ((c - '0' + 2) % 10) + '0';
        }
        else if (isalpha(c))
        {
            if (isupper(c))
            {
                c = ((c - 'A' + 2) % 26) + 'A';
            }
            else
            {
                c = ((c - 'a' + 2) % 26) + 'a';
            }
        }
    }

    return textoCifrado;
}

template <typename T>
std::string BST<T>::descifrarTexto(const std::string &texto)
{
    std::string textoDescifrado = texto;

    for (char &c : textoDescifrado)
    {
        if (isdigit(c))
        {
            c = ((c - '0' - 2 + 10) % 10) + '0';
        }
        else if (isalpha(c))
        {
            if (isupper(c))
            {
                c = ((c - 'A' - 2 + 26) % 26) + 'A';
            }
            else
            {
                c = ((c - 'a' - 2 + 26) % 26) + 'a';
            }
        }
    }

    return textoDescifrado;
}

template <typename T>
bool BST<T>::estaVacia() const
{
    return raiz == nullptr;
}
template <typename T>
void BST<T>::salirDelParqueadero(const std::string &placa)
{
    BSTNode<T>* actual = raiz;
    bool encontrado = false;

    while (actual != nullptr)
    {
        T coche = actual->data;

        if (coche.getPlaca() == placa)
        {
            if (coche.getHoraSalida() != std::chrono::system_clock::time_point())
            {
                if (placa < actual->data.getPlaca())
                {
                    actual = actual->left;
                }
                else
                {
                    actual = actual->right;
                }
                continue;
            }

            auto ahora = std::chrono::system_clock::now();
            coche.setHoraSalida(ahora);
            actual->data = coche;

            std::cout << "El coche con placa " << placa << " ha salido del parqueadero." << std::endl;
            encontrado = true;
            break;
        }

        if (placa < actual->data.getPlaca())
        {
            actual = actual->left;
        }
        else
        {
            actual = actual->right;
        }
    }

    if (encontrado)
    {
        GuardarArchivo("autos_historial.txt");
    }
    else
    {
        std::cerr << "Coche con placa " << placa << " no encontrado en el parqueadero." << std::endl;
    }
}
template <typename T>
void BST<T>::GuardarPropietarios(const std::string& nombreArchivo)
{
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo para escritura: " << nombreArchivo << endl;
        return;
    }

    GuardarPropietariosRec(root, archivo);

    archivo.close();
}

template <typename T>
void BST<T>::GuardarPropietariosRec(BSTNode<T>* node, ofstream& archivo)
{
    if (node == nullptr)
    {
        return;
    }

    GuardarPropietariosRec(node->left, archivo);

    archivo << node->data.getNombre() << ","
            << node->data.getApellido() << ","
            << node->data.getCedula() << ","
            << node->data.getCorreo() << ",";

    vector<string> placas = node->data.getPlacas();
    for (size_t i = 0; i < placas.size(); ++i)
    {
        archivo << placas[i];
        if (i < placas.size() - 1)
        {
            archivo << ",";
        }
    }
    archivo << endl;

    GuardarPropietariosRec(node->right, archivo);
}

template <typename T>
void BST<T>::CargarPropietarios(const std::string& nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo para lectura: " << nombreArchivo << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string nombre, apellido, cedula, correo, placasStr;

        getline(ss, nombre, ',');
        getline(ss, apellido, ',');
        getline(ss, cedula, ',');
        getline(ss, correo, ',');
        getline(ss, placasStr);

        vector<string> placas;
        stringstream ssPlacas(placasStr);
        string placa;
        while (getline(ssPlacas, placa, ','))
        {
            placas.push_back(placa);
        }

        T propietario(nombre, apellido, cedula, correo);
        for (const auto& p : placas)
        {
            propietario.agregarPlaca(p);
        }

        this->insertar(propietario);
    }

    archivo.close();
}

template <typename T>
void BST<T>::BusquedaAvanzadaPropietario(string criterio, string valorInicio, string valorFin)
{
    if (raiz == nullptr)
    {
        cout << "El arbol esta vacio." << endl;
        return;
    }

    if (criterio != "hora")
    {
        transform(valorInicio.begin(), valorInicio.end(), valorInicio.begin(), ::tolower);
    }

    bool encontrado = false;
    BusquedaAvanzadaPropietarioRec(raiz, criterio, valorInicio, valorFin, encontrado);

    if (!encontrado)
    {
        cout << "No se encontro ningun propietario con el criterio de busqueda: " << criterio << endl;
    }
}

template <typename T>
void BST<T>::BusquedaAvanzadaPropietarioRec(BSTNode<T>* node, string criterio, string valorInicio, string valorFin, bool& encontrado)
{
    if (node == nullptr)
    {
        return;
    }

    BusquedaAvanzadaPropietarioRec(node->left, criterio, valorInicio, valorFin, encontrado);

    if (criterio == "cedula")
    {
        string cedula = node->data.getCedula();
        transform(cedula.begin(), cedula.end(), cedula.begin(), ::tolower);
        if (cedula == valorInicio)
        {
            cout << "========================================" << endl;
            cout << "   PROPIETARIO REGISTRADO POR CEDULA" << endl;
            cout << "========================================" << endl;
            cout << node->data << endl;
            encontrado = true;
        }
    }
    else if (criterio == "correo")
    {
        string correo = node->data.getCorreo();
        transform(correo.begin(), correo.end(), correo.begin(), ::tolower);
        if (correo == valorInicio)
        {
            cout << "========================================" << endl;
            cout << "   PROPIETARIO REGISTRADO POR CORREO" << endl;
            cout << "========================================" << endl;
            cout << node->data << endl;
            encontrado = true;
        }
    }
    else if (criterio == "nombre")
    {
        string nombre = node->data.getNombre();
        transform(nombre.begin(), nombre.end(), nombre.begin(), ::tolower);
        if (nombre == valorInicio)
        {
            cout << "========================================" << endl;
            cout << "   PROPIETARIO REGISTRADO POR NOMBRE" << endl;
            cout << "========================================" << endl;
            cout << node->data << endl;
            encontrado = true;
        }
    }
    else if (criterio == "apellido")
    {
        string apellido = node->data.getApellido();
        transform(apellido.begin(), apellido.end(), apellido.begin(), ::tolower);
        if (apellido == valorInicio)
        {
            cout << "========================================" << endl;
            cout << "   PROPIETARIO REGISTRADO POR APELLIDO" << endl;
            cout << "========================================" << endl;
            cout << node->data << endl;
            encontrado = true;
        }
    }

    BusquedaAvanzadaPropietarioRec(node->right, criterio, valorInicio, valorFin, encontrado);
}