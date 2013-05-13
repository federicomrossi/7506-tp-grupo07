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

}

int BlockTable::insert(Reg & aReg){
	HashExtensible *aHash = new HashExtensible();
	int pos = aHash->doHash(aReg.getId(),this->getSize());
	int blockNumber = this->blockReferences[pos];
	this->archivo = new ArchivoBloques(MAX_BLOCK_SIZE,".hashBlock");
	archivo->abrirArchivo();
	Block *tmpBlock;
	//archivo->leerBloque((void*) tmpBlock,blockNumber); No esta implementado
	if (this->getSize()+aReg.getSize()<MAX_BLOCK_SIZE){
		tmpBlock->getRegList();

		//archivo->escribirBloque((void*)tmpBlock,blockNumber); No esta implementado
	}
	return 0; //hacer
}

int BlockTable::saveBlock(Block * aBlock){
	//Aca tengo que meterme en el archivo y guardarlo donde va
	return 0;
}

int BlockTable::getSize(){
	return size;
}
