#include <iostream>
#include "../logica_BlockTable.h"
#include "../domain_RegistroGenerico.h"
#include "config.h"
#include "../prueba_UnRegistroGenerico.h"
using namespace std;

int DATA[DATA_LENGTH][2];

void fillData(){
	for(int i=0;i<DATA_LENGTH;i++){
		DATA[i][0] = i+1;
		DATA[i][1] = i+1;
	}
}

int main()
{
	BlockTable<UnRegistroGenerico> aBlockTable(TEST_FILE_TABLE, TEST_FILE, BLOCK_SIZE);
	int error=0;

	//Inserto
	fillData();
	for(int i=0;i<DATA_LENGTH;i++){
		cout << "** Agregando registro "<< i  << endl;
		UnRegistroGenerico aReg;
		aReg.setClave(DATA[i][0]);
		aBlockTable.insert(aReg);
	}

	cout << "Despues de insertar" << endl;


	//Busco
	for(int i=0;i<DATA_LENGTH;i++){
		UnRegistroGenerico* aReg = new UnRegistroGenerico();
		aReg->setClave(DATA[i][0]);
		int ad = aBlockTable.search(aReg);
		if( ! ( ad && aReg->getClave() ==  DATA[i][0])){
			cout << " \t ** Error i=" << i << " id=" << DATA[i][0] << " ad=" << DATA[i][1] << " ret_val=" << ad << endl;
			error++;
		}
		cout << "Claveeee" <<aReg->getClave()  << endl;
		delete aReg;
	}

	cout << "fin " ;
	if(error)
		cout << "ERROR";
	else
		cout << " No Hay errores =D";
	cout << endl;

    return 0;
}
