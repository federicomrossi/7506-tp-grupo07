#include "letraFrec.h"

letraFrec::letraFrec(string letra){
	this->letra = letra;
	this->frec = 1;
}


string letraFrec::getLetra(){
	return (this->letra);
}


unsigned int letraFrec::getFrec(){
	return (this->frec);
}


void letraFrec::aumentarFrec(){
	this->frec++;
}
