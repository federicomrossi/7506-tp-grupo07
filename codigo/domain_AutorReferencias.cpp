#include "domain_AutorReferencias.h"

AutorReferencias::AutorReferencias(){
}

AutorReferencias::AutorReferencias(unsigned int clave){
    this->setClave(clave);
}

AutorReferencias::~AutorReferencias(){
}

unsigned int AutorReferencias::getCant(){
    return this->cant;
}

unsigned int AutorReferencias::getRef1(){
    return this->ref1;
}

unsigned int AutorReferencias::getRef2(){
    return this->ref2;
}

unsigned int AutorReferencias::getRef3(){
    return this->ref3;
}

unsigned int AutorReferencias::getRef4(){
    return this->ref4;
}

unsigned int AutorReferencias::getRef5(){
    return this->ref5;
}

unsigned int AutorReferencias::getRefLista(){
    return this->refLista;
}

void AutorReferencias::setCant(unsigned int cant){
    this->cant= cant;
}

void AutorReferencias::setRef1(unsigned int ref){
    this->ref1 = ref;
}

void AutorReferencias::setRef2(unsigned int ref){
    this->ref2 = ref;
}

void AutorReferencias::setRef3(unsigned int ref){
    this->ref3 = ref;
}

void AutorReferencias::setRef4(unsigned int ref){
    this->ref4 = ref;
}

void AutorReferencias::setRef5(unsigned int ref){
    this->ref5 = ref;
}

void AutorReferencias::setRefLista(unsigned int ref){
    this->refLista = ref;
}

void AutorReferencias::serializar(SerialBuffer *buffer){
    RegistroGenerico::serializar(buffer);
    buffer->pack(&cant,sizeof(cant));
    buffer->pack(&ref1,sizeof(ref1));
    buffer->pack(&ref2,sizeof(ref2));
    buffer->pack(&ref3,sizeof(ref3));
    buffer->pack(&ref4,sizeof(ref4));
    buffer->pack(&ref5,sizeof(ref5));
    buffer->pack(&refLista,sizeof(refLista));
}

void AutorReferencias::deserializar(SerialBuffer *buffer){
    RegistroGenerico::deserializar(buffer);
    buffer->unpack(&cant);
    buffer->unpack(&ref1);
    buffer->unpack(&ref2);
    buffer->unpack(&ref3);
    buffer->unpack(&ref4);
    buffer->unpack(&ref5);
    buffer->unpack(&refLista);
}
