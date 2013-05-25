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
    return this->refs[0];
}

unsigned int AutorReferencias::getRef2(){
    return this->refs[1];
}

unsigned int AutorReferencias::getRef3(){
    return this->refs[2];
}

unsigned int AutorReferencias::getRef4(){
    return this->refs[3];
}

unsigned int AutorReferencias::getRef5(){
    return this->refs[4];
}

unsigned int AutorReferencias::getRefLista(){
    return this->refLista;
}

void AutorReferencias::setCant(unsigned int cant){
    this->cant= cant;
}

void AutorReferencias::setRef1(unsigned int ref){
    this->refs[0] = ref;
}

void AutorReferencias::setRef2(unsigned int ref){
    this->refs[1] = ref;
}

void AutorReferencias::setRef3(unsigned int ref){
    this->refs[2] = ref;
}

void AutorReferencias::setRef4(unsigned int ref){
    this->refs[3] = ref;
}

void AutorReferencias::setRef5(unsigned int ref){
    this->refs[4]= ref;
}

void AutorReferencias::setRefLista(unsigned int ref){
    this->refLista = ref;
}

unsigned int* AutorReferencias::getRefs(){
    return this->refs;
}

void AutorReferencias::serializar(SerialBuffer *buffer){
    RegistroGenerico::serializar(buffer);
    buffer->pack(&cant,sizeof(cant));
    buffer->pack(refs,sizeof(unsigned int)*5);
    buffer->pack(&refLista,sizeof(refLista));
}

void AutorReferencias::deserializar(SerialBuffer *buffer){
    RegistroGenerico::deserializar(buffer);
    buffer->unpack(&cant);
    buffer->unpack(&refs);
    buffer->unpack(&refLista);
}
