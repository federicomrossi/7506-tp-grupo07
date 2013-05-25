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


#include <list>
#include <string.h>
#include <stdlib.h>
//#include "logica_Reg.h" Estaria quedando deprecado para usar registros genericos
#include "fisica_ArchivoBloques.h"
#include "logica_HashExtensible.h"
#include "config.h"
#include "domain_RegistroGenerico.h"

//Probando a las 6:17 de la maniana si puedo hacer andar las clases de fede
#include "fisica_SerialBuffer.h"
using namespace std;
/*
 * El tamanio de registros en un bloque debe poder ser configurable desde afuera
 * ver bien !!!
 * */



template <class T>
class Block {
	public:
		Block(int DispersionSize,int blockAdress, char* filePath, int blocksize); //Creo un bloque en una tabla de bloques. Inicialmente el tamanio es 0

		//  Agrego un registro a la cubeta, los resultados posibles son: 0 sino se agrego, 1 si se agrego, 2 si se duplico el tamanio.
		int Insert(T & aReg);

		// Si el bloque queda en overflow tengo que crear otro para luego redistribuir los registros*/
		Block* createNew(int newDispersionSize);

		//crea un nuevo bloque, redispersando y cambiando los tamanios de dispersion de ambos bloques
		int separate();

		// Cuando se produce un overflow, tengo que redispersar los registros */
		int redistribute(Block * aNewBlock,int tableSize);

		// Cuando se duplica la tabla, o un bloque queda en overflow pero con mas de 1 referencia en la tabla entonces es necesario cambiar el tamanio de dispersion del bloque
		// Devuelve el nuevo tamanio de dispersion
		void changeDispersionSize(int);

		// Cuando un bloque queda en overflow, necesito buscar el proximo bloque en donde pueda redispersar,  */
		int getBlockInTable();
		
		//Si entra el registro devuelve verdadero, si no falso
		bool easyInsert(T& aReg);

		//Devuelve el tamanio de dispersion del bloque
		int getDispersionSize();

		//Cuando se agrega un nuevo bloque se tiene que duplicar el tamanio de dispersion del bloque
		int duplicateDispersionSize();

		//Devuelve el numero de bloque
		int getBlockNum();

		//Devuelve la lista de registros
		list<T> getRegList();

		//Devuelve la posicion del bloque en el archivo de bloques
		int getBlockAdress();

		//Devuelve el espacio ocupado dentro del bloque
		short int getNumberOfRegs();


		//Una vez que obtengo el bloque, tengo que buscar en la lista el registro que yo quiero
		//Devuelvo el fileAdress de ese registro que es donde estara guardado el dato
		//SI NO SE ENCUENTRA EL REGISTRO SE DEVUELVE 0
		bool search(T*&);

		void read();
		void write();
		//TODO: solo el cierra
		//void open(const char * fileName);
		//void close();
		//ArchivoBloques* getArchivo();

		//Obtengo el numero del ultimo bloque
		unsigned int newBlockNum();

		~Block();

	protected:
		short int numberOfRegs;
		//short int maxNumberOfRegs;
		//int blockCurrentSize;
		int maxBlockSize;
		int dispersionSize;
		list< T > regsList;
		int blockNum;
		char *filePath;

	private:
		void getCurrentBuffer(SerialBuffer * );
};

template <class T>
Block<T>::Block(int dispersionSize, int blockNum, char* filePath, int blocksize){
	this->numberOfRegs=0;
	this->dispersionSize=dispersionSize;
	this->maxBlockSize=blocksize;
	//this->maxNumberOfRegs=MAX_REGS_PER_BLOCK;
	this->blockNum = blockNum;
	this->filePath=new char[strlen(filePath)+1]();
	strcpy(this->filePath, filePath);
}

/*
 * en un bloque yo tengo que agregar un registro, y ademas tengo que agregar ese bloque a la lista de bloques
 * */


template <class T>
unsigned int Block<T>::newBlockNum(){
	ArchivoBloques archivo(this->maxBlockSize, this->filePath);
	return  archivo.ultimoBloque();
}

template <class T>
int Block<T>::Insert(T & aReg){
	this->numberOfRegs+=1;
	this->regsList.push_back(aReg);
	return 0;

}

template <class T>
void Block<T>::changeDispersionSize(int newDispersionSize){
	this->dispersionSize=newDispersionSize;
}
template <class T>
list<T> Block<T>::getRegList(){
	return this->regsList;
}

template <class T>
int Block<T>::getBlockNum(){
	return this->blockNum;
}

template <class T>
int Block<T>::duplicateDispersionSize(){
	return (this->dispersionSize*=2);
}

template <class T>
int Block<T>::getDispersionSize(){
	return dispersionSize;
}

template <class T>
short int Block<T>::getNumberOfRegs(){
	return this->numberOfRegs;
}


template <class T>
bool Block<T>::easyInsert(T& aReg){
	SerialBuffer aSerialBuffer(maxBlockSize);
	this->getCurrentBuffer(&aSerialBuffer);

	unsigned short int preSize = aSerialBuffer.getBuffSize();
	aReg.serializar(&aSerialBuffer);

	if(aSerialBuffer.getBuffSize() - preSize == 0)
		return false;
	return true;
}

template <class T>
bool Block<T>::search(T*& regToLook){
	typename list<T>::iterator it;
	for (it = regsList.begin(); it != regsList.end(); it++){
		if ((it)->getClave()==regToLook->getClave()){
			//TODO:Habria que hacer delete?
			regToLook=&*it;
			return true;
		}
	}
	return false;
}

// Implementacion con clase de archivo -> No anda
//void Block::write(){
//	ArchivoBloques archivo(this->maxBlockSize, this->filePath);
//	// Inicializamos el archivo de bloques o lo levantamos si ya existia
//	if(archivo.abrirArchivo() == -1){
//		// El archivo no existe, lo creamos
//		archivo.crearArchivo();
//		archivo.abrirArchivo();
//	}
//	//Si existe pero esta cerrado, lo abrimos
//	if (!archivo.estaAbierto()){
//		archivo.abrirArchivo();
//	}
//
//	int *Buf = (int*) calloc(this->maxBlockSize, 1);
//	int i=0;
//
//	list<Reg>::iterator it;
//	cout << " Write -> " ;
//	for(it = regsList.begin(); it!= regsList.end(); it++){
//		Buf[i++] = it->getId();
//		Buf[i++] = it->getFileAdress();
//		cout << " '" << it->getId() << "' '" << it->getFileAdress() << "'";
//	}
//	cout << endl;
//
//	archivo.escribirBloque((void*) Buf, this->getBlockNum(), this->maxBlockSize);
//	archivo.cerrarArchivo();
//	free(Buf);
//}

// Implementacion abriendo archivo de manera cabeza -> Anda =D
/*
void Block::write(){
	fstream archivo(this->filePath,ios::in|ios::out|ios::binary);
	if (!archivo.is_open())
		archivo.open(this->filePath,ios::out|ios::binary);

	//2int *Buf = (int*) calloc(this->maxBlockSize, 1);
	int * Buf = new int[this->maxBlockSize]();
	int i=0;

	list<Reg>::iterator it;
	//1	cout << " Write -> " ;
	for(it = regsList.begin(); it!= regsList.end(); it++){
		Buf[i++] = it->getId();
		Buf[i++] = it->getFileAdress();
		//1	cout << " '" << it->getId() << "' '" << it->getFileAdress() << "'";
	}
	//1cout << endl;

	archivo.seekg(0,archivo.beg);
	archivo.seekg(this->maxBlockSize*this->getBlockNum());
	archivo.write((char*)Buf,this->maxBlockSize);
	archivo.close();
	//2free(Buf);
	delete[]Buf;
}
*/


template <class T>
void Block<T>::getCurrentBuffer(SerialBuffer* aSerialBuffer){
	aSerialBuffer->pack(&(this->numberOfRegs), sizeof(this->numberOfRegs));
	typename list<T>::iterator it;
	for(it = regsList.begin(); it!= regsList.end(); it++){
		it->serializar(aSerialBuffer);
	}
}

template <class T>
void Block<T>::write(){
	ArchivoBloques archivo(maxBlockSize,this->filePath);
	SerialBuffer aSerialBuffer(maxBlockSize);
	this->getCurrentBuffer(&aSerialBuffer);
	archivo.escribirBloque(aSerialBuffer.getBuffer(),this->getBlockNum());
}



/// SEGUIR CON ESTOOOOO
template <class T>
void Block<T>::read(){
	ArchivoBloques archivo(maxBlockSize,this->filePath);
	SerialBuffer aSerialBuffer(maxBlockSize);
	archivo.leerBloque(aSerialBuffer.getBuffer(),this->getBlockNum());
	aSerialBuffer.unpack(&(this->numberOfRegs));
	//TODO: Liberar 
	regsList.clear();
	for (int i=0; i < this->numberOfRegs;i++){
		T reg;
		reg.deserializar(&aSerialBuffer);
		regsList.push_back(reg);
		//aSerialBuffer.unpack(&(this->numberOfRegs));
		//aSerialBuffer.unpack()
	}
}


/*void Block::read(){ //
	ArchivoBloques archivo(maxBlockSize,this->filePath);
	SerialBuffer aSerialBuffer(maxBlockSize);
	int id,adress;
	archivo.leerBloque(aSerialBuffer.getBuffer(),this->getBlockNum());
	aSerialBuffer.unpack(&id);
	aSerialBuffer.unpack(&adress);
	Reg* aReg=new Reg(id,adress);
	this->Insert(*aReg);
}*/

// Implementacion abriendo archivo de manera cabeza -> Anda =D
/*
void Block::read(){
	fstream archivo(this->filePath,ios::in|ios::out|ios::binary);
	if (!archivo.is_open()){
		//1		cout << "Error Abrir archivo!!!!! ***** " << endl;
		return;
		archivo.open(this->filePath,ios::out|ios::binary);
	}

	//2int *buf = (int*) calloc(this->maxBlockSize, 1);
	int * buf = new int [this->maxBlockSize]();
	archivo.seekg(0,archivo.beg);
	archivo.seekg(this->maxBlockSize*this->getBlockNum());
	archivo.read((char*)buf, this->maxBlockSize);


	//


	//1cout << "Read ->" ;
	//for (int i=0; ((unsigned int) i)<this->maxBlockSize/sizeof(int) && buf[i]!=0; i++){ //Cuando viene un id =0 significa qe ya no hay mas info TODO: controlar qe no se pase del buffer
	for (int i=0; ((unsigned int) i)<this->maxBlockSize/sizeof(int); i+=2){
		//TODO: donde libera los registros?
		//1	cout << " '" << buf[i] << "' '" << buf[i+1] << "'";
		if(buf[i]!=0){
			Reg* aReg= new Reg(buf[i],buf[i+1]);
			this->Insert(*aReg);
		}
	}
	//1	cout << endl;
	archivo.close();
	//2free(buf);
	delete[] buf;
}
*/
/**/
/*
ArchivoBloques* Block::getArchivo(){
	return this->archivo;
}*/

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

template <class T>
Block<T>::~Block() {
	//2free(this->filePath);
	regsList.clear();
	delete [] this->filePath;
}

#endif
