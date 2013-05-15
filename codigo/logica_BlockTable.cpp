/*
 * BlockTable.cpp
 *
 *  Created on: May 11, 2013
 *      Author: rburdet
 */


#include <string.h>
#include "logica_BlockTable.h"
#include "config.h"

BlockTable::BlockTable() {
	size=1;
	blockReferences = new int [1];
}

int BlockTable::insert(Reg & aReg){

	HashExtensible *aHash = new HashExtensible(); // TODO: pasarlo a una funcion
	//HashExtensible::doHash(aReg.getId(),this->getSize()); TODO: Metodo estatico,  no instanciar pelotudeces
	int pos = aHash->doHash(aReg.getId(),this->getSize());
	int tmpBlockNumber = this->blockReferences[pos];
	this->archivo = new ArchivoBloques(MAX_BLOCK_SIZE,".hashBlock");
	archivo->abrirArchivo();
	Block *tmpBlock=new Block(this->getSize(),tmpBlockNumber);
	//archivo->leerBloque((void*) tmpBlock,tmpBlockReference); No esta implementado
	//A este bloque lo tengo que hidratar,tener en cuenta que en un archivo se van a guardar solo los registros del bloque
	//mientras que en otro archivo se va a guardar una tira con todas las posiciones de bloques

	if (tmpBlock->easyInsert(aReg)){
		tmpBlock->Insert(aReg);
		archivo->escribirBloque((void*)tmpBlock,tmpBlock->getBlockNum(),MAX_BLOCK_SIZE);
	}
	else {
		// la posicion del nuevo bloque va a ser al final del archivo
		int lastBlockNum=0; //TODO: el numero de bloque se guarda en otro archivo


		Block * anotherBlock = new Block(tmpBlock->duplicateDispersionSize(),lastBlockNum+1); //HARDCODEADA CABEZA


		//si no tengo referencias repetidas tengo que duplicar la tabla
		if (! canAddBlock(tmpBlock)){
			duplicateTable();
		}

		insertBlock(pos,lastBlockNum+1,tmpBlock->getDispersionSize());
		redisperse(tmpBlock,anotherBlock);
		archivo->escribirBloque((void*)tmpBlock,tmpBlock->getBlockNum(),tmpBlock->getCurrentSize());
		archivo->escribirBloque((void*)anotherBlock,anotherBlock->getBlockNum(),anotherBlock->getCurrentSize());
		this->insert(aReg);
		// Llamar recursivametne this->insert(aReg)
	}
	//TODO: ESTO de aca
	//archivo->leerBloque((void*) tmpBlock,blockNumber); No esta implementado
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
	return (aBlock->getDispersionSize()!=this->getSize());
}

void BlockTable::insertBlock(int blockPos,int newBlockPos,int td){
	for (int i = blockPos; i < this->getSize(); i+=td) {
		blockReferences[i]=newBlockPos;
	}
	for (int i = blockPos-td; i >= 0; i-=td) {
		blockReferences[i]=newBlockPos;
	}
}

void BlockTable::redisperse(Block* anOldBlock, Block* aNewBlock){
	HashExtensible* aHash= new HashExtensible();
	list<Reg>::iterator it;
	list<Reg> tmpList;

	for (it = anOldBlock->getRegList().begin(); it != anOldBlock->getRegList().end() ; it++) {
		int pos = aHash->doHash((*it).getId(),this->getSize());
		int blockNum = this->blockReferences[pos];
		if( anOldBlock->getBlockNum() == blockNum )
			tmpList.push_back((*it));
		else
			aNewBlock->Insert((*it));
	}

	anOldBlock->setList(tmpList); //cabeza
}



void BlockTable::duplicateTable(){
	int newBlockTableSize = size *2;
	int *tmpBlockReference = new int [newBlockTableSize];
	for (int i = 0; i < size ; i++) {
		tmpBlockReference[i] = blockReferences[i];
		tmpBlockReference[2*i] = blockReferences[i];
	}
	delete blockReferences;
	blockReferences=tmpBlockReference;
}

