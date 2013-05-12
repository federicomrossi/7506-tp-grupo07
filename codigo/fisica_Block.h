/*
*	Block.h
*
*	Esta clase es la mas importante dentro del hash. Incluye informacion vital para el funcionamiento del mismo.
Esta informacion incluye:
	Posicion del bloque en el archivo
	Tamanio de dispersion del bloque
	Los registros que contiene cada bloque
*
*
*/

#ifndef BLOCK_H_
#define BLOCK_H_

#include "logica_BlockTable.h"
#include "logica_Reg.h"
#include <list>

using namespace std;
/*
 * El tamanio de registros en un bloque debe poder ser configurable desde afuera
 * ver bien !!!
 * */

class Block {
	public:
		Block(BlockTable& aBlockTable); //Creo un bloque en una tabla de bloques. Inicialmente el tamanio es 0

		/* Agrego un registro a la cubeta, los resultados posibles son: 0 sino se agrego, 1 si se agrego, 2 si se duplico el tamanio.
			*/
		int Insert(Reg & aReg);

		/* Si el bloque queda en overflow tengo que crear otro para luego redistribuir los registros*/
		Block* createNew(int newDispersionSize);

		int separate(); //crea un nuevo bloque, redispersando y cambiando los tamanios de dispersion de ambos bloques

		/* Cuando se produce un overflow, tengo que redispersar los registros */
		int redistribute(Block * aNewBlock);

		/* Cuando se duplica la tabla, o un bloque queda en overflow pero con mas de 1 referencia en la tabla entonces es necesario cambiar el tamanio de dispersion del bloque
		 * Devuelve el nuevo tamanio de dispersion*/

		int changeDispersionSize();

		/* Cuando un bloque queda en overflow, necesito buscar el proximo bloque en donde pueda redispersar,  */
		int getBlockInTable();
		/* Para persistir a un bloque */
		
		list<Reg>* getRegList();

	protected:
		int blockCurrentSize;
		int maxBlockSize;
		BlockTable& blockTable;
		int blockAdress;
		int dispersionSize;
		list<Reg>* regsList;

};
#endif
