/*
 * BlockTable.h
 *
 *  Created on: May 4, 2013
 *      Author: rburdet
 */

/*
 *   Esta clase es la encargada de manejar las referencias a bloques.
 *	Al agregar un registro, se le aplica una funcion de dispersion, el valor que retorne
 *	esa funcion de dispersion sera la posicion en la tabla.
 *	En cada posicion de la tabla se encuentra una referencia a un bloque en un archivo
 *	de bloques.
 *
 * */

#ifndef BLOCKTABLE_H_
#define BLOCKTABLE_H_

#include "logica_Reg.h"
#include "fisica_Block.h"

using namespace std;

class BlockTable{
	BlockTable();	// Cuando se crea la tabla de bloques, se crea vacia.
	int insert(Reg&); // A su vez llama al insertar del bloque
	int insertBlock(int blockReference);
	int saveBlock(Block * aBlock); //Cuando agrego algo a un bloque lo tengo que guardar
	int resizeTable(BlockTable&); //Duplica el tamanio de la tabla
	int duplicateTable(BlockTable&); // copia la primera parte de la tabla, en la segunda
	int search(Reg&); // Busca el registro atraves de la funcion hash
	int open(char* fileName); //Abre el archivo donde tengo la tabla
	int close(); // Lo cierra

//	int getBlock(Block& aBlock , int blockAdress); //se copia al bloque en blockAdress en el bloque nuevo vacio aBlock


	protected:
		int size;
		int blockReferences[];
		const char* fileName; //El archivo va a ser siempre el mismo, configurable en momento de compilacion
};

#endif
