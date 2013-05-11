/*
 * Block.cpp
 *
 *  Created on: May 4, 2013
 *      Author: rburdet
 */
#include "fisica_Block.h"
#include "Reg.h"

const int blockSize = 512; // DEBE SER CONFIGURABLE DESDE AFUERA !!!

Block::Block(BlockTable& aBlockTable): blockTable(aBlockTable) //primero tengo que llamar a este constructor
{
	blockCurrentSize=0;
	blockTable=aBlockTable;
	dispersionSize=0;
	blockAdress=0;
	maxBlockSize=blockCurrentSize;
	regsList= 0; //NULL
}

/*
 * en un bloque yo tengo que agregar un registro, y ademas tengo que agregar ese bloque a la lista de bloques
 * */


int Block::Insert(Reg & aReg){
	//si puedo agregar agrego
	if (blockCurrentSize + (aReg.getSize()) < maxBlockSize){
		blockCurrentSize=blockCurrentSize+ aReg.getSize();
		this->getRegList()->push_back(aReg);
		return (blockTable.saveBlock(this)); //si lo pude guardar, 1;
	}else {
		this->separate();
		return (blockTable.insert(aReg)); // Si lo puede guardar, 1
	}
}
/*Block::~Block() {
	// TODO Auto-generated destructor stub
} */
