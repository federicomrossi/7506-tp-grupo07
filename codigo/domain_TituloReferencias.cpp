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
    return this->refs[0];
}

unsigned int TituloReferencias::getRef2(){
    return this->refs[1];
}

unsigned int TituloReferencias::getRef3(){
    return this->refs[2];
}

unsigned int TituloReferencias::getRefLista(){
    return this->refLista;
}

void TituloReferencias::setCant(unsigned int cant){
    this->cant= cant;
}

void TituloReferencias::setRef1(unsigned int ref){
    this->refs[0] = ref;
}

void TituloReferencias::setRef2(unsigned int ref){
    this->refs[1] = ref;
}

void TituloReferencias::setRef3(unsigned int ref){
    this->refs[2] = ref;
}

void TituloReferencias::setRefLista(unsigned int ref){
    this->refLista = ref;
}

unsigned int* TituloReferencias::getRefs(){
    return this->refs;
}

int TituloReferencias::serializar(SerialBuffer *buffer){
	RegistroGenerico::serializar(buffer);
    if(buffer->pack(&cant,sizeof(cant)))
		return 0;
    if(buffer->pack(refs,sizeof(unsigned int)*3))
		return 0;
    if(buffer->pack(&refLista,sizeof(refLista)))
		return 0;

	return 1;
}

void TituloReferencias::deserializar(SerialBuffer *buffer){
    RegistroGenerico::deserializar(buffer);
    buffer->unpack(&cant);
    buffer->unpack(&refs);
    buffer->unpack(&refLista);
}

// Devuelve el tamanio en bytes que ocuparia persistir la clase.
size_t TituloReferencias::getTamanioEnBytes()
{
    size_t bytes = 0;

    // Contamos el tamanio de la clase padre
    bytes += RegistroGenerico::getTamanioEnBytes();
    
    // Agregamos el tamanio de los atributos de esta clase
    bytes += sizeof(unsigned int)*5 + sizeof(unsigned short int)*3;

    return bytes;
}
