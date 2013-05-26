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

int RTTreferencia::serializar(SerialBuffer *buffer){
    RegistroGenerico::serializar(buffer);
    if(buffer->pack(&refLista,sizeof(refLista)))
		return 0;
	return 1;
}

void RTTreferencia::deserializar(SerialBuffer *buffer){
    RegistroGenerico::deserializar(buffer);
    buffer->unpack(&refLista);
}
