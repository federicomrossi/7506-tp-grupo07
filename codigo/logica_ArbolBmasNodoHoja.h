//
//  ArbolBmasNodoHoja.h
//	[ Insertar documentacion ]
//


#ifndef ARBOLBMAS_NODO_HOJA_H
#define ARBOLBMAS_NODO_HOJA_H


#include "fisica_ArchivoBloques.h"
#include "logica_ArbolBmasNodo.h"
#include "lib_ListaFija.h"


// Definicion de tipo uint para utilizar nombre mas corto
typedef unsigned int uint; 




/* ****************************************************************************
 * DECLARACIÓN DE LA ESTRUCTURA
 * ***************************************************************************/


template < size_t MAX_HOJA, size_t MAX_INTERNO >
struct NodoHoja : public Nodo
{
	// Referencia al nodo hermano
	uint nodoHermano;
	// Claves de registros
	ListaFija< uint, MAX_INTERNO + 1 > claves;
	// Lista de registros (se usa si es un nodo hoja)
	ListaFija< RegistroGenerico, MAX_HOJA + 1 > registros;


	// Constructor
	NodoHoja();

	// Destructor
	~NodoHoja();	

	// Inserta el registro en el nodo.
	// PRE: 'clave' es la clave a insertar; 'registro' es el registro
	// asociado a dicha clave; 'archivo' es un puntero al archivo donde
	// se almacena el arbol; 'contBloques' es el contador de bloques del
	// arbol.
	// POST: devuelve true si queda en overflow o false en caso contrario
	virtual bool insertar(uint& clave, RegistroGenerico& registro, 
		ArchivoBloques *archivo, uint& contBloques);

	// Reparte su contenido con su nodoHermano, pasandole la mitad.
	// PRE: 'nodoHermano' es un nodo con el que se hara la division
	// POST: devuelve la clave del registro inferior de 'nodoHermano'
	virtual uint dividir(Nodo *nodoHermano);


	// Se imprime el nodo en la salida estandar con su contenido.
	// FORMATO: "[nivel], [numero_bloque]: ([clave1])..([claveN])[nodo_hermano]
	virtual void imprimir(uint& nivelDelArbol);
};




/* ****************************************************************************
 * DEFINICIÓN DE LA ESTRUCTURA
 * ***************************************************************************/


// Constructor
template < size_t MAX_HOJA, size_t MAX_INTERNO >
NodoHoja< MAX_HOJA, MAX_INTERNO >::NodoHoja()
{
	this->cantMaxClaves = MAX_HOJA;
}


// Destructo
template < size_t MAX_HOJA, size_t MAX_INTERNO >
NodoHoja< MAX_HOJA, MAX_INTERNO >::~NodoHoja() 
{

}

// Inserta el registro en el nodo.
// PRE: 'clave' es la clave a insertar; 'registro' es el registro
// asociado a dicha clave; 'archivo' es un puntero al archivo donde
// se almacena el arbol; 'contBloques' es el contador de bloques del
// arbol.
// POST: devuelve true si queda en overflow o false en caso contrario
template < size_t MAX_HOJA, size_t MAX_INTERNO >
bool NodoHoja< MAX_HOJA, MAX_INTERNO >::insertar(uint& clave, 
	RegistroGenerico& registro, ArchivoBloques *archivo, uint& contBloques)
{
	for(size_t i = 0; i < this->claves.tamanio(); i++)
	{
		if(this->claves[i] == clave)
			throw "ERROR: Claves iguales en arbol.";

		// Si la clave es mas grande que el actual, insertamos en ese lugar
		else if(this->claves[i] > clave)
		{
			this->claves.insertar(clave, i);
			this->registros.insertar(registro, i);
			break;
		}
		// Si llegamos a la ultima posicion y no hubo elemento mayor,
		// insertamos clave y registro al final de las listas.
		else if(i == (claves.tamanio() - 1))
		{
			this->claves.insertarUltimo(clave);
			this->registros.insertarUltimo(registro);
		}
	}

	this->cantClaves++;

	// Corroboramos si entro en overflow y devolvemos de acuerdo a esto
	if(this->cantClaves > this->cantMaxClaves) return true;
	return false;
}


// Reparte su contenido con su nodoHermano, pasandole la mitad.
// PRE: 'nodoHermano' es un nodo con el que se hara la division
// POST: devuelve la clave del registro inferior de 'nodoHermano'
template < size_t MAX_HOJA, size_t MAX_INTERNO >
uint NodoHoja< MAX_HOJA, MAX_INTERNO >::dividir(Nodo *nodoHermano)
{
	// Casteamos para poder tratarlo como nodo hoja
	NodoHoja *nodoHojaHermano = (NodoHoja< MAX_HOJA, MAX_INTERNO >*)
		nodoHermano;

	// Calculamos posicion de corte
	int pos_corte = this->claves.tamanio() / 2;

	// Transferimos elementos de la segunda mitad hacia las listas del
	// nodo hermano
	this->claves.transferir(nodoHojaHermano->claves, pos_corte, 
		this->claves.tamanio() - 1);
	this->registros.transferir(nodoHojaHermano->registros, pos_corte,
		this->registros.tamanio() - 1);

	// Apuntamos al nodo hermano
	this->nodoHermano = nodoHojaHermano->numBloque;

	// Actualizamos cantidad de claves en nodos
	this->cantClaves = this->claves.tamanio();
	nodoHojaHermano->cantClaves = nodoHojaHermano->claves.tamanio();

	// Retornamos la clave menor del nodo hermano
	return nodoHojaHermano->claves.verPrimero();
}


// Se imprime el nodo en la salida estandar con su contenido.
// FORMATO: "[nivel], [numero_bloque]: ([clave1])...([claveN])[nodo_hermano] 
template < size_t MAX_HOJA, size_t MAX_INTERNO >
void NodoHoja< MAX_HOJA, MAX_INTERNO >::imprimir(uint& nivelDelArbol)
{
	// Tabulamos de acuerdo al nivel
	std::cout << std::string((nivelDelArbol - this->nivel), '\t');
	std::cout << this->nivel << ", " << this->numBloque << ": ";

	// Iteramos sobre las claves
	for(size_t i = 0; i < this->claves.tamanio(); i++)
		std::cout << "(" << this->claves[i] << ")";

	std::cout << this->nodoHermano << std::endl;

	return;
}

#endif
