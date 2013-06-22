#include "CtxM1.h"
#include <stdio.h>

using namespace std;
CtxM1::CtxM1(){
	this->ordenContexto=-1;
}

CtxM1::~CtxM1(){}

probabilidades CtxM1::getProbabilidadesEscape(string letrasContexto, ListaExclusion& listaExclusion){
	probabilidades aux;
	unsigned short int cantDistintos=MAX_NUM_CARACTERES;
	unsigned int probAcum=0;
	unsigned int probTotal=MAX_NUM_CARACTERES;
	for (int i=0; i<MAX_NUM_CARACTERES ; i++){
		if ( listaExclusion.estaExcluido((char)i)) {
			probTotal--;
			cantDistintos--;
		}
	}
	aux.probaAcumulada=probAcum;
	aux.probaTotal=probTotal;
	aux.cantDistintos=cantDistintos;
	return aux;
}

probabilidades CtxM1::getProbabilidades(char letra,string letrasContexto, ListaExclusion& listaExclusion){
	probabilidades aux;
	unsigned short int cantDistintos=MAX_NUM_CARACTERES;
	unsigned int probAcum=0;
	unsigned int probCaracter=0;
	unsigned int probTotal=MAX_NUM_CARACTERES;
	bool acumulo = true;
	for (int i=0; i<MAX_NUM_CARACTERES ; i++){
		if ( ((int)letra != i) ) {
			if (!listaExclusion.estaExcluido((char)i)){
				if (acumulo){
					probAcum++ ;
				}
			}else{
				probTotal--;
				cantDistintos--;
			}
		}
		else if((int)letra == i) {
				probCaracter=1;
				acumulo=false;
		}
	}
	aux.probaCaracter=probCaracter;
	aux.probaAcumulada=probAcum;
	aux.probaTotal=probTotal;
	aux.cantDistintos=cantDistintos;
	return aux;
}

int CtxM1::extraerCaracter(unsigned short probaAcumulada, std::string contextoActual, ListaExclusion &listaExclusion)
{
	
	unsigned int acumulada=0;

	for (int i=0;i<MAX_NUM_CARACTERES;i++){
		if (probaAcumulada<acumulada) {
			return i-1;
		}

		if (!listaExclusion.estaExcluido((char)i)) {
			acumulada++;
		}
	}

	if (probaAcumulada<acumulada) {
		return MAX_NUM_CARACTERES-1;
	} else {
		listaExclusion.persistir();
		return -1;
	}

}

