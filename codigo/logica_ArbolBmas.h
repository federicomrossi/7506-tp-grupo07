//
//  ArbolBmas.h
//	[ Insertar documentacion ]
//

#ifndef ARBOLBMAS_H
#define ARBOLBMAS_H


#include <stack>
#include "fisica_ArchivoBloques.h"
#include "domain_RegistroGenerico.h"




/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class ArbolBmas
{

private:

	// Estructura con informacion del arbol. Se utiliza solamente para
	// almacenar o para levantar los metadatos del arbol desde un archivo
	struct Metadata {
		unsigned int nivel;				// Contador del nivel actual del árbol
		unsigned int contBloques;		// Contador de bloques existentes
	};

	struct Nodo
	{

		// Constructor
		Nodo(unsigned int nivel, unsigned int numBloque);
	};

	// Clase interna que representa al nodo interno de un arbol. 
	struct NodoInterno
	{
		unsigned int nivel;					// Nivel en el que se encuentra
		unsigned int numBloque;				// Numero de bloque que representa
		short int cantClavesReg;			// Cantidad ḿáxima de claves de 
											// registros que puede contener.
		unsigned int hijos[5];				// Arreglo de numeros de bloque de
											// de los hijos.
		unsigned int claves[4];				// Arreglo de claves del nodo.

		// Constructo
		// Nodo(unsigned int nivel, unsigned int numBloque, 
		// 	short int cantRegistros);
		NodoInterno();

		// //
		// int insertar(const TipoClave clave, int direccionRegistro);

		// //
		// int eliminar(const TipoClave clave, int direccionRegistro = -1);

		// // Devuelve la mayor clave del nodo
		// int claveMayor();

		// //
		// int particionar(Nodo *nodoNuevo);
	};




	ArchivoBloques *archivo;		// Archivo donde se almacena el árbol
	Nodo *raiz;						// Nodo de la raiz
	unsigned int nivel;				// Contador del nivel actual del árbol
	unsigned int contBloques;		// Contador de bloques existentes
	stack<Nodo*> ramaNodos;			// Almacenador para rama (HACERLO PILA)


	// Carga la metadata del arbol desde el archivo.
	// POST: si todavia no ha sido abierto o creado el archivo, no hace nada.
	void cargarMetadata();

	// Guarda la metadata actual del arbol en el archivo, actualizando info.
	// POST: si todavia no ha sido abierto o creado el archivo, no hace nada.
	void guardarMetadata();

	// //
	// Nodo* buscarHoja(const TipoClave clave);

	// // Carga un nodo en memoria
	// Nodo* cargarNodo(const int direccionRegistro);

	// // Almacena un nodo en archivo
	// int almacenarNodo(Nodo *nodo);

public:

	// Constructor
	ArbolBmas();

	// Destructor
	// ~ArbolBmas();

	// Abre un arbol ya existente
	// PRE: 'nombre_archivo' es la ruta del archivo donde se almacena el arbol.
	// POST: si no existe el archivo se lanza una excepcion.
	void abrir(string& nombre_archivo);

	//
	int insertar(const unsigned int clave, RegistroGenerico *registro);

	//
	int buscar(const unsigned int clave);
};

#endif
