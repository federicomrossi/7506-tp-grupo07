#include <iostream>
#include "Ctx0.h"

using namespace std;

Ctx0::Ctx0(){
	this->ordenContexto=0;
	this->probTotal=0;
	for (int i=0; i<MAX_NUM_CARACTERES;i++)
		caracteres[i]=0;	
	CtxM1 pCtxPrevio;
}

void Ctx0::aumentarFrec(char letra){
	caracteres[(int)letra]++;
}

void Ctx0::exclusion(list<letraFrec> listaFrecs){
	list<letraFrec>::iterator it;
	for (it = listaFrecs.begin() ; it != listaFrecs.end() ; it ++){
		char aux = it->getLetra();
		caracteres[(int)aux]=0;
	}
}

unsigned int Ctx0::getTotal(list<letraFrec> listaFrecs){
	unsigned int cont = 0;
	this->exclusion(listaFrecs);
	for (int i=0; i<MAX_NUM_CARACTERES; i++){
		cont += caracteres[i];
	}
	this->probTotal=cont;
	return cont;
}

unsigned int Ctx0::getFrec(char letra){
		std::cout<<"la frecuencai del escape aca es: "<<caracteres[MAX_NUM_CARACTERES]<<endl;
		unsigned int aux= caracteres[(int)letra];
		aumentarFrec(letra);
		if ( aux != 0){
			return (aux);
		}
		else{
			//incremento el escape
			caracteres[MAX_NUM_CARACTERES]++;
			return(pCtxPrevio.getFrec(letra));
		}
}

