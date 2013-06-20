#include "Ctx0.h"

using namespace std;

Ctx0::Ctx0(){
	this->ordenContexto=0;
	for (int i=0; i<MAX_NUM_CARACTERES;i++)
		caracteres[i]=0;	
}

void Ctx0::aumentarFrec(string letra){
	if (letra != "ESC")
		caracteres[static_cast<int>(letra[0])]++;
	else 
		caracteres[MAX_NUM_CARACTERES]++;
}

void Ctx0::exclusion(list<letraFrec> listaFrecs){
	list<letraFrec>::iterator it;
	for (it = listaFrecs.begin() ; it != listaFrecs.end() ; it ++){
		string aux = it->getLetra();
		caracteres[static_cast<int>(aux[0])]=0;
	}
}

unsigned int Ctx0::getTotal(list<letraFrec> listaFrecs){
	unsigned int cont = 0;
	this->exclusion(listaFrecs);
	for (int i=0; i<MAX_NUM_CARACTERES; i++){
		cont += caracteres[i];
	}
	return cont;
}

unsigned int Ctx0::getFrec(string letra){
	if (letra != "ESC")
	{	
		return (caracteres[static_cast<int>(letra[0])]);
	}else
		return (caracteres[MAX_NUM_CARACTERES]);
}


