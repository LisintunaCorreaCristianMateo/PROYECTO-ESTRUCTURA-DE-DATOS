#ifndef HISTORIAL_H
#define HISTORIAL_H
#include <iostream>
#include <string>
using namespace std;

class Historial{
	private:
		int puesto;
		string placa;            // Placa del veh�culo (si est� ocupado)
		string cedula;
		string nombre;
		string segundoNombre;
		string apellido;
		string segundoApellido;
		string fecha;
		string horaIngreso;
		string horaSalida;
		   
		Historial* siguiente;         // Apunta al siguiente nodo
		Historial* anterior;

	public :
	//constructor
	Historial(int _puesto, string _placa,string _cedula,string _nombre,string _segundoNombre, string _apellido, string _segundoApellido,string _fecha,string _horaIngreso,string _horaSalida);

	
		//Destructor
	~Historial();
    
        // Getters
    int getPuesto();

    bool isOcupado();

    string getPlaca();

    string gethoraIngreso();

    string gethoraSalida();

    string getNombre();

    string getSegundoNombre();
    
    string getApellido();
    
    string getSegundoApellido();
    
    string getCedula();
    
    string getFecha();

    Historial* getSiguiente();

    Historial* getAnterior();

    // Setters


    void setPlaca( string value);

    void setCedula(string );
    
    void setNombre(string);

    void setSegundoNombre(string);

    void setApellido(string);

    void setSegundoApellido(string);

    void setHoraIngreso(string);
    
    void setHoraSalida(string);

    void setFecha(string);



    void setSiguiente(Historial* nodo);

    void setAnterior(Historial* nodo);

};


#endif


