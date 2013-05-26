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

// Devuelve el tamanio en bytes que ocuparia persistir la clase.
size_t RTTreferencia::getTamanioEnBytes()
{
    size_t bytes = 0;

    // Contamos el tamanio de la clase padre
    bytes += RegistroGenerico::getTamanioEnBytes();
    
    // Agregamos el tamanio de los atributos de esta clase
    bytes += sizeof(unsigned int) + sizeof(unsigned short int);

    return bytes;
}
