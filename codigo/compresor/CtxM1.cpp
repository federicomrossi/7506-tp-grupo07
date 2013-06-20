#include "CtxM1.h"
#include <stdio.h>
#define MAX_NUM_CARACTERES 257

using namespace std;
CtxM1::CtxM1(){
	this->probTotal=MAX_NUM_CARACTERES;
	this->ordenContexto=-1;
}

unsigned int CtxM1::getFrec(char letra,string letrasContexto){

	if (letra != EOF){
		unsigned short int aux =this->probTotal;
		this->probTotal--;
		return (aux);
	}else
		return 1;
} 
