#include <iostream>
#include <string>
#include "Ctx0.h"

using namespace std;

Ctx0::Ctx0(){
	this->ordenContexto=0;
	this->probTotal=0;
	for (int i=0; i<MAX_NUM_CARACTERES;i++)
		caracteres[i]=0;	
}

void Ctx0::aumentarFrec(char letra,string letrasContexto){
	caracteres[(int)letra]++;
	this->probTotal++;
}

void Ctx0::exclusion(list<letraFrec> listaFrecs){
	list<letraFrec>::iterator it;
	int cantidadDeCaracteres=0;
	//recorro toda la lista, por cada posicion voy a tener una letra distinta a excluir, por lo tanto tambien tengo que excluir el escape tantas veces como la cantidad de letras que haya
	for (it = listaFrecs.begin() ; it != listaFrecs.end() ; it ++){
		char aux = it->getLetra();
		cantidadDeCaracteres++;
		caracteres[(int)aux]=0;
	}
	caracteres[MAX_NUM_CARACTERES]-=cantidadDeCaracteres;
}

unsigned int Ctx0::getTotal(list<letraFrec> listaFrecs,string letrasContexto){
	unsigned int cont = 0;
	this->exclusion(listaFrecs);
	for (int i=0; i<=MAX_NUM_CARACTERES; i++){
		cont += caracteres[i];
	}
	return cont;
}

unsigned int Ctx0::getTotal(){
	unsigned int cont = 0;
	for (int i=0; i<=MAX_NUM_CARACTERES; i++)
		cont += caracteres[i];
	return cont;	
}


unsigned int Ctx0::getFrec(char letra,string letrasContexto){
		std::cout<<"la frecuencai del escape aca es: "<<caracteres[MAX_NUM_CARACTERES]<<endl;
		unsigned int aux= caracteres[(int)letra];
		aumentarFrec(letra,letrasContexto);
		if ( aux != 0){
			return (aux);
		}
		else{
			//incremento el escape
			caracteres[MAX_NUM_CARACTERES]++;
			//CAMBIAR ESTO
			//TODO
			return(0);
		}
}
