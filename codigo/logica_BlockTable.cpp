/*
 * BlockTable.cpp
 *
 *  Created on: May 11, 2013
 *      Author: rburdet
 */

/*
 * DECLARACION DE CONSTANTES
 */

namespace{
	const int MAX_BLOCK_SIZE= 512; //Esto debe ser configurable
}
#include "logica_BlockTable.h"

BlockTable::BlockTable() {
	size=1;
	blockReferences[0]=0;
}

int BlockTable::insert(Reg & aReg){

	HashExtensible *aHash = new HashExtensible();
	int pos = aHash->doHash(aReg.getId(),this->getSize());
	int tmpBlockReference = this->blockReferences[pos];
	this->archivo = new ArchivoBloques(MAX_BLOCK_SIZE,".hashBlock");
	archivo->abrirArchivo();
	Block *tmpBlock=new Block(this->getSize(),tmpBlockReference);
	//archivo->leerBloque((void*) tmpBlock,tmpBlockReference); No esta implementado
	//A este bloque lo tengo que hidratar,tener en cuenta que en un archivo se van a guardar solo los registros del bloque
	//mientras que en otro archivo se va a guardar una tira con todas las posiciones de bloques
	int lastFilePos= 100; // HARDCODEADA CABEZA

	if (tmpBlock->easyInsert(aReg))
		tmpBlock->Insert(aReg);
	else {
		// la posicion del nuevo bloque va a ser al final del archivo

		Block * anotherBlock = new Block(tmpBlock->getDispersionSize()*2,lastFilePos); //HARDCODEADA CABEZA

		if (canAddBlock(tmpBlock)){
			insertBlock(pos,lastFilePos);
			tmpBlock->redistribute(anotherBlock,this->getSize());
		}else{
			//duplicar la tabla
		}
	}
	//archivo->leerBloque((void*) tmpBlock,blockNumber); No esta implementado
	tmpBlock->Insert(aReg);
	//archivo->escribirBloque((void*)tmpBlock,blockNumber); No esta implementado

	return 0;
}

int BlockTable::saveBlock(Block * aBlock){
	//Aca tengo que meterme en el archivo y guardarlo donde va
	return 0;
}

int BlockTable::getSize(){
	return size;
}

bool BlockTable::canAddBlock(Block* aBlock){
	return (aBlock->getDispersionSize()==this->getSize());
}

int BlockTable::insertBlock(int blockPos,int newBlockReference){
	return this->blockReferences[blockPos]=newBlockReference;
}
