/*
 * Reg.cpp
 *
 *  Created on: May 4, 2013
 *      Author: rburdet
 */

#include "logica_Reg.h"
#include <string>
using namespace std;

Reg::Reg(int id, int fileAdress) {
	this->size=sizeof(id)+sizeof(fileAdress);
	this->id=id;
	this->fileAdress=fileAdress;
}

Reg::~Reg() {
}

int Reg:: getSize(){
	return size;
}
