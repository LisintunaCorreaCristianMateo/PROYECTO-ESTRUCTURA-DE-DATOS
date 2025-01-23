#include <iostream>
#include <vector>
#include <conio.h>
#include "Propietario.h"
#include "Coche.h"
#include "BST.h"
#include "Validaciones.h"
#include "ValidacionPlaca.h"
#include "Menu.h"
#include "Ordenamiento.cpp"

using namespace std;

Coche coche;

template <typename T>
void menuEliminarPlaca(BST<Propietario> &arbolPropietarios)
{
    Placa<Propietario> validador;
    Validaciones validaciones;
    system("cls");
    cout << "========================================" << endl;
    cout << "========================================" << endl;
    cout << "    ELIMINAR PLACA DE PROPIETARIO       " << endl;
    cout << "========================================" << endl;
    cout << "========================================" << endl;

    string cedula = validaciones.ingresarCedula("Ingrese la cedula del propietario: ");
    BSTNode<Propietario>* aux = arbolPropietarios.search(cedula);
    bool encontrado = false;

    if (aux != nullptr) {
        encontrado = true;
        cout << "========================================" << endl;
        cout << "   PROPIETARIO REGISTRADO" << endl;
        cout << "========================================" << endl;
        cout << aux->data << endl;

        vector<string> placas = aux->data.getPlacas();

        if (placas.empty()) {
            cout << "Este propietario no tiene placas asociadas." << endl;
            return;
        }

        vector<string> opcionesPlacas = placas;
        opcionesPlacas.push_back("Volver");
        int seleccion = menuInteractivo(opcionesPlacas, "Seleccionar Placa a Eliminar");

        if (seleccion == opcionesPlacas.size() - 1) {
            return;
        }

        string placa = placas[seleccion];

        vector<string> placasActualizadas = aux->data.eliminarPlaca(placa);

        Propietario propietarioActualizado(aux->data.getNombre(), aux->data.getApellido(),
                                           aux->data.getCedula(), aux->data.getCorreo());

        propietarioActualizado.setPlacas(placasActualizadas);

        aux->data = propietarioActualizado;
        cout << aux->data << endl;

        arbolPropietarios.insert(propietarioActualizado);
    }

    if (!encontrado) {
        cout << "No se encontró un propietario con esa cédula." << endl;
    }
}



int menuInteractivo(const vector<string> &opciones, const string &titulo)
{
    int seleccion = 0;
    const int numOpciones = opciones.size();

    while (true)
    {
        system("cls");

        cout << "========================================" << endl;
        cout << "========================================" << endl;
        cout << "        " << titulo << endl;
        cout << "========================================" << endl;
        cout << "========================================" << endl;

        for (int i = 0; i < numOpciones; ++i)
        {
            if (i == seleccion)
            {
                cout << " > " << opciones[i] << " < " << endl;
            }
            else
            {
                cout << "   " << opciones[i] << endl;
            }
        }

        cout << "========================================" << endl;

        char tecla = _getch();

        if (tecla == 'a' || tecla == 72)
        {
            seleccion = (seleccion - 1 + numOpciones) % numOpciones;
        }
        else if (tecla == 's' || tecla == 80)
        {
            seleccion = (seleccion + 1) % numOpciones;
        }
        else if (tecla == 13)
        {
            return seleccion;
        }
    }
}

void menuGestionPropietarios(BST<Propietario> &arbolPropietarios)
{ 
    bool salirSubmenu = false;
    while (!salirSubmenu)
    {
        system("cls");
        cout << "========================================" << endl;
        cout << "========================================" << endl;
        cout << "      Menu de Gestion de Propietarios   " << endl;
        cout << "========================================" << endl;
        cout << "========================================" << endl;

        vector<string> opcionesPropietarios = {
            "Agregar Propietario",
            "Mostrar Propietarios",
            "Busqueda Avanzada",
            "Eliminar Placa de Propietario",
            "Volver al Menu Principal"};

        int seleccionPropietarios = menuInteractivo(opcionesPropietarios, "Menu de Gestion de Propietarios");
       
        switch (seleccionPropietarios)
        {
        case 0:
            {
                Propietario nuevoPropietario = nuevoPropietario.agregarPropietario();
                arbolPropietarios.insertar(nuevoPropietario);
                arbolPropietarios.GuardarPropietarios("propietarios.txt");
                break;
            }
        case 1:
            arbolPropietarios.mostrar(arbolPropietarios.getRaiz());
            system("pause");
            break;
        case 2:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "          BUSQUEDA AVANZADA             " << endl;
                cout << "========================================" << endl;
                menuBusquedaAvanzadaPropietario(arbolPropietarios);
                system("pause");
                break;
            }
        case 3:
          {
            menuEliminarPlaca<Propietario>(arbolPropietarios);
            break;
        }
        case 4:
            salirSubmenu = true;
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    }
}
void menuBusquedaAvanzadaPropietario(BST<Propietario> &arbolPropietarios)
{
    Validaciones validaciones;
    vector<string> opcionesBusqueda = {
        "Buscar por Cedula",
        "Buscar por Correo",
        "Buscar por Nombre",
        "Buscar por Apellido",
        "Volver al Menu Principal"};

    while (true)
    {
        int seleccionBusqueda = menuInteractivo(opcionesBusqueda, "Menu de Busqueda Avanzada");

        switch (seleccionBusqueda)
        {
        case 0:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "  Buscar por Cedula" << endl;
            cout << "========================================" << endl;
            string cedula;
            cout << "Ingrese la cedula: ";
            cedula = validaciones.ingresarCedula("Ingrese la cedula: ");
            arbolPropietarios.BusquedaAvanzadaPropietario("cedula", cedula, "");
            break;
        }
        case 1:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "  Buscar por Correo" << endl;
            cout << "========================================" << endl;
            string correo;
            cout << "Ingrese el correo: ";
            correo = validaciones.ingresarCorreo("Ingrese el correo: ");
            arbolPropietarios.BusquedaAvanzadaPropietario("correo", correo, "");
            break;
        }
        case 2:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "  Buscar por Nombre" << endl;
            cout << "========================================" << endl;
            string nombre;
            cout << "Ingrese el nombre: ";
            nombre = validaciones.ingresarString("Ingrese el nombre: ");
            arbolPropietarios.BusquedaAvanzadaPropietario("nombre", nombre, "");
            break;
        }
        case 3:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "  Buscar por Apellido" << endl;
            cout << "========================================" << endl;
            string apellido;
            cout << "Ingrese el apellido: ";
            apellido = validaciones.ingresarString("Ingrese el apellido: ");
            arbolPropietarios.BusquedaAvanzadaPropietario("apellido", apellido, "");
            break;
        }
        case 4:
        {
            cout << "Saliendo..." << endl;
            return;
        }
        default:
            cout << "Opción invalida. Intentalo de nuevo." << endl;
            break;
        }

        system("pause");
    }
}

void menu(BST<Coche> &arbol, BST<Coche> &arbolHistorial, BST<Propietario> &arbolPropietarios)
{
    Placa<Coche> validador;

    vector<string> opciones = {
        "Insertar Coche",
        "Mostrar Lista de Coches",
        "Busqueda de Coche Por Placa",
        "Busqueda Avanzada",
        "Menu de Gestion de Propietarios",
        "Liberar el parqueadero",
        "Recorridos",
        "Ayuda",
        "Salir"};

    string archivo = "autos.txt";
    string archivoHistorial = "autos_historial.txt";

    while (true)
    {
        int seleccion = menuInteractivo(opciones, "Menu de Parqueadero");

        switch (seleccion)
        {
        case 0:
        {

            if (arbolPropietarios.estaVacia())
            {
                cout << "No hay propietarios registrados. Por favor, registre un propietario antes de continuar." << endl;
                break;
            }

            Coche nuevoCoche = nuevoCoche.InsertarDatos(arbol, arbolHistorial, arbolPropietarios);
            arbol.insertar(nuevoCoche);
            arbol.GuardarArchivo("autos.txt");
            arbolHistorial.insertar(nuevoCoche);
            arbolHistorial.GuardarArchivo("autos_historial.txt");
            break;
        }
        case 1:
        {
            bool salirSubmenu = false;

            while (!salirSubmenu)
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "========================================" << endl;
                cout << "         Menu de Lista de Coches        " << endl;
                cout << "========================================" << endl;
                cout << "========================================" << endl;

                vector<string> opcionesLista = {
                    "Mostrar Coches en Parqueadero",
                    "Mostrar Historial Completo de Coches",
                    "Volver al Menu Principal"};

                int seleccionLista = menuInteractivo(opcionesLista, "Menu de Lista de Coches");

                switch (seleccionLista)
                {
                case 0:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "   LISTA DE COCHES EN EL PARQUEADERO    " << endl;
                    cout << "========================================" << endl;
                    arbol.mostrar(arbol.getRaiz());
                    system("pause");
                    break;
                }
                case 1:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "   HISTORIAL COMPLETO DE COCHES         " << endl;
                    cout << "========================================" << endl;
                    arbolHistorial.mostrar(arbolHistorial.getRaiz());
                    system("pause");
                    break;
                }
                case 2:
                {
                    cout << "Regresando al menu principal..." << endl;
                    salirSubmenu = true;
                    break;
                }
                default:
                    cout << "Opción inválida. Inténtelo de nuevo." << endl;
                    system("pause");
                    break;
                }
            }
            break;
        }
        case 2:
        {
            bool salirSubmenu = false;
            while (!salirSubmenu)
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "========================================" << endl;
                cout << "        Menu de Busqueda por Placa      " << endl;
                cout << "========================================" << endl;
                cout << "========================================" << endl;

                vector<string> opcionesBusqueda = {
                    "Buscar en Parqueadero",
                    "Buscar en Historial",
                    "Volver al Menu Principal"};

                int seleccionBusqueda = menuInteractivo(opcionesBusqueda, "Menu de Busqueda por Placa");

                switch (seleccionBusqueda)
                {
                case 0:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "   BUSQUEDA DE PLACA EN PARQUEADERO     " << endl;
                    cout << "========================================" << endl;
                    string placa;
                    cout << "Ingrese la placa a buscar(Utilize mayusculas para validar su placa): ";
                    cin >> placa;
                    arbol.buscarPorPlaca(placa);
                    system("pause");
                    break;
                }
                case 1:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "   BUSQUEDA DE PLACA EN HISTORIAL       " << endl;
                    cout << "========================================" << endl;
                    string placa;
                    cout << "Ingrese la placa a buscar(Utilize mayusculas para validar su placa): ";
                    cin >> placa;
                    arbolHistorial.buscarPorPlaca(placa);
                    system("pause");
                    break;
                }
                case 2:
                {
                    cout << "Regresando al menu principal..." << endl;
                    salirSubmenu = true;
                    break;
                }
                default:
                    cout << "Opción inválida. Inténtelo de nuevo." << endl;
                    system("pause");
                    break;
                }
            }
            break;
        }
        case 3:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            cout << "     BIENVENIDOS A LA BUSQUEDA AVANZADA  " << endl;
            cout << "========================================" << endl;
            cout << "========================================" << endl;

            menuBusquedaAvanzada(arbol, arbolHistorial);
            break;
        }
        case 4:
            menuGestionPropietarios(arbolPropietarios);
            break;
        case 5:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            cout << "  BIENVENIDOS A LA GESTION DE ESTACIONAMIENTO " << endl;
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            string placa;
            cout << "Ingrese la placa del coche que  va a  dejar el estacionamiento: ";
            cin >> placa;
            arbolHistorial.salirDelParqueadero(placa);
            arbol.eliminarPorPlaca(placa);
            break;
        }
        case 6:
        {
            menuMostrarRecorridos(arbol, arbolHistorial, arbolPropietarios);
            break;
        }
        case 7:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            cout << "               (i)AYUDA                 " << endl;
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            string archivo = "ayuda.html";
            string comando = "start " + archivo;
            system(comando.c_str());
            break;
        }
        case 8:
        {
            cout << "Saliendo..." << endl;
            return;
        }
        default:
            cout << "Opcion invalida. Inténtelo de nuevo." << endl;
            break;
        }

        system("pause");
    }
}

void menuBusquedaAvanzada(BST<Coche> &arbol, BST<Coche> &arbolHistorial)
{
    Validaciones validaciones;
    vector<string> opciones = {
        "Buscar en Parqueadero",
        "Buscar en Historial de Coches",
        "Volver al Menu Principal"};

    while (true)
    {
        int seleccion = menuInteractivo(opciones, "Menu de Busqueda Avanzada");

        switch (seleccion)
        {
        case 0:
        {
            vector<string> opcionesBusqueda = {
                "Buscar por Modelo",
                "Buscar por Color",
                "Buscar por Año/Fecha",
                "Buscar por Marca",
                "Buscar por Hora",
                "Volver al Menu Principal"};

            int seleccionBusqueda = menuInteractivo(opcionesBusqueda, "Menu de Busqueda en Parqueadero");

            switch (seleccionBusqueda)
            {
            case 0:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "  Buscar por Modelo" << endl;
                cout << "========================================" << endl;
                string modelo;
                cout << "Ingrese el modelo: ";
                modelo = validaciones.ingresarString("Ingrese el modelo: ");
                arbol.BusquedaAvanzada("modelo", modelo, "");
                break;
            }
            case 1:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "  Buscar por Color" << endl;
                cout << "========================================" << endl;
                string color;
                cout << "Ingrese el color: ";
                color = validaciones.ingresarString("Ingrese el color: ");
                arbol.BusquedaAvanzada("color", color, "");
                break;
            }
            case 2:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "  Buscar por Anio/Fecha" << endl;
                cout << "========================================" << endl;
                string fecha;
                cout << "Ingrese la fecha (DD-MM-AAAA): ";
                cin >> fecha;
                arbol.BusquedaAvanzada("fecha", fecha, "");
                break;
            }
            case 3:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "  Buscar por Marca" << endl;
                cout << "========================================" << endl;
                string marca;
                cout << "Ingrese la marca: ";
                marca = validaciones.ingresarString("Ingrese la marca: ");
                arbol.BusquedaAvanzada("marca", marca, "");
                break;
            }
            case 4:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "  Buscar por Hora" << endl;
                cout << "========================================" << endl;
                string HoraEntrada1, HoraEntrada2;
                cout << "Ingrese la hora de entrada 1: ";
                cin >> HoraEntrada1;
                cout << "Ingrese la hora de entrada 2: ";
                cin >> HoraEntrada2;
                arbol.BusquedaAvanzada("hora", HoraEntrada1, HoraEntrada2);
                break;
            }
            case 5:
            {
                cout << "Saliendo..." << endl;
                return;
            }
            default:
                cout << "Opción invalida. Intentalo de nuevo." << endl;
                break;
            }
            break;
        }

        case 1:
        {
            vector<string> opcionesBusqueda = {
                "Buscar por Modelo",
                "Buscar por Color",
                "Buscar por Año/Fecha",
                "Buscar por Marca",
                "Buscar por Hora",
                "Volver al Menu Principal"};

            int seleccionBusqueda = menuInteractivo(opcionesBusqueda, "Menu de Busqueda en Historial");

            switch (seleccionBusqueda)
            {
            case 0:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "  Buscar por Modelo" << endl;
                cout << "========================================" << endl;
                string modelo;
                cout << "Ingrese el modelo: ";
                modelo = validaciones.ingresarString("Ingrese el modelo: ");
                arbolHistorial.BusquedaAvanzada("modelo", modelo, "");
                break;
            }
            case 1:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "  Buscar por Color" << endl;
                cout << "========================================" << endl;
                string color;
                cout << "Ingrese el color: ";
                color = validaciones.ingresarString("Ingrese el color: ");
                arbolHistorial.BusquedaAvanzada("color", color, "");
                break;
            }
            case 2:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "  Buscar por Año/Fecha" << endl;
                cout << "========================================" << endl;
                string fecha;
                cout << "Ingrese la fecha (DD-MM-AAAA): ";
                cin >> fecha;
                arbolHistorial.BusquedaAvanzada("fecha", fecha, "");
                break;
            }
            case 3:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "  Buscar por Marca" << endl;
                cout << "========================================" << endl;
                string marca;
                cout << "Ingrese la marca: ";
                marca = validaciones.ingresarString("Ingrese la marca: ");
                arbolHistorial.BusquedaAvanzada("marca", marca, "");
                break;
            }
            case 4:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "  Buscar por Hora" << endl;
                cout << "========================================" << endl;
                string HoraEntrada1, HoraEntrada2;
                cout << "Ingrese la hora de entrada 1: ";
                cin >> HoraEntrada1;
                cout << "Ingrese la hora de entrada 2: ";
                cin >> HoraEntrada2;
                arbolHistorial.BusquedaAvanzada("hora", HoraEntrada1, HoraEntrada2);
                break;
            }
            case 5:
            {
                cout << "Saliendo..." << endl;
                return;
            }
            default:
                cout << "Opcion invalida. Intentalo de nuevo." << endl;
                break;
            }
            break;
        }

        case 2:
            cout << "Saliendo..." << endl;
            return;

        default:
            cout << "Opcion invalida. Intentalo de nuevo." << endl;
            break;
        }

        system("pause");
    }
}




template <typename T>
void mostrarElementos(const std::vector<T>& lista) {
    for (const auto& elemento : lista) {
        std::cout << elemento << std::endl;
    }
}

void menuMostrarRecorridos(BST<Coche> &arbol, BST<Coche> &arbolHistorial, BST<Propietario> &arbolPropietarios)
{
    bool salirMenu = false;

    while (!salirMenu)
    {
        system("cls");
        std::cout << "========================================" << std::endl;
        std::cout << "           Menu de Recorridos           " << std::endl;
        std::cout << "========================================" << std::endl;

        std::vector<std::string> opcionesTipo = {
            "Mostrar Coches",
            "Mostrar Propietarios",
            "Volver al Menu Principal"};

        int seleccionTipo = menuInteractivo(opcionesTipo, "Seleccione el tipo de recorrido:");

        if (seleccionTipo == 2)
        {
            salirMenu = true;
            continue;
        }

        if (seleccionTipo == 0)
        {
            menuMostrarCoches(arbol, arbolHistorial);
        }
        else if (seleccionTipo == 1)
        {
            menuMostrarPropietarios(arbolPropietarios);
        }
    }
}

void menuMostrarCoches(BST<Coche> &arbol, BST<Coche> &arbolHistorial)
{
    bool salirSubmenu = false;

    while (!salirSubmenu)
    {
        system("cls");
        std::cout << "========================================" << std::endl;
        std::cout << "           Menu de Mostrar Coches       " << std::endl;
        std::cout << "========================================" << std::endl;

        std::vector<std::string> opcionesMostrar = {
            "Mostrar en Inorden",
            "Mostrar en Preorden",
            "Mostrar en Posorden",
            "Volver al Menu Principal"};

        int seleccionMostrar = menuInteractivo(opcionesMostrar, "Seleccione el tipo de recorrido:");

        if (seleccionMostrar == 3)
        {
            salirSubmenu = true;
            continue;
        }

        system("cls");
        std::vector<Coche> lista;

        switch (seleccionMostrar)
        {
        case 0:
            lista = obtenerElementosEnOrden(arbol, "inorden");
            std::cout << "Lista de coches en Inorden:" << std::endl;
            break;
        case 1:
            lista = obtenerElementosEnOrden(arbol, "preorden");
            std::cout << "Lista de coches en Preorden:" << std::endl;
            break;
        case 2:
            lista = obtenerElementosEnOrden(arbol, "posorden");
            std::cout << "Lista de coches en Posorden:" << std::endl;
            break;
        default:
            std::cout << "Opcion invalida. Intente de nuevo." << std::endl;
            continue;
        }

        mostrarElementos(lista);

        system("pause");
    }
}

void menuMostrarPropietarios(BST<Propietario> &arbolPropietarios)
{
    bool salirSubmenu = false;

    while (!salirSubmenu)
    {
        system("cls");
        std::cout << "========================================" << std::endl;
        std::cout << "       Menu de Mostrar Propietarios     " << std::endl;
        std::cout << "========================================" << std::endl;

        std::vector<std::string> opcionesMostrar = {
            "Mostrar en Inorden",
            "Mostrar en Preorden",
            "Mostrar en Posorden",
            "Volver al Menu Principal"};

        int seleccionMostrar = menuInteractivo(opcionesMostrar, "Seleccione el tipo de recorrido:");

        if (seleccionMostrar == 3)
        {
            salirSubmenu = true;
            continue;
        }

        system("cls");
        std::vector<Propietario> lista;

        switch (seleccionMostrar)
        {
        case 0:
            lista = obtenerElementosEnOrden(arbolPropietarios, "inorden");
            std::cout << "Lista de propietarios en Inorden:" << std::endl;
            break;
        case 1:
            lista = obtenerElementosEnOrden(arbolPropietarios, "preorden");
            std::cout << "Lista de propietarios en Preorden:" << std::endl;
            break;
        case 2:
            lista = obtenerElementosEnOrden(arbolPropietarios, "posorden");
            std::cout << "Lista de propietarios en Posorden:" << std::endl;
            break;
        default:
            std::cout << "Opcion invalida. Intente de nuevo." << std::endl;
            continue;
        }

        mostrarElementos(lista);

        system("pause");
    }
}