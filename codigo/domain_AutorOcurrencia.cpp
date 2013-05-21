#include "domain_AutorOcurrencia.h"
#include <iostream>

AutorOcurrencia::AutorOcurrencia(unsigned int autorId, unsigned int documentoId){
    this->autorId = autorId;
    this->documentoId=documentoId;
}

AutorOcurrencia::AutorOcurrencia(){
}

AutorOcurrencia::~AutorOcurrencia(){
}

int AutorOcurrencia::comparar(Comparable *c) const{
    AutorOcurrencia *ocur = (AutorOcurrencia*) c;
    if(this->autorId > ocur->autorId) return 1;
    if(this->autorId < ocur->autorId) return -1;
    if(this->documentoId > ocur->documentoId) return 1;
    if(this->documentoId < ocur->documentoId) return -1;
    return 0;
}

unsigned int AutorOcurrencia::getDocumentoId() const{
    return documentoId;
}

unsigned int AutorOcurrencia::getAutorId() const{
    return autorId;
}


std::ostream& operator << (std::ostream &out, AutorOcurrencia &ocur){
    unsigned int p = ocur.getAutorId();
    out.write((char*) &p,sizeof(unsigned int));
    p = ocur.getDocumentoId();
    out.write((char*) &p,sizeof(unsigned int));
    return out;
}

std::istream& operator >> (std::istream &out, AutorOcurrencia &ocur){
    unsigned int p;
    out.read((char*) &p,sizeof(unsigned int));
    ocur.autorId = p;
    out.read((char*) &p,sizeof(unsigned int));
    ocur.documentoId = p;
    return out;
}
