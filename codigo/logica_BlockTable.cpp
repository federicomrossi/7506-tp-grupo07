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
	//TODO:Cambiar esto, hay que crear la tabla con los datos de un archivo donde tenga la tabla
	string name = HASH_BLOCK_TABLE_FILE;
	this->open(name.c_str());
	this->hidratateBlockTable();

	blockReferences = new int [1];
}

void BlockTable::hidratateBlockTable(){
	this->archivo->seekg(0,this->archivo->end);
	int length= this->archivo->tellg();
	this->archivo->seekg(0,this->archivo->beg);
	this->archivo->read((char*)this->blockReferences,length);
	this->size=length/sizeof(int);

}
int BlockTable::open(const char * fileName){
	this->archivo->open(fileName,ios::in|ios::out|ios::binary);
	if(!this->archivo){
		return 0;
	}
	return 1;
}

int BlockTable::search(Reg& aReg){
	int pos=HashExtensible::doHash(aReg.getId(),this->getSize());
	//Aca ya tengo que tener la tabla en memoria, siempre supongo que entra toda la tabla en memoria
	int blockNumber=this->blockReferences[pos];
	Block *aBlock = new Block(this->getSize(),blockNumber);
	aBlock->getArchivo()->leerBloque((void*)aBlock,blockNumber);
	aBlock->search(aReg);
	return 0;

}

int BlockTable::insert(Reg & aReg){

	HashExtensible::doHash(aReg.getId(),this->getSize());// TODO: Probar si esto funciona
	int pos = HashExtensible::doHash(aReg.getId(),this->getSize());
	int tmpBlockNumber = this->blockReferences[pos];
	Block *tmpBlock=new Block(this->getSize(),tmpBlockNumber);
	tmpBlock->open(HASH_BLOCK_FILE);
	//this->archivo = new ArchivoBloques(MAX_BLOCK_SIZE,".hashBlock");
	//archivo->abrirArchivo();


	//tmpBlock->getArchivo()->leerBloque((void*) &metadata,tmpBlockNumber);
	//A este bloque lo tengo que hidratar,tener en cuenta que en un archivo se van a guardar solo los registros del bloque
	//mientras que en otro archivo se va a guardar una tira con todas las posiciones de bloques

	if (tmpBlock->easyInsert(aReg)){
		tmpBlock->Insert(aReg);
		tmpBlock->getArchivo()->escribirBloque((void*)tmpBlock,tmpBlock->getBlockNum(),MAX_BLOCK_SIZE);
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
		tmpBlock->getArchivo()->escribirBloque((void*)tmpBlock,tmpBlock->getBlockNum(),tmpBlock->getCurrentSize());
		anotherBlock->getArchivo()->escribirBloque((void*)anotherBlock,anotherBlock->getBlockNum(),anotherBlock->getCurrentSize());
		this->insert(aReg);
		// Llamar recursivametne this->insert(aReg)
	}
	//TODO: ESTO de aca
	//archivo->leerBloque((void*) tmpBlock,blockNumber); No esta implementado
	//archivo->escribirBloque((void*)tmpBlock,blockNumber); No esta implementado

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

BlockTable::~BlockTable(){
	//
	this->archivo->write((char*)this->blockReferences,sizeof(int)*this->size);
	//this->archivo->escribirBloque((void*)this,0,100);//Aca tendria que tirar la tabla en un archivo, y nada mas.
													 //el archivo no tiene bloques nada
	this->archivo->close();
	delete []blockReferences;
}
