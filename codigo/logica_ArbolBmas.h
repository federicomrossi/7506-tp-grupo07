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

	ArchivoBloques<Nodo> archivo;	// Archivo donde se almacena el árbol
	Nodo raiz;						// Nodo de la raiz
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

	// Crea el arbol
	void crear(string& nombre_archivo);

	//
	int insertar(const TipoClave clave, const int direccionRegistro);

	//
	int buscar(const TipoClave clave, const int direccionRegistro = -1);
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


// Crea el arbol
template < typename TipoClave >
void ArbolBmas< TipoClave >::crear(string& nombre_archivo)
{
	// Abrimos el archivo donde almacenamos el arbol
	this->archivo.abrir(nombre_archivo.c_str());
	this->raiz = new Nodo();
}



#endif
