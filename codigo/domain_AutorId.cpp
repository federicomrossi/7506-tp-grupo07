#include "domain_AutorId.h"
#include <string.h>

AutorId::AutorId(const char* autor, unsigned int id){
    memcpy(this->autor,autor,100);
    this->id =id;
}

AutorId::AutorId(){
}

AutorId::~AutorId(){
}

int AutorId::comparar(Comparable *obj) const{
    return 1;
}

unsigned int AutorId::getId() const{
    return this->id;
}

const char* AutorId::getAutor() const{
    return this->autor;
}

std::ostream& operator << (std::ostream &out, AutorId &ocur){
    const char* c = ocur.getAutor();
    out.write(c,100);
    unsigned int p = ocur.getId();
    out.write((char*) &p,sizeof(unsigned int));
    return out;
}

std::istream& operator >> (std::istream &out, AutorId &ocur){
    unsigned int p;
    char c[100];
    out.read((char*) c,100);
    memcpy(ocur.autor,c,100);
    out.read((char*) &p,sizeof(unsigned int));
    ocur.id = p;
    return out;
}
