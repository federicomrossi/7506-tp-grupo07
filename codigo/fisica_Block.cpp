/*
 * Block.cpp
 *
 *  Created on: May 4, 2013
 *      Author: rburdet
 */
#include "fisica_Block.h"
#include "logica_HashExtensible.h"
#include "logica_Reg.h"
#include "config.h"

using namespace std;

//TODO: hidratar bloque

Block::Block(int dispersionSize,int blockAdress){
	//TODO:revisar que se use all lo que esta aca
	blockCurrentSize=0;
	this->dispersionSize=dispersionSize;
	//this->blockAdress=blockAdress; TODO: Como hago para laburar con el num de bloque?
	maxBlockSize=MAX_BLOCK_SIZE;
	blockNum++;
}

/*
 * en un bloque yo tengo que agregar un registro, y ademas tengo que agregar ese bloque a la lista de bloques
 * */


int Block::Insert(Reg & aReg){
		this->blockCurrentSize+=aReg.getSize();
		this->getRegList().push_back(aReg);
		return 0; // cambiar
}

void Block::changeDispersionSize(int newDispersionSize){
	this->dispersionSize=newDispersionSize;
}
list<Reg> Block::getRegList(){
	return this->regsList;
}

int Block::getBlockNum(){
	return this->blockNum;
}

int Block::duplicateDispersionSize(){
	return (this->dispersionSize*=2);
}

int Block::getDispersionSize(){
	return dispersionSize;
}


// TODO: SE ELIMINA?
int Block::separate(){
	return 0; //hacer
}

int Block::getCurrentSize(){
	return this->blockCurrentSize;
}

/* TODO: SE USA  ? ? ?
int Block::getBlockAdress(){
	return blockAdress;
}*/

bool Block::easyInsert(Reg& aReg){
	return (aReg.getSize()+ blockCurrentSize < MAX_BLOCK_SIZE);
}

void Block::setList(list<Reg> newRegList){
	this->regsList=newRegList;
}

int Block::search(Reg& regToLook){
	list<Reg>::iterator it;
	for (it = regsList.begin(); it != regsList.end(); it++){
		if ((*it).getId()==regToLook.getId()){
			regToLook.setFileAdress((*it).getFileAdress());
			//El size es siempre el mismo
			return ((*it).getFileAdress());
		}
	}
	return 0;
}

void Block::open(const char* fileName){
	this->archivo = new ArchivoBloques(MAX_BLOCK_SIZE, fileName);

	// Inicializamos el archivo de bloques o lo levantamos si ya existia
	if(this->archivo->abrirArchivo() == -1){
		// El archivo no existe, lo creamos
		this->archivo->crearArchivo();
		this->archivo->abrirArchivo();
	}
	//Si existe pero esta cerrado, lo abrimos
	if (!this->archivo->estaAbierto()){
		this->archivo->abrirArchivo();
	}
}

ArchivoBloques* Block::getArchivo(){
	return this->archivo;
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
