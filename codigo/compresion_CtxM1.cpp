#include "compresion_CtxM1.h"
#include <stdio.h>

using namespace std;
CtxM1::CtxM1(){
	this->ordenContexto=-1;
}

CtxM1::~CtxM1(){}

probabilidades CtxM1::getProbabilidadesEscape(string letrasContexto, ListaExclusion  *listaExclusion){
	probabilidades aux;
	unsigned short int cantDistintos=MAX_NUM_CARACTERES;
	unsigned int probAcum=0;
	unsigned int probTotal=MAX_NUM_CARACTERES;
	for (int i=0; i<MAX_NUM_CARACTERES ; i++){
		if ( listaExclusion->estaExcluido(i)) {
			probTotal--;
			cantDistintos--;
		}
	}
	aux.probaAcumulada=probAcum;
	aux.probaTotal=probTotal;
	aux.cantDistintos=cantDistintos;
	return aux;
}

probabilidades CtxM1::getProbabilidades(unsigned char letra,string letrasContexto, ListaExclusion *listaExclusion){
	probabilidades aux;
	unsigned short int cantDistintos=MAX_NUM_CARACTERES;
	unsigned int probAcum=0;
	unsigned int probCaracter=0;
	unsigned int probTotal=MAX_NUM_CARACTERES;
	bool acumulo = true;
	for (unsigned int i=0; i<MAX_NUM_CARACTERES ; i++){
		if ( ((unsigned int)letra != i) ) {
			if (!listaExclusion->estaExcluido((int)i)){
				if (acumulo){
					probAcum++ ;
				}
			}else if (listaExclusion->estaExcluido((int)i)){
				probTotal--;
				cantDistintos--;
			}
		}
		else if((unsigned int)letra == i) {
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

int CtxM1::extraerCaracter(unsigned short probaAcumulada, std::string contextoActual, ListaExclusion *listaExclusion)
{

	unsigned int acumulada=0;

	for (int i=0;i<MAX_NUM_CARACTERES;i++){
		if (probaAcumulada<acumulada) {
			return i-1;
		}

		if (!listaExclusion->estaExcluido(i)) {
			acumulada++;
		}
	}

	if (probaAcumulada<acumulada) {
		return MAX_NUM_CARACTERES-1;
	} else {
		listaExclusion->persistir();
		return -1;
	}

}

