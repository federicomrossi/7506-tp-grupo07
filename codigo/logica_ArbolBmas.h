//
//  ArbolBmas.h
//	[ Insertar documentacion ]
//

#ifndef ARBOLBMAS_H
#define ARBOLBMAS_H


#include "VarBuffer.h"
#include "Indice.h"




/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


template < typename TipoClave >
class ArbolBmas
{

private:

	class Nodo : public Indice
	{
		int maxClaves;		// Numero maximo de claves en el nodo

		// Constructor
		Nodo(int maxClaves, int unico = 1);

		//
		int insertar(const TipoClave clave, int direccionRegistro);

		//
		int eliminar(const TipoClave clave, int direccionRegistro = -1);

		// Devuelve la mayor clave del nodo
		int claveMayor();

		//
		int particionar(Nodo *nodoNuevo);
	};

	Nodo raiz;				// Nodo de la raiz
	int altura;				// Altura del arbol
	int orden;				// Orden del arbol
	Nodo *Nodos[];			// Almacenador para rama
	VarBuffer archivo;		// Archivo de almacenamiento del arbol

	//
	Nodo* buscarHoja(const TipoClave clave);

	// Carga un nodo en memoria
	Nodo* cargarNodo(const int direccionRegistro);

	// Almacena un nodo en archivo
	int almacenarNodo(Nodo *nodo);

public:

	// Constructor
	ArbolBmas(int orden, int tamanioClave = sizeof(TipoClave), int unico = 1);

	// Destructor
	~ArbolBmas();

	// CONSIDERAR BORRAR ESTE METODO
	int iniciar(string nombre, int modo);

	// CONSIDERAR BORRAR ESTE METODO
	int crear(string nombre, int modo);

	// CONSIDERAR BORRAR ESTE METODO
	int cerrar();

	//
	int insertar(const TipoClave clave, const int direccionRegistro);

	//
	int eliminar(const TipoClave clave, const int direccionRegistro = -1);

	//
	int buscar(const TipoClave clave, const int direccionRegistro = -1);
};



/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/





#endif
