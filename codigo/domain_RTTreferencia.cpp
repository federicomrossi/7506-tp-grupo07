#include "domain_RTTreferencia.h"

RTTreferencia::RTTreferencia(){
}

RTTreferencia::RTTreferencia(unsigned int clave){
    this->setClave(clave);
}

RTTreferencia::~RTTreferencia(){
}

unsigned int RTTreferencia::getRefLista(){
    return this->refLista;
}

void RTTreferencia::setRefLista(unsigned int ref){
    this->refLista = ref;
}

void RTTreferencia::serializar(SerialBuffer *buffer){
    RegistroGenerico::serializar(buffer);
    buffer->pack(&refLista,sizeof(refLista));
}

void RTTreferencia::deserializar(SerialBuffer *buffer){
    RegistroGenerico::deserializar(buffer);
    buffer->unpack(&refLista);
}
