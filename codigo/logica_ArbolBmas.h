//
//  ArbolBmas.h
//	[ Insertar documentacion ]
//


#ifndef ARBOLBMAS_H
#define ARBOLBMAS_H


#include <stack>
#include "fisica_ArchivoBloques.h"
#include "logica_ArbolBmasNodo.h"



// Definicion de tipo uint para utilizar nombre mas corto
typedef unsigned int uint; 




/* ****************************************************************************
 * CONFIGURACION
 * ***************************************************************************/

namespace {

	// Cantidad de registros en nodos
	const int CANT_REG_NODO_INTERNO = 5;
	const int CANT_REG_NODO_HOJA = 6;
}




/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class ArbolBmas
{

public:

	// Constructor
	ArbolBmas();

	// Destructor
	~ArbolBmas();

	// Abre un arbo.
	// PRE: 'nombre_archivo' es la ruta del archivo donde se almacena el arbol.
	// POST: Si existe el archivo, se carga el arbol existente, y si no existe
	// se crea un arbol nuevo en dicho archivo.
	void abrir(const char* nombre_archivo);

	// Inserta un registro nuevo en el árbol
	// PRE: 'clave' es la clave o id con el que se identifica el registro;
	// 'registro' es el registro que se desea ingresar, el cual debe ser un
	// RegistroGenerico
	void insertar(const uint clave, RegistroGenerico& registro);

	// Busca un registro en el arbol
	// PRE: 'clave' es la clave o id que identifica al registro a buscar;
	// 'registro' es una referencia a una almacenador en donde se insertara el
	// resultado de la busqueda
	// POST: Si se encontró el registro, se devuelve true y se almacena en
	// 'registro' al mismo. Si no se encontró, se devuelve false y se almacena
	// en 'registro' el registro superior mas proximo al buscado.
	bool buscar(const uint clave, RegistroGenerico& registro);

	// Cierra el archivo si se encuentra abierto
	void cerrar();


private:

	ArchivoBloques *archivo;				// Archivo donde se almacena
	ArbolBmasNodo *raiz;					// Nodo de la raiz
	uint nivel;								// Contador del nivel actual
	uint contBloques;						// Contador de bloques existentes
	stack<ArbolBmasNodo*> ramaNodos;		// Almacenador para rama


	// Carga la metadata del arbol desde el archivo.
	// POST: si todavia no ha sido abierto o creado el archivo, no hace nada.
	void cargarMetadata();

	// Guarda la metadata actual del arbol en el archivo, actualizando info.
	// POST: si todavia no ha sido abierto o creado el archivo, no hace nada.
	void guardarMetadata();


	// Estructura con informacion del arbol. 
	// Se utiliza solamente para almacenar o para levantar los metadatos del
	// arbol desde un archivo
	struct Metadata {
		uint nivel;					// Contador del nivel actual del árbol
		uint contBloques;			// Contador de bloques existentes
	};


	// Clase privada que representa a un nodo interno del arbol. 
	class NodoInterno : public ArbolBmasNodo
	{
		list< uint > hijos;			// Referencias a hijos

		// Constructor
		NodoInterno();

		// Inserta el registro en el nodo.
		// PRE: 'clave' es la clave a insertar; 'registro' es el registro
		// asociado a dicha clave.
		// POST: devuelve true si queda en overflow o false en caso contrario
		virtual bool insertar(uint clave, RegistroGenerico registro);

		// Reparte su contenido con su nodoHermano, pasandole la mitad.
		// PRE: 'nodoHermano' es un nodo con el que se hara la division
		// POST: devuelve la clave del registro inferior de 'nodoHermano'
		uint dividir(NodoInterno& nodoHermano);
	};


	// Clase privada que representa a un nodo hoja del arbol.
	class NodoHoja : public ArbolBmasNodo 
	{
		list< RegistroGenerico > registros;			// Lista de registros

		// Consctructor
		NodoHoja();

		// Inserta el registro en el nodo.
		// PRE: 'clave' es la clave a insertar; 'registro' es el registro
		// asociado a dicha clave.
		// POST: devuelve true si queda en overflow o false en caso contrario
		virtual bool insertar(uint clave, RegistroGenerico registro);

		// Reparte su contenido con su nodoHermano, pasandole la mitad.
		// PRE: 'nodoHermano' es un nodo con el que se hara la division
		// POST: devuelve la clave del registro inferior de 'nodoHermano'
		uint dividir(NodoHoja& nodoHermano);
	};
};

#endif
