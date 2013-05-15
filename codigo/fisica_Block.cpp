/*
 * Block.cpp
 *
 *  Created on: May 4, 2013
 *      Author: rburdet
 */
#include "fisica_Block.h"
#include "logica_HashExtensible.h"
#include "logica_Reg.h"

using namespace std;

Block::Block(int dispersionSize,int blockAdress)/*: blockTable(aBlockTable) *///primero tengo que llamar a este constructor
{
	blockCurrentSize=0;
	//blockTable=aBlockTable;
	this->dispersionSize=dispersionSize;
	this->blockAdress=blockAdress;
	maxBlockSize=blockCurrentSize;
	blockNum++;
}

/*
 * en un bloque yo tengo que agregar un registro, y ademas tengo que agregar ese bloque a la lista de bloques
 * */


int Block::Insert(Reg & aReg){
	//si puedo agregar agrego
	/*if (blockCurrentSize + (aReg.getSize()) < maxBlockSize){
		blockCurrentSize=blockCurrentSize+ aReg.getSize();*/  // de esto se esta ocupando el insertEasy
		this->getRegList().push_back(aReg);
		return 0; // cambiar
	//	return (blockTable.saveBlock(this)); //si lo pude guardar, 1;
	/*}else {
		this->separate();
		return 1 ; //cambiar
	//	return (blockTable.insert(aReg)); // Si lo puede guardar, 1
	}*/ //														de esto tmb
}

void Block::changeDispersionSize(int newDispersionSize){
	this->dispersionSize=newDispersionSize;
}
list<Reg> Block::getRegList(){
	return this->regsList;
}

int Block::separate(){
	return 0; //hacer
}

int Block::getBlockAdress(){
	return blockAdress;
}

bool Block::easyInsert(Reg& aReg){
	return (aReg.getSize()+ blockCurrentSize < MAX_BLOCK_SIZE);
}
	/*
	Block* Block::createNew(int newDispersionSize){
		Block* aNewBlock = new Block(newDispersionSize);
	}
	*/
/*
int Block::redistribute(Block* aNewBlock,int tableSize){
		list<Reg>::iterator it;
		HashExtensible *aHash= new HashExtensible();
		for (it = this->getRegList().begin(); it != this->getRegList().end() ; it++) {
			int pos = aHash->doHash((*it).getId(),tableSize);
			this->Insert(*it);	//SEGUIR CON ESTOOOO
		}
		return 0; //cambiar
}*/ //LA REDISPERSION LA TENDRIA QUE SABER HACER LA TABLA, NO EL BLOQUE

/*Block::~Block() {
}*/
int Block::blockNum=0;
