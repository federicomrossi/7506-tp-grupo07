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
	const uint NUM_BLOQUE_METADATA = 1;
	const uint NUM_BLOQUE_RAIZ_INICIAL = 2;
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
	cerrar();
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
	if(this->archivo->abrirArchivo() == -1)
	{
		// El archivo no existe, lo creamos
		this->archivo->crearArchivo();
		this->archivo->abrirArchivo();

		// Creamos el nodo raiz
		this->raiz = new NodoHoja< CANT_REG_NODO_HOJA, CANT_REG_NODO_INTERNO >;
		this->raiz->inicializar(NUM_BLOQUE_RAIZ_INICIAL, 0);

		// // DEBUG LINES
		// try {
		// 	NodoHoja< CANT_REG_NODO_HOJA, CANT_REG_NODO_INTERNO > h;
		// 	h.inicializar(NUM_BLOQUE_RAIZ_INICIAL, 0);
		// 	RegistroGenerico reg;
		// 	uint bloque = 3;
		// 	RegistroGenerico reg1;
		// 	uint bloque1 = 4;
		// 	RegistroGenerico reg2;
		// 	uint bloque2 = 1;
		// 	RegistroGenerico reg3;
		// 	uint bloque3 = 2;
		// 	RegistroGenerico reg4;
		// 	uint bloque4 = 5;
		// 	RegistroGenerico reg5;
		// 	uint bloque5 = 7;
		// 	RegistroGenerico reg6;
		// 	uint bloque6 = 6;

		// 	if(h.insertar(bloque, reg, this->archivo, this->contBloques))
		// 		std::cout << "OVERFLOW " << 0 << std::endl;
		// 	if(h.insertar(bloque1, reg1, this->archivo, this->contBloques))
		// 		std::cout << "OVERFLOW " << 1 << std::endl;
		// 	if(h.insertar(bloque2, reg2, this->archivo, this->contBloques))
		// 		std::cout << "OVERFLOW " << 2 << std::endl;
		// 	if(h.insertar(bloque3, reg3, this->archivo, this->contBloques))
		// 		std::cout << "OVERFLOW " << 3 << std::endl;
		// 	if(h.insertar(bloque4, reg4, this->archivo, this->contBloques))
		// 		std::cout << "OVERFLOW " << 4 << std::endl;
		// 	if(h.insertar(bloque5, reg5, this->archivo, this->contBloques))
		// 		std::cout << "OVERFLOW " << 5 << std::endl;
		// 	if(h.insertar(bloque6, reg6, this->archivo, this->contBloques))
		// 		std::cout << "OVERFLOW " << 6 << std::endl;
			
		// 	std::cout << "ELEMENTOS EN LISTA: " << h.claves.tamanio() << 
		// 		std::endl;
		// 	std::cout << "REGISTROS EN LISTA: " << h.registros.tamanio() << 
		// 		std::endl;

		// 	uint a = 2;
		// 	h.imprimir(a);

		// 	std::cout << "DIVIDIMOS: " << std::endl;

		// 	NodoHoja< CANT_REG_NODO_HOJA, CANT_REG_NODO_INTERNO > hh;
		// 	hh.inicializar(NUM_BLOQUE_RAIZ_INICIAL+1, 0);

		// 	std::cout << "hacia arriba: " << h.dividir(&hh) << std::endl;

		// 	std::cout << "REGISTROS EN LISTA h: " << h.registros.tamanio() << 
		// 		std::endl;
		// 	std::cout << "REGISTROS EN LISTA hh: " << hh.registros.tamanio() << 
		// 		std::endl;

		// 	h.imprimir(a);
		// 	hh.imprimir(a);

		// 	RegistroGenerico reg7;
		// 	uint bloque7 = 7;
		// 	RegistroGenerico reg8;
		// 	uint bloque8 = 8;
		// 	RegistroGenerico reg9;
		// 	uint bloque9 = 9;
		// 	RegistroGenerico reg10;
		// 	uint bloque10 = 10;

		// 	h.insertar(bloque7, reg7, this->archivo, this->contBloques);
		// 	h.insertar(bloque8, reg8, this->archivo, this->contBloques);
		// 	h.insertar(bloque9, reg9, this->archivo, this->contBloques);
		// 	h.insertar(bloque10, reg10, this->archivo, this->contBloques);

		// 	h.imprimir(a);

		// 	std::cout << "DIVIDIMOS: " << std::endl;

		// 	NodoHoja< CANT_REG_NODO_HOJA, CANT_REG_NODO_INTERNO > hhh;
		// 	hhh.inicializar(NUM_BLOQUE_RAIZ_INICIAL+2, 0);

		// 	std::cout << "hacia arriba: " << h.dividir(&hhh) << std::endl;

		// 	h.imprimir(a);
		// 	hhh.imprimir(a);
		// 	hh.imprimir(a);

		// }
		// catch(char const * e)
		// {
		// 	std::cout << e << std::endl;
		// }

		// std::cout << "NODO HOJA COMPLETO" << std::endl;
		// std::cout << sizeof(*this->raiz) << std::endl;
		// std::cout << sizeof(NodoHoja< CANT_REG_NODO_HOJA, CANT_REG_NODO_INTERNO >) << std::endl;
		// // END DEBUG LINES

		// Creamos metadata del arbol con valores iniciales
		guardarMetadata();

		// Guardamos nodo raiz inicial
		// this->archivo->escribirBloque((char*) this->raiz, this->raiz->getNumBloque(), sizeof(*this->raiz));

		return;
	}
	
	// Cargamos metadata
	cargarMetadata();

	// std::cout << "raiz: " << this->raiz->getNumBloque() << " " << this->raiz->nivel << std::endl;
}


// Inserta un registro nuevo en el árbol
// PRE: 'clave' es la clave o id con el que se identifica el registro;
// 'registro' es el registro que se desea ingresar, el cual debe ser un
// RegistroGenerico
void ArbolBmas::insertar(const uint clave, RegistroGenerico& registro)
{
	// Corroboramos que se haya creado el arbol
	if(!this->archivo)
		throw "ArbolBmas::insertar() ERROR: no se ha abierto el arbol";

	// if(!this->raiz->insertar(clave, registro, this->archivo, 
	// 	this->contBloques)) return;

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


// Cierra el archivo si se encuentra abierto
void ArbolBmas::cerrar()
{
	// Corroboramos que esté abierto el archivo
	if(this->archivo->estaAbierto())
		this->archivo->cerrarArchivo();
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

	// Limpiamoss buffer
	this->buffer->clear();

	// Levantamos la metadata del archivo
	this->archivo->leerBloque(this->buffer, NUM_BLOQUE_METADATA);

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
	// Corroboramos que esté abierto el archivo
	if(!this->archivo->estaAbierto()) return;

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
	this->archivo->escribirBloque(this->buffer, NUM_BLOQUE_METADATA, 
		sizeof(*buffer));
}
