//
//  ArbolBmasNodo.h
//	[ Insertar documentacion ]
//


#ifndef ARBOLBMAS_NODO_H
#define ARBOLBMAS_NODO_H


class ArchivoBloques;
class SerialBuffer;
class RegistroGenerico;

// Definicion de tipo uint para utilizar nombre mas corto
typedef unsigned int uint; 




/* ****************************************************************************
 * DECLARACIÓN DE LA ESTRUCTURA
 * ***************************************************************************/


struct Nodo
{
	SerialBuffer *buffer;			// Buffer utilizado para serializacion
	uint numBloque;					// Numero de bloque del nodo
	uint nivel;						// Nivel en el que se encuentra el nodo
	uint cantMaxClaves;				// Cantidad maxima de claves permitidas

	// Constructor
	Nodo();

	// Destructor
	virtual ~Nodo();

	// Inicializa el nodo.
	// PRE: 'numBloque' es el numero de bloque en el que se encuentra
	// almacenado; 'nivel' es el nivel en el que se encuentra el nodo.
	void inicializar(uint numBloque, uint nivel);

	// Establece el numero de bloque del nodo. Se utiliza para setear
	// el numero de bloque de un nodo existente, previo a realizar la
	// carga de este a memoria.
	void setNumBloque(uint numBloque);

	// Devuelve el numero de bloque en el que se encuentra el nodo.
	uint getNumBloque();

	// Inserta el registro en el nodo.
	// PRE: 'clave' es la clave a insertar; 'registro' es el registro
	// asociado a dicha clave; 'archivo' es un puntero al archivo donde
	// se almacena el arbol; 'contBloques' es el contador de bloques del
	// arbol.
	// POST: devuelve true si queda en overflow o false en caso contrario
	virtual bool insertar(uint& clave, RegistroGenerico& registro, 
		ArchivoBloques *archivo, uint& contBloques) = 0;

	// Busca un registro.
	// PRE: 'clave' es la clave o id asociado al registro a buscar; 'registro'
	// es un puntero a un almacenador en donde se insertara el resultado de la
	// busqueda.
	// POST: Si se encontró el registro, se devuelve true y se almacena en
	// 'registro' al mismo. Si no se encontró, se devuelve false y se almacena
	// en 'registro' el registro superior mas proximo al buscado.
	virtual bool buscar(const uint clave, RegistroGenerico & registro, 
		ArchivoBloques *archivo) = 0;

	// Reparte su contenido con su nodoHermano, pasandole la mitad.
	// PRE: 'nodoHermano' es un nodo con el que se hara la division
	// POST: devuelve la clave del registro inferior de 'nodoHermano'
	virtual uint dividir(Nodo *nodoHermano) = 0;

	// Carga el nodo desde un archivo.
	// PRE: 'archivo' es donde se almacena el nodo que se desea cargar, el
	// cual se encuentra en el numero de bloque con el que fue inicializado.
	// POST: se han cargado todos los atributos internos del nodo
	virtual void cargar(ArchivoBloques *archivo) = 0;

	// Guarda el nodo en un archivo.
	// PRE: 'archivo' es donde se almacenaran los datos del nodo, los cuales
	// se guardaran en el numero de bloque con el cual fue inicializado.
	// POST: se guardo el estado del nodo en el archivo.
	virtual void guardar(ArchivoBloques *archivo) = 0;

	// Se imprime el nodo en la salida estandar con su contenido
	virtual void imprimir(uint& nivelDelArbol, ArchivoBloques *archivo) = 0;
};

#endif
