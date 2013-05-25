#include "domain_TituloReferencias.h"

TituloReferencias::TituloReferencias(){
}

TituloReferencias::TituloReferencias(unsigned int clave){
    this->setClave(clave);
}

TituloReferencias::~TituloReferencias(){
}

unsigned int TituloReferencias::getCant(){
    return this->cant;
}

unsigned int TituloReferencias::getRef1(){
    return this->ref1;
}

unsigned int TituloReferencias::getRef2(){
    return this->ref2;
}

unsigned int TituloReferencias::getRef3(){
    return this->ref3;
}

unsigned int TituloReferencias::getRefLista(){
    return this->refLista;
}

void TituloReferencias::setCant(unsigned int cant){
    this->cant= cant;
}

void TituloReferencias::setRef1(unsigned int ref){
    this->ref1 = ref;
}

void TituloReferencias::setRef2(unsigned int ref){
    this->ref2 = ref;
}

void TituloReferencias::setRef3(unsigned int ref){
    this->ref3 = ref;
}

void TituloReferencias::setRefLista(unsigned int ref){
    this->refLista = ref;
}

void TituloReferencias::serializar(SerialBuffer *buffer){
    RegistroGenerico::serializar(buffer);
    buffer->pack(&cant,sizeof(cant));
    buffer->pack(&ref1,sizeof(ref1));
    buffer->pack(&ref2,sizeof(ref2));
    buffer->pack(&ref3,sizeof(ref3));
    buffer->pack(&refLista,sizeof(refLista));
}

void TituloReferencias::deserializar(SerialBuffer *buffer){
    RegistroGenerico::deserializar(buffer);
    buffer->unpack(&cant);
    buffer->unpack(&ref1);
    buffer->unpack(&ref2);
    buffer->unpack(&ref3);
    buffer->unpack(&refLista);
}
