#include "compresion_letraFrec.h"
//si se agrego la letra, se la agrega con frecuencia 1 
letraFrec::letraFrec(char letra){
	this->letra = letra;
	this->frec = 1;
}


char letraFrec::getLetra(){
	return (this->letra);
}


unsigned int letraFrec::getFrec(){
	return (this->frec);
}


void letraFrec::aumentarFrec(){
	this->frec++;
}
