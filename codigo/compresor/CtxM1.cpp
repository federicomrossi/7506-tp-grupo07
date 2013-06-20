#include "CtxM1.h"
#define MAX_NUM_CARACTERES 257

using namespace std;
CtxM1::CtxM1(){
	this->probTotal=MAX_NUM_CARACTERES;
	this->ordenContexto=-1;
}

void CtxM1::aumentarFrec(string letra){
}


unsigned int CtxM1::getFrec(string letra){
	if (letra != "EOF"){
		this->probTotal--;
		return (this->probTotal);
	}else
		return 1;
} 
