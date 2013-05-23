/*
 * BlockTable.cpp
 *
 *  Created on: May 11, 2013
 *      Author: rburdet
 */
#include "logica_BlockTable.h"

#define PRINT_REF(X) cout << X << "blockReferences" ; for(int i=0;i<this->getSize();i++) cout << " '" << this->blockReferences[i] << "'"; cout << endl
using namespace std;

BlockTable::BlockTable(string path, string blockPath, int blockSize) {
	// TODO: exepcion si path == NULL
	this->filePath= new char[strlen(path.c_str())+1]();
	//this->filePath = (char*) calloc(strlen(path.c_str()) +1, sizeof(char));
	strcpy(this->filePath, path.c_str());
	this->blockPath = new char[strlen(blockPath.c_str())+1]();
	//this->blockPath = (char*) calloc(strlen(blockPath.c_str()) +1, sizeof(char));
	strcpy(this->blockPath, blockPath.c_str());
	this->blockReferences = NULL;
	this->blockSize = blockSize;
	this->read();
}

void BlockTable::read(){
	fstream archivo(this->filePath,ios::in|ios::out|ios::binary);

	if (!archivo.is_open())
		archivo.open(this->filePath,ios::out|ios::binary);

	archivo.seekg(0,archivo.end); //TODO: revisar que esto ande bien!
	this->size = archivo.tellg() / sizeof(int);

	if(this->blockReferences)
		//free(this->blockReferences);
		delete [] this->blockReferences;

	if(this->size){ //TODO: revisar que esto ande bien!
		archivo.seekg(0,archivo.beg);
		//this->blockReferences = (int*) calloc(this->size, sizeof(int));
		this->blockReferences= new int[this->size]();
		archivo.read((char*)this->blockReferences, this->size * sizeof(int));
	}else{
		this->size = 1;
		//this->blockReferences = (int*) calloc(this->size, sizeof(int));;
		this->blockReferences = new int[this->size]();
	}

	archivo.close();
}

void BlockTable::write(){
	fstream archivo(this->filePath,ios::in|ios::out|ios::binary);
	archivo.write((char*)this->blockReferences,sizeof(int)*this->size);
	archivo.close();
}

//TODO: por que le paso un registro y no un id solo, osae, al crear un registro ya lo creo con un adres especifico, y si estoy buscando, no se ese adress!
int BlockTable::search(Reg& aReg){ // TODO: persistencia
	int pos=HashExtensible::doHash(aReg.getId(),this->getSize());
	
	int blockNumber=this->blockReferences[pos];

	//1cout << "\tSearch doHash(regId=" << aReg.getId() << ", size=" << this->getSize() <<") = "<< pos << endl;
	//1	PRINT_REF("\t\t (" << blockNumber << ")");

	Block aBlock(this->getSize(), blockNumber, this->blockPath, this->blockSize);
	//1 cout << "\t\t\t Read";
	aBlock.read();

	return aBlock.search(aReg);
}

int BlockTable::countNumberOfReferences(int blockNumber){
	int count = 0;
	for (int i=0; i< this->getSize(); i++){
		if (this->blockReferences[i]==blockNumber)
			count +=1;
	}
	return count;
}

int BlockTable::insert(Reg & aReg){
	int pos = HashExtensible::doHash(aReg.getId(),this->getSize());
	int tmpBlockNumber = this->blockReferences[pos];
	int dispersionSize = this->getSize() / this->countNumberOfReferences(tmpBlockNumber);
	//1cout << "\tInserto doHash(regId=" << aReg.getId() << ", size=" << this->getSize() <<") = "<< pos << endl;
	//1	PRINT_REF("\t\t (" << tmpBlockNumber << ")");

	Block tmpBlock(dispersionSize, tmpBlockNumber, this->blockPath, this->blockSize);
	//1cout << "\t\t\t tmpBlock";
	tmpBlock.read();

	//Puede ser el caso de que el ID ya exista en el hash, en ese caso, no se agrega

	if(tmpBlock.search(aReg)==-1){
		//1cout << "agrego xq no esta"<<endl;
		if (tmpBlock.easyInsert(aReg)){
			tmpBlock.Insert(aReg);
			//1cout << "\t\t\t\teasyInsert ";
			tmpBlock.write();
		} else {
			//1cout << " como no es easy insert, tengo que ver que hago"<<endl;
			//1cout << "el TD del bloque: "<<tmpBlock.getBlockNum()<< " es de :"<<dispersionSize<< endl;
			//1cout << endl;
			if (! this->canAddBlock(&tmpBlock)){
				this->duplicateTable();
				//1				PRINT_REF("\t\t afterDuplicate:");
			}
			int lastBlockNum = tmpBlock.newBlockNum();
			Block anotherBlock(tmpBlock.duplicateDispersionSize(), lastBlockNum, this->blockPath, this->blockSize);
			//1			cout << "\t\t anotherBlock(TD="<< anotherBlock.getDispersionSize() << ", lastBlockNum=" << lastBlockNum << ", path=" << this->blockPath << ", size="<< this->blockSize << ")" << endl;

			this->insertBlock(pos, lastBlockNum, tmpBlock.getDispersionSize());
			//1cout << "\t\tinsertBlock(pos=" << pos << ", lastBlockNum=" << lastBlockNum << ", TD=" << tmpBlock.getDispersionSize() << ")" << endl;
			//1PRINT_REF("\t\t after insertBlock:");

			this->redisperse(&tmpBlock, &anotherBlock);

			this->insert(aReg);
		}
	}
	return 0;
}

int BlockTable::getSize(){
	return size;
}

bool BlockTable::canAddBlock(Block* aBlock){
	//1cout << "\t\t TT:" << this->getSize() << " TD:" << aBlock->getDispersionSize() << endl;
	return (aBlock->getDispersionSize()!=this->getSize());
}

void BlockTable::insertBlock(int blockPos, int newBlockNum, int td){
	for (int i = blockPos; i < this->getSize(); i+=td) {
		this->blockReferences[i] = newBlockNum;
	}

	for (int i = blockPos-td; i >= 0; i-=td) {
		this->blockReferences[i] = newBlockNum;
	}
}

void BlockTable::redisperse(Block* anOldBlock, Block* aNewBlock){
	list<Reg>::iterator it;
	list<Reg> anOldBlockList = anOldBlock->getRegList();
	Block newAnOldBlock(anOldBlock->getDispersionSize(), anOldBlock->getBlockNum(), this->blockPath, this->blockSize);

	for (it = anOldBlockList.begin(); it != anOldBlockList.end() ; it++) {
		int pos = HashExtensible::doHash((*it).getId(),this->getSize());
		int blockNum = this->blockReferences[pos];
		if( anOldBlock->getBlockNum() == blockNum )
			newAnOldBlock.Insert(*it);
		else
			aNewBlock->Insert((*it));
	}

	//1cout << "\t\t\t\t(" << newAnOldBlock.getBlockNum() <<", TD:" <<  newAnOldBlock.getDispersionSize() << ") newAnOldBlock.write() ";
	newAnOldBlock.write();
	//1cout << "\t\t\t\t(" << aNewBlock->getBlockNum() <<", TD:" <<  aNewBlock->getDispersionSize() << ") aNewBlock.write() ";
	aNewBlock->write();
}



void BlockTable::duplicateTable(){
	int newBlockTableSize = this->size *2;
	int *tmpBlockReference = (int*) calloc(newBlockTableSize, sizeof(int));
	for (int i = 0; i < this->size ; i++) {
		tmpBlockReference[i] = this->blockReferences[i];
		tmpBlockReference[this->size+i] = this->blockReferences[i];
	}
	delete this->blockReferences;
	this->blockReferences = tmpBlockReference;
	this->size = newBlockTableSize;
}

BlockTable::~BlockTable(){
	this->write();
	free(this->blockReferences);
	delete [] this->blockPath;
	//free(this->blockPath);
	delete [] this->filePath;
	//free(this->filePath);
}
