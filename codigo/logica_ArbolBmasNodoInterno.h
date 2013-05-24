//
//  ArbolBmasNodoHoja.h
//	[ Insertar documentacion ]
//


#ifndef ARBOLBMAS_NODO_INTERNO_H
#define ARBOLBMAS_NODO_INTERNO_H


#include "fisica_ArchivoBloques.h"
#include "logica_ArbolBmasNodo.h"
#include "logica_ArbolBmasNodoInterno.h"
#include "logica_ArbolBmasNodoHoja.h"
#include "lib_ListaFija.h"


// Definicion de tipo uint para utilizar nombre mas corto
typedef unsigned int uint;




/* ****************************************************************************
 * DECLARACIÓN DE LA ESTRUCTURA
 * ***************************************************************************/


template < size_t MAX_HOJA, size_t MAX_INTERNO >
struct NodoInterno : public Nodo
{
	// Claves de registros
	ListaFija< uint, MAX_INTERNO + 1 > claves;

	// Referencias a hijos (se usa si es un nodo interno)
	ListaFija< uint, MAX_INTERNO + 2 > hijos;


	// Constructor
	NodoInterno();

	// Destructor
	~NodoInterno();	

	// Inserta el registro en el nodo.
	// PRE: 'clave' es la clave a insertar; 'registro' es el registro
	// asociado a dicha clave; 'archivo' es un puntero al archivo donde
	// se almacena el arbol; 'contBloques' es el contador de bloques del
	// arbol.
	// POST: devuelve true si queda en overflow o false en caso contrario
	virtual bool insertar(uint& clave, RegistroGenerico& registro, 
		ArchivoBloques *archivo, uint& contBloques);

	// Agrega una primer clave al nodo con sus respectivos hijos. Sirve
	// para inicializar un nuevo nodo luego de dividir nodos hijos.
	// PRE: 'clave' es la clave que tendra los hijos; 
	// POST: Se agregaron la clave y los hijos al nodo.
	void insertarHijosIniciales(uint clave, uint numBloqueIzq, 
		uint numBloqueDer);

	// Reparte su contenido con su nodoHermano, pasandole la mitad.
	// PRE: 'nodoHermano' es un nodo con el que se hara la division
	// POST: devuelve la clave del registro inferior de 'nodoHermano'
	virtual uint dividir(Nodo *nodoHermano);

	// Carga el nodo desde un archivo.
	// PRE: 'archivo' es donde se almacena el nodo que se desea cargar, el
	// cual se encuentra en el numero de bloque con el que fue inicializado.
	// POST: se han cargado todos los atributos internos del nodo
	virtual void cargar(ArchivoBloques *archivo);

	// Guarda el nodo en un archivo.
	// PRE: 'archivo' es donde se almacenaran los datos del nodo, los cuales
	// se guardaran en el numero de bloque con el cual fue inicializado.
	// POST: se guardo el estado del nodo en el archivo.
	virtual void guardar(ArchivoBloques *archivo);

	// Se imprime el nodo en la salida estandar con su contenido
	// FORMATO: "[nivel], [numero_bloque]: [hijo1]([clave1])..[hijoN]([claveN])
	// [hijoN+1] 
	virtual void imprimir(uint& nivelDelArbol, ArchivoBloques *archivo);
};




/* ****************************************************************************
 * DEFINICIÓN DE LA ESTRUCTURA
 * ***************************************************************************/


// Constructor
template < size_t MAX_HOJA, size_t MAX_INTERNO >
NodoInterno< MAX_HOJA, MAX_INTERNO >::NodoInterno()
{
	this->cantMaxClaves = MAX_INTERNO;
}


// Destructor
template < size_t MAX_HOJA, size_t MAX_INTERNO >
NodoInterno< MAX_HOJA, MAX_INTERNO >::~NodoInterno() { }


// Inserta el registro en el nodo.
// PRE: 'clave' es la clave a insertar; 'registro' es el registro
// asociado a dicha clave; 'archivo' es un puntero al archivo donde
// se almacena el arbol; 'contBloques' es el contador de bloques del
// arbol.
// POST: devuelve true si queda en overflow o false en caso contrario
template < size_t MAX_HOJA, size_t MAX_INTERNO >
bool NodoInterno< MAX_HOJA, MAX_INTERNO >::insertar(uint& clave, 
	RegistroGenerico& registro, ArchivoBloques *archivo, uint& contBloques)
{
	Nodo *nodo;

	if(this->nivel == 1)
		nodo = new NodoHoja< MAX_HOJA, MAX_INTERNO >;
	else
		nodo = new NodoInterno< MAX_HOJA, MAX_INTERNO >;

	// Iteramos sobre los hijos
	for(size_t i = 0; i < this->hijos.tamanio(); i++)
	{
		// Si llegamos al hijo final insertamos allí, pero si se encuentra
		// una clave mayor a la que se desea insertar, insertamos en el 
		// hijo izquierdo de la primer clave mayor que aparezca
		if(i == (this->hijos.tamanio()-1) || clave < this->claves[i])
		{
			// Cargamos el nodo en memoria
			nodo->setNumBloque(this->hijos[i]);
			nodo->cargar(archivo);

			// Insertamos la clave y el registro en el nodo, y verificamos
			// si se produjo overflow en este, en cual caso, accionaremos
			if(nodo->insertar(clave, registro, archivo, contBloques))
			{
				/* Se produjo overflow en el nodo */

				Nodo *nodoHermano;

				// Creamos nodo hermano
				if(this->nivel == 1)
					nodoHermano = new NodoHoja< MAX_HOJA, MAX_INTERNO >;
				else
					nodoHermano = new NodoInterno< MAX_HOJA, MAX_INTERNO >;
				
				// Incrementamos el contador de bloques del arbol
				contBloques++;
				// Inicializamos los datos del nodo hermano
				nodoHermano->inicializar(contBloques, nodo->nivel);

				// Dividimos el contenido entre nodo y nodo hermano e
				// insertamos la clave retornada a la lista de claves
				this->claves.insertar(nodo->dividir(nodoHermano), i);
				this->cantClaves++;

				// Agregamos el numero de bloque del nodo hermano a la lista
				// de hijos
				this->hijos.insertar(nodoHermano->getNumBloque(), i+1);

				nodo->guardar(archivo);
				nodoHermano->guardar(archivo);

				delete nodo;
				delete nodoHermano;

				// Verificamos si hay overblow y devolvemos true o false
				if(this->claves.tamanio() > this->cantMaxClaves) return true;
				return false;
			}

			// Escribimos el nodo en el archivo
			nodo->guardar(archivo);

			break;
		}
	}

	delete nodo;

	// Verificamos si entro en overflow y devolvemos de acuerdo a esto
	if(this->cantClaves > this->cantMaxClaves) return true;
	return false;
}


// Agrega una primer clave al nodo con sus respectivos hijos. Sirve
// para inicializar un nuevo nodo luego de dividir nodos hijos.
// PRE: 'clave' es la clave que tendra los hijos; 
// POST: Se agregaron la clave y los hijos al nodo.
template < size_t MAX_HOJA, size_t MAX_INTERNO >
void NodoInterno< MAX_HOJA, MAX_INTERNO >::insertarHijosIniciales(uint clave,
		uint numBloqueIzq, uint numBloqueDer)
{
	this->claves.insertarUltimo(clave);
	this->hijos.insertarUltimo(numBloqueIzq);
	this->hijos.insertarUltimo(numBloqueDer);
}


// Reparte su contenido con su nodoHermano, pasandole la mitad.
// PRE: 'nodoHermano' es un nodo con el que se hara la division
// POST: devuelve la clave del registro inferior de 'nodoHermano'
template < size_t MAX_HOJA, size_t MAX_INTERNO >
uint NodoInterno< MAX_HOJA, MAX_INTERNO >::dividir(Nodo *nodoHermano)
{
	// Casteamos para poder tratarlo como nodo hoja
	NodoInterno *nodoInternoHermano = (NodoInterno< MAX_HOJA, MAX_INTERNO >*)
		nodoHermano;

	// Calculamos posicion de corte
	int pos_corte = (this->claves.tamanio() / 2) + 1;

	// Transferimos elementos de la segunda mitad hacia las listas del
	// nodo hermano
	this->claves.transferir(nodoInternoHermano->claves, pos_corte, 
		this->claves.tamanio() - 1);
	this->hijos.transferir(nodoInternoHermano->hijos, pos_corte,
		this->hijos.tamanio() - 1);

	// Tomamos la clave que subira hacia el nodo padre y la borramos de la
	// lista de claves del nodo actual
	uint clave_subir = this->claves.verUltimo();
	this->claves.eliminarUltimo();

	// Actualizamos cantidad de claves en nodos
	this->cantClaves = this->claves.tamanio();
	nodoInternoHermano->cantClaves = nodoInternoHermano->claves.tamanio();

	return clave_subir;
}


// Carga el nodo desde un archivo.
// PRE: 'archivo' es donde se almacena el nodo que se desea cargar, el
// cual se encuentra en el numero de bloque con el que fue inicializado.
// POST: se han cargado todos los atributos internos del nodo
template < size_t MAX_HOJA, size_t MAX_INTERNO >
void NodoInterno< MAX_HOJA, MAX_INTERNO >::cargar(ArchivoBloques *archivo)
{
	this->buffer->clear();
	archivo->leerBloque(this->buffer->getBuffer(), this->numBloque);

	uint numBloque, nivel, cantClaves, cantMaxClaves;

	this->buffer->unpack(&numBloque);
	this->buffer->unpack(&nivel);
	this->buffer->unpack(&cantClaves);
	this->buffer->unpack(&cantMaxClaves);

	this->numBloque = numBloque;
	this->nivel = nivel;
	this->cantClaves = cantClaves;
	this->cantMaxClaves = cantMaxClaves;

	// Deserializamos las claves
	this->claves.deserializar(buffer);
	// Deserializamos los registros
	this->hijos.deserializar(buffer);
}


// Guarda el nodo en un archivo.
// PRE: 'archivo' es donde se almacenaran los datos del nodo, los cuales
// se guardaran en el numero de bloque con el cual fue inicializado.
// POST: se guardo el estado del nodo en el archivo.
template < size_t MAX_HOJA, size_t MAX_INTERNO >
void NodoInterno< MAX_HOJA, MAX_INTERNO >::guardar(ArchivoBloques *archivo)
{
	this->buffer->clear();

	uint numBloque = this->numBloque;
	uint nivel = this->nivel;
	uint cantClaves = this->cantClaves;
	uint cantMaxClaves = this->cantMaxClaves;

	// Serializamos atributos
	this->buffer->pack(&numBloque, sizeof(uint));
	this->buffer->pack(&nivel, sizeof(uint));
	this->buffer->pack(&cantClaves, sizeof(uint));
	this->buffer->pack(&cantMaxClaves, sizeof(uint));

	// Serializamos las claves
	this->claves.serializar(buffer);
	// Serializamos los registros
	this->hijos.serializar(buffer);

	// Escribimos bloque y limpiamos buffer
	archivo->escribirBloque(this->buffer->getBuffer(), this->numBloque);
	this->buffer->clear();
}


// Se imprime el nodo en la salida estandar con su contenido
// FORMATO: "[nivel], [numero_bloque]: [hijo1]([clave1])...[hijoN]([claveN])
// [hijoN+1] 
template < size_t MAX_HOJA, size_t MAX_INTERNO >
void NodoInterno< MAX_HOJA, MAX_INTERNO >::imprimir(uint& nivelDelArbol, 
	ArchivoBloques *archivo)
{
	// Tabulamos de acuerdo al nivel
	int tabs = nivelDelArbol - this->nivel;
	std::cout << std::string(tabs, '\t');
	std::cout << this->nivel << ", " << this->numBloque << ": ";

	// Iteramos sobre las claves
	for(size_t i = 0; i < this->claves.tamanio(); i++)
	{
		std::cout << this->hijos[i];
		std::cout << "(" << this->claves[i] << ")";
	}

	std::cout << this->hijos[this->hijos.tamanio() - 1] << std::endl;

	// Imprimimos hijos
	for(size_t i = 0; i < this->hijos.tamanio(); i++)
	{
		Nodo* hijo = 0;

		if(this->nivel == 1)
			hijo = new NodoHoja< MAX_HOJA, MAX_INTERNO >;
		else
			hijo = new NodoInterno< MAX_HOJA, MAX_INTERNO >;

		hijo->setNumBloque(this->hijos[i]);
		hijo->cargar(archivo);
		hijo->imprimir(nivelDelArbol, archivo);

		delete hijo;
	}
}

#endif
