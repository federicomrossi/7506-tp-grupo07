//
//  ArbolBmas.h
//	[ Insertar documentacion ]
//

#ifndef ARBOLBMAS_H
#define ARBOLBMAS_H


#include <stack>
#include "fisica_ArchivoBloques.h"




/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


template < typename TipoClave >
class ArbolBmas
{

private:

	class Nodo
	{
		unsigned int nivel;			// Nivel en el que se encuentra el nodo
		unsigned int numBloque;		// Numero de bloque que representa
		short int cantRegistros;	// Cantidad ḿáxima de registros que puede
									// contener el nodo.

		// Constructor
		Nodo();

		//
		int insertar(const TipoClave clave, int direccionRegistro);

		//
		int eliminar(const TipoClave clave, int direccionRegistro = -1);

		// Devuelve la mayor clave del nodo
		int claveMayor();

		//
		int particionar(Nodo *nodoNuevo);
	};

	ArchivoBloques archivo;			// Archivo donde se almacena el árbol
	Nodo *raiz;						// Nodo de la raiz
	unsigned int contBloques;		// Contador de bloques existentes
	unsigned int nivel;				// Contador del nivel actual del árbol
	stack<Nodo> ramaNodos;			// Almacenador para rama (HACERLO PILA)

	//
	Nodo* buscarHoja(const TipoClave clave);

	// Carga un nodo en memoria
	Nodo* cargarNodo(const int direccionRegistro);

	// Almacena un nodo en archivo
	int almacenarNodo(Nodo *nodo);

public:

	// Constructor
	ArbolBmas();

	// Destructor
	~ArbolBmas();

	// Abre un arbol ya existente
	// PRE: 'nombre_archivo' es la ruta del archivo donde se almacena el arbol.
	// POST: si no existe el archivo se lanza una excepcion.
	void abrir(string& nombre_archivo);

	//
	int insertar(const TipoClave clave);

	//
	int buscar(const TipoClave clave);
};



/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
template < typename TipoClave >
ArbolBmas< TipoClave >::ArbolBmas() : contBloques(0), nivel(0) { }


// Destructor
template < typename TipoClave >
ArbolBmas< TipoClave >::~ArbolBmas() { }


// Abre un arbol ya existente
// PRE: 'nombre_archivo' es la ruta del archivo donde se almacena el arbol.
// POST: si no existe el archivo se crea uno nuevo y se inicializa el arbol,
template < typename TipoClave >
void ArbolBmas< TipoClave >::abrir(string& nombre_archivo)
{
	// Abrimos el archivo donde almacenaremos el arbol
	this->archivo.abrir(nombre_archivo.c_str());
	
	this->raiz = new Nodo();
	this->archivo.escribirBloque(this->raiz, 0);

	// Abrimos el archivo donde se encuentra almacenado el arbol
	this->archivo.abrir(nombre_archivo.c_str());

	this->raiz = this->archivo.leerBloque(1);
}


//
template < typename TipoClave >
int ArbolBmas< TipoClave >::insertar(const TipoClave clave)
{
	return 0;
}


//
template < typename TipoClave >
int ArbolBmas< TipoClave >::buscar(const TipoClave clave)
{
	return 0;
}

#endif
