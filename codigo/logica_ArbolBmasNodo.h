//
//  ArbolBmasNodo.h
//	Clase abstracta que representa un Nodo del Arbol B+.
//


#ifndef ARBOLBMASNODO_H
#define ARBOLBMASNODO_H


#include <list>
#include "domain_RegistroGenerico.h"


// Definicion de tipo uint para utilizar nombre mas corto
typedef unsigned int uint; 



class ArbolBmasNodo
{

private:

	uint numBloque;				// Numero de bloque del nodo
	uint nivel;					// Nivel en el que se encuentra el nodo
	uint cantClaves;			// Cantidad actual de claves
	uint cantMaxClaves;			// Cantidad maxima de claves permitidas
	list< uint > claves;		// Claves de registros

public:
	
	// Constructor
	ArbolBmasNodo(uint numBloque, uint nivel, uint cantMaxClaves) : 
		numBloque(numBloque), nivel(nivel), cantMaxClaves(cantMaxClaves) { }

	// Inserta el registro en el nodo.
	// PRE: 'clave' es la clave a insertar; 'registro' es el registro
	// asociado a dicha clave.
	// POST: devuelve true si queda en overflow o false en caso contrario
	virtual bool insertar(uint clave, RegistroGenerico registro) = 0;
};

#endif
