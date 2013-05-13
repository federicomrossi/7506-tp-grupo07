//
//  ArbolBmas.h
//	[ Insertar documentacion ]
//

#ifndef ARBOLBMAS_H
#define ARBOLBMAS_H


#include <stack>
#include "fisica_ArchivoBloques.h"




/* ****************************************************************************
 * CONSTANTES
 * ***************************************************************************/

namespace {

	// Constantes para el tamaño de los bloques
	const int CANT_REG_NODO_INTERNO = 5;
	const int CANT_REG_NODO_HOJA = 6;

	// Constantes para los numeros de bloque
	const unsigned int NUM_BLOQUE_METADATA = 0;
	const unsigned int NUM_BLOQUE_RAIZ = 1;
}




/* ****************************************************************************
 * DECLARACIÓN DEL TEMPLATE
 * ***************************************************************************/


template < typename TipoClave >
class ArbolBmas
{

private:

	// Estructura con informacion del arbol. Se utiliza solamente para
	// almacenar o para levantar los metadatos del arbol desde un archivo
	struct Metadata {
		unsigned int nivel;				// Contador del nivel actual del árbol
		unsigned int contBloques;		// Contador de bloques existentes
	};

	// Clase interna que representa el nodo de un arbol. 
	struct Nodo
	{
		unsigned int nivel;			// Nivel en el que se encuentra el nodo
		unsigned int numBloque;		// Numero de bloque que representa
		short int cantRegistros;	// Cantidad ḿáxima de registros que puede
									// contener el nodo.


		// Constructor
		// Nodo(unsigned int nivel, unsigned int numBloque, 
		// 	short int cantRegistros);
		Nodo();

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
	int insertar(const TipoClave clave);

	//
	int buscar(const TipoClave clave);
};



/* ****************************************************************************
 * DEFINICIÓN DEL TEMPLATE
 * ***************************************************************************/


// Constructor
template < typename TipoClave >
ArbolBmas< TipoClave >::ArbolBmas() {
	this->contBloques = 0;
	this->nivel = 0;
}


// Destructor
// template < typename TipoClave >
// ArbolBmas< TipoClave >::~ArbolBmas() 
// {
// 	// Liberamos archivo
// 	if(this->archivo != 0) delete this->archivo;
// }


// Abre un arbol ya existente
// PRE: 'nombre_archivo' es la ruta del archivo donde se almacena el arbol.
// POST: si no existe el archivo se crea uno nuevo y se inicializa el arbol,
template < typename TipoClave >
void ArbolBmas< TipoClave >::abrir(string& nombre_archivo)
{
	// Creamos un archivo de bloques
	this->archivo = new ArchivoBloques(sizeof(Nodo), nombre_archivo.c_str());

	// Inicializamos el archivo de bloques o lo levantamos si ya existia
	if(this->archivo->abrirArchivo() == -1)
	{
		// El archivo no existe, lo creamos
		this->archivo->crearArchivo();

		// Creamos metadata del arbol con valores iniciales
		guardarMetadata();

		// Creamos el nodo raiz
		this->raiz = new Nodo();
		this->raiz->nivel = this->nivel;
		this->raiz->numBloque = NUM_BLOQUE_RAIZ;
		this->archivo->escribirBloque((void*) this->raiz, NUM_BLOQUE_RAIZ);

		return;
	}
	
	// Cargamos metadata
	cargarMetadata();

	// Cargamos nodo raiz
	this->archivo->leerBloque((void*) this->raiz, NUM_BLOQUE_RAIZ);

	// Apilamos puntero a nodo raiz para comenzar rama
	this->ramaNodos.push(this->raiz);
}


//
template < typename TipoClave >
int ArbolBmas< TipoClave >::insertar(const TipoClave clave)
{
	// Corroboramos que se haya creado el arbol
	if(!this->archivo)
		throw "ERROR: no se ha abierto el arbol";

	return 0;
}


//
template < typename TipoClave >
int ArbolBmas< TipoClave >::buscar(const TipoClave clave)
{
	// Corroboramos que se haya creado el arbol
	if(!this->archivo)
		throw "ERROR: no se ha abierto el arbol";

	return 0;
}

#endif




/*
 *  METODOS PRIVADOS
 */


// Carga la metadata del arbol desde el archivo.
// POST: si todavia no ha sido abierto o creado el archivo, no hace nada.
template < typename TipoClave >
void ArbolBmas< TipoClave >::cargarMetadata()
{
	// Corroboramos que esté abierto el archivo
	if(!this->archivo->estaAbierto()) return;

	// Levantamos la metadata del archivo
	Metadata *metadata = 0;
	this->archivo->leerBloque((void*) metadata, NUM_BLOQUE_METADATA);

	// Cargamos datos en atributos
	this->nivel = metadata->nivel;
	this->contBloques = metadata->contBloques;

	delete metadata;
}


// Guarda la metadata actual del arbol en el archivo, actualizando info.
// POST: si todavia no ha sido abierto o creado el archivo, no hace nada.
template < typename TipoClave >
void ArbolBmas< TipoClave >::guardarMetadata()
{
	// Corroboramos que esté abierto el archivo
	if(!this->archivo->estaAbierto()) return;

	// Creamos la metadata a almacenar
	Metadata *metadata = new Metadata();
	metadata->nivel = this->nivel;
	metadata->contBloques = this->contBloques;

	// Escribimos metadata en archivo
	this->archivo->escribirBloque((void*) metadata, NUM_BLOQUE_METADATA);

	delete metadata;
}



/*
 *  ESTRUCTURAS INTERNAS
 */


// Constructor
template < typename TipoClave >
ArbolBmas< TipoClave >::Nodo::Nodo()
{

}