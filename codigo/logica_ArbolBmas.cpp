//
//  ArbolBmas.cpp
//	[ Insertar documentacion ]
//


#include "logica_ArbolBmas.h"
#include "fisica_SerialBuffer.h"
#include "fisica_ArchivoBloques.h"
#include "logica_ArbolBmasNodo.h"
#include "logica_ArbolBmasNodoHoja.h"
#include "logica_ArbolBmasNodoInterno.h"
#include "domain_RegistroGenerico.h"




/* ****************************************************************************
 * CONSTANTES
 * ***************************************************************************/

namespace {

	// Constantes para el buffer
	const int BUFFER_TAMANIO = 512;

	// Constantes para los numeros de bloque
	const uint NUM_BLOQUE_METADATA = 0;
	const uint NUM_BLOQUE_RAIZ_INICIAL = 1;
}




/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
ArbolBmas::ArbolBmas() : nivel(0), contBloques(NUM_BLOQUE_RAIZ_INICIAL) 
{
	this->buffer = new SerialBuffer(BUFFER_TAMANIO);
}


// Destructor
ArbolBmas::~ArbolBmas() 
{
	// Liberamos la memoria utilizada por el archivo
	delete this->archivo;
	// Liberamos la memoria utilizada para el buffer de serializacion
	delete this->buffer;
	// Liberamos la memoria utilizada para mantener la raiz en memoria
	delete this->raiz;
}


// Abre un arbol ya existente
// PRE: 'nombre_archivo' es la ruta del archivo donde se almacena el arbol.
// POST: si no existe el archivo se crea uno nuevo y se inicializa el arbol,
void ArbolBmas::abrir(const char* nombre_archivo)
{
	// Creamos un archivo de bloques
	this->archivo = new ArchivoBloques(512, nombre_archivo);

	// Inicializamos el archivo de bloques o lo levantamos si ya existia
	// if(this->archivo->abrirArchivo() == -1)
	if(true)
	{
		// El archivo no existe, lo creamos
		// this->archivo->crearArchivo();
		// this->archivo->abrirArchivo();

		// Creamos el nodo raiz
		this->raiz = new NodoHoja< CANT_REG_NODO_HOJA, CANT_REG_NODO_INTERNO >;
		this->raiz->inicializar(NUM_BLOQUE_RAIZ_INICIAL, 0);

		// Creamos metadata del arbol con valores iniciales
		guardarMetadata();

		return;
	}
	
	// Cargamos metadata
	cargarMetadata();
}


// Inserta un registro nuevo en el árbol
// PRE: 'clave' es la clave o id con el que se identifica el registro;
// 'registro' es el registro que se desea ingresar, el cual debe ser un
// RegistroGenerico
void ArbolBmas::insertar(uint clave, RegistroGenerico& registro)
{
	// Corroboramos que se haya creado el arbol
	if(!this->archivo)
		throw "ArbolBmas::insertar() ERROR: no se ha abierto el arbol";

	// Insertamos. Si no hubo overflow, retornamos
	if(!this->raiz->insertar(clave, registro, this->archivo, 
		this->contBloques)) return;

	// Hubo overflow, pasamos a partir la raiz y generar una nueva raiz.
	Nodo *nuevoHermano;

	if(this->nivel == 0)
		nuevoHermano = new NodoHoja< CANT_REG_NODO_HOJA, 
			CANT_REG_NODO_INTERNO >;
	else
		nuevoHermano = new NodoInterno< CANT_REG_NODO_HOJA, 
			CANT_REG_NODO_INTERNO >;

	NodoInterno< CANT_REG_NODO_HOJA, CANT_REG_NODO_INTERNO > *nuevaRaiz = 
		new NodoInterno< CANT_REG_NODO_HOJA, CANT_REG_NODO_INTERNO >;

	// Inicializamos al nuevo hermano
	this->contBloques++;
	nuevoHermano->inicializar(this->contBloques, this->nivel);

	// Inicializamos a la nueva raiz
	this->contBloques++;
	this->nivel++;
	nuevaRaiz->inicializar(this->contBloques, this->nivel);

	// Dividimos al nodo
	uint claveQueSube = this->raiz->dividir(nuevoHermano);

	// Insertamos clave e hijos en la nueva raiz
	nuevaRaiz->insertarHijosIniciales(claveQueSube, 
		this->raiz->getNumBloque(), nuevoHermano->getNumBloque());

	// Escribimos los nodos
	nuevaRaiz->guardar(this->archivo);
	nuevoHermano->guardar(this->archivo);
	this->raiz->guardar(this->archivo);

	delete this->raiz;
	delete nuevoHermano;
	
	// Guardamos en el arbol la nueva raiz
	this->raiz = nuevaRaiz;
}


// // Busca un registro en el arbol
// // PRE: 'clave' es la clave o id que identifica al registro a buscar;
// // 'registro' es una referencia a una almacenador en donde se insertara el
// // resultado de la busqueda
// // POST: Si se encontró el registro, se devuelve true y se almacena en
// // 'registro' al mismo. Si no se encontró, se devuelve false y se almacena
// // en 'registro' el registro superior mas proximo al buscado.
// bool ArbolBmas::buscar(const uint clave, RegistroGenerico& registro)
// {
// 	// Corroboramos que se haya creado el arbol
// 	if(!this->archivo)
// 		throw "ArbolBmas::buscar() ERROR: no se ha abierto el arbol";

// 	return false;
// }


// Imprime el arbol sobre la salida estandar. Las tabulaciones indican
// el nivel, siendo el nivel cero aquel que se encuentra con la mayor
// tabulacion.
void ArbolBmas::imprimir()
{
	this->raiz->imprimir(this->nivel, this->archivo);
}



/**********************************
 *  METODOS PRIVADOS
 **********************************/


// Carga la metadata del arbol desde el archivo.
// POST: si todavia no ha sido abierto o creado el archivo, no hace nada.
void ArbolBmas::cargarMetadata()
{
	// Limpiamoss buffer
	this->buffer->clear();

	// Levantamos la metadata del archivo
	this->archivo->leerBloque(this->buffer->getBuffer(), NUM_BLOQUE_METADATA);

	// Variables auxiliares para deserializacion
	uint nivel;
	uint contBloques;
	uint bloqueRaiz;

	// Deserializamos metadata del arbol
	this->buffer->unpack(&nivel);
	this->buffer->unpack(&contBloques);
	this->buffer->unpack(&bloqueRaiz);

	// Cargamos datos en atributos
	this->nivel = nivel;
	this->contBloques = contBloques;

	// Cargamos la raiz
	// Si el nivel es cero, la raiz es un nodo hoja, sino es nodo interno
	if(this->nivel == 0)
		this->raiz = new NodoHoja< CANT_REG_NODO_HOJA, CANT_REG_NODO_INTERNO >;
	else
		this->raiz = new NodoInterno< CANT_REG_NODO_HOJA, 
				CANT_REG_NODO_INTERNO >;

	// Seteamos el numero de bloque de la raiz y la leemos del archivo
	this->raiz->setNumBloque(bloqueRaiz);
	this->raiz->cargar(this->archivo);

	// DEBUG LINES
	std::cout << "UNPACK: " << nivel << " " << contBloques << " " 
		<< bloqueRaiz << std::endl;
	// END DEBUG LINES

	// Cargamos datos en atributos
	// this->nivel = metadata.nivel;
	// this->contBloques = metadata.contBloques;

	// Cargamos la raiz
	// this->archivo->leerBloque(this->raiz, metadata.raiz);
}


// Guarda la metadata actual del arbol en el archivo, actualizando info.
// POST: si todavia no ha sido abierto o creado el archivo, no hace nada.
void ArbolBmas::guardarMetadata()
{
	uint nivel = this->nivel;
	uint contBloques = this->contBloques;
	uint bloqueRaiz = this->raiz->getNumBloque();

	// Limpiamoss buffer
	this->buffer->clear();

	// Serializamos metadata del arbol
	this->buffer->pack(&nivel, sizeof(uint));
	this->buffer->pack(&contBloques, sizeof(uint));
	this->buffer->pack(&bloqueRaiz, sizeof(uint));

	// DEBUG LINES
	std::cout << "PACK: " << nivel << " " << contBloques << " " 
		<< bloqueRaiz << std::endl;
	// END DEBUG LINES

	// Escribimos metadata en archivo
	this->archivo->escribirBloque(this->buffer->getBuffer(), 
		NUM_BLOQUE_METADATA);
}
