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

#include "fisica_Block.h"
#include "fisica_ArchivoBloques.h"
#include "logica_HashExtensible.h"
#include "logica_Reg.h"

using namespace std;
class BlockTable{
	public:
		BlockTable();	// Cuando se crea la tabla de bloques, se crea vacia.
		int insert(Reg&); // A su vez llama al insertar del bloque
		int insertBlock(int blockPos,int newBlockReference,int td); //En la posicion blockPos de la tabla pongo la nueva ref.
		int saveBlock(Block * aBlock); //Cuando agrego algo a un bloque lo tengo que guardar
		int resizeTable(); //Duplica el tamanio de la tabla
		int duplicateTable(); // copia la primera parte de la tabla, en la segunda
		int search(Reg&); // Busca el registro atraves de la funcion hash
		int open(char* fileName); //Abre el archivo donde tengo la tabla
		int close(); // Lo cierra
		int getSize(); //Devuelve el tamanio de la tabla
	//	int getBlock(Block& aBlock , int blockAdress); //se copia al bloque en blockAdress en el bloque nuevo vacio aBlock
		bool canAddBlock(Block* aBlock); //Tengo referencias libres? true significa que no hace falta duplicar
		int redisperse(Block* anOldBlock,Block* aNewBlock); //redisperso los registros del bloque viejo al bloque nuevo
		int size;
		int *blockReferences;
		const char* fileName; //El archivo va a ser siempre el mismo, configurable en momento de compilacion
		ArchivoBloques* archivo;
};

#endif
