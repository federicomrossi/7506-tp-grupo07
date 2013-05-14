//
//  ArbolBmas.cpp
//	[ Insertar documentacion ]
//



#include "logica_ArbolBmas.h"




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
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
ArbolBmas::ArbolBmas() {
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
void ArbolBmas::abrir(string& nombre_archivo)
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
		this->raiz = new Nodo(this->nivel, NUM_BLOQUE_RAIZ);
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
int ArbolBmas::insertar(const unsigned int clave, RegistroGenerico *registro)
{
	// Corroboramos que se haya creado el arbol
	if(!this->archivo)
		throw "ArbolBmas::insertar() ERROR: no se ha abierto el arbol";

	return 0;
}


//
int ArbolBmas::buscar(const unsigned int clave)
{
	// Corroboramos que se haya creado el arbol
	if(!this->archivo)
		throw "ArbolBmas::buscar() ERROR: no se ha abierto el arbol";

	return 0;
}




/**********************************
 *  METODOS PRIVADOS
 **********************************/


// Carga la metadata del arbol desde el archivo.
// POST: si todavia no ha sido abierto o creado el archivo, no hace nada.
void ArbolBmas::cargarMetadata()
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
void ArbolBmas::guardarMetadata()
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



/**********************************
 *  ESTRUCTURAS INTERNAS
 **********************************/


// Constructor
ArbolBmas::Nodo::Nodo(unsigned int nivel, unsigned int numBloque)
{

}


// Constructor
ArbolBmas::NodoInterno::NodoInterno()	
{

}
