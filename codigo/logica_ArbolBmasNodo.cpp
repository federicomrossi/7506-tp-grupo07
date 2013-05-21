//
//  ArbolBmasNodo.cpp
//	[ Insertar documentacion ]
//


#include "logica_ArbolBmasNodo.h"
#include "fisica_ArchivoBloques.h"
#include "fisica_SerialBuffer.h"
#include "domain_RegistroGenerico.h"



/* ****************************************************************************
 * CONSTANTES
 * ***************************************************************************/

namespace {

	// Constantes para el buffer
	const int BUFFER_TAMANIO = 512;
}



/* ****************************************************************************
 * DEFINICIÓN DE LA ESTRUCTURA
 * ***************************************************************************/


// Constructor
Nodo::Nodo() 
{
	this->buffer = new SerialBuffer(BUFFER_TAMANIO);
}


// Destructor
Nodo::~Nodo() 
{
	// Liberamos la memoria utilizada para el buffer de serializacion
	delete this->buffer;
}


// Inicializa el nodo.
// PRE: 'numBloque' es el numero de bloque en el que se encuentra
// almacenado; 'nivel' es el nivel en el que se encuentra el nodo.
void Nodo::inicializar(uint numBloque, uint nivel)
{
	this->numBloque = numBloque;
	this->nivel = nivel;
	this->cantClaves = 0;
}

// Establece el numero de bloque del nodo. Se utiliza para setear
// el numero de bloque de un nodo existente, previo a realizar la
// carga de este a memoria.
void Nodo::setNumBloque(uint numBloque)
{
	this->numBloque = numBloque;
}


// Devuelve el numero de bloque en el que se encuentra el nodo
uint Nodo::getNumBloque()
{
	return this->numBloque;
}
