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

Ctx0::~Ctx0(){}

void Ctx0::aumentarFrec(char letra,string letrasContexto){
	caracteres[(unsigned int)letra]++;
}


probabilidades Ctx0::getProbabilidades(char letra,string letrasContexto, ListaExclusion *listaExclusion){
	probabilidades aux;
	unsigned short int cantDistintos=0;
	unsigned int probAcum=0;
	unsigned int probCaracter=0;
	unsigned int probTotal=0;
	bool acumulo = true;
	for (int i=0; i<MAX_NUM_CARACTERES ; i++){
		if ( ((int)letra != i) && (caracteres[(int)i]!=0) ) {
			if (!listaExclusion->estaExcluido(i)){
				probTotal+=caracteres[(int)i];
				if (acumulo){
					probAcum+= caracteres[(int)i];
				}
				listaExclusion->excluirCaracter(i);
				cantDistintos++;
			}
		}
		else if(letra == i) {
				probTotal+=caracteres[i];
				probCaracter=caracteres[i];
				acumulo=false;
				if (probCaracter!=0)
					cantDistintos++;
		}
	}
	aux.probaCaracter=probCaracter;
	aux.probaAcumulada=probAcum;
	aux.probaTotal=probTotal;
	aux.cantDistintos=cantDistintos;
	if (aux.probaCaracter==0)
		listaExclusion->persistir();
	return aux;
}

probabilidades Ctx0::getProbabilidadesEscape(string letrasContexto,ListaExclusion *listaExclusion){
	probabilidades aux;
	unsigned short int cantDistintos=0;
	unsigned int probAcum=0;
	unsigned int probTotal=0;
	for (int i=0; i<MAX_NUM_CARACTERES ; i++){
		if ( !listaExclusion->estaExcluido(i)) {
			probTotal+=caracteres[(int)i];
			if(caracteres[i]>0)
				cantDistintos++;
		}
	}
	aux.probaAcumulada=probAcum;
	aux.probaTotal=probTotal;
	aux.cantDistintos=cantDistintos;
	return aux;
}

int Ctx0::extraerCaracter(unsigned short probaAcumulada,  string contextoActual, ListaExclusion *listaExclusion)
{
	unsigned int acumulada = 0;

	for (int i=0;i<MAX_NUM_CARACTERES;i++) {

		if (probaAcumulada<acumulada) {
			return i-1;
		}

		if (!listaExclusion->estaExcluido(i)) {
			acumulada+= caracteres[i];
		}

		if (caracteres[i]!=0) {
			listaExclusion->excluirCaracter(i);
		}

	}

	if (probaAcumulada<acumulada) {
		return MAX_NUM_CARACTERES-1;
	} else {
		listaExclusion->persistir();
		return -1;
	}

}






