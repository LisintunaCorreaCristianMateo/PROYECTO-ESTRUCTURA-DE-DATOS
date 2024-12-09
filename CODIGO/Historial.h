#ifndef HISTORIAL_H
#define HISTORIAL_H

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

		   
		Nodo* siguiente;         // Apunta al siguiente nodo
		Nodo* anterior;

	public :
	//constructor
	Nodo(int _puesto, string _placa,string _cedula,string _nombre,string _segundoNombre, string _apellido, string _segundoApellido,string _fecha,string _horaIngreso,string _horaSalida);

	
		//Destructor
	~Nodo();
    
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

    Nodo* getSiguiente();

    Nodo* getAnterior();

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



    void setSiguiente(Nodo* nodo);

    void setAnterior(Nodo* nodo);

};


#endif


