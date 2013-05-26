#ifndef DOMAIN_TITULOREFERENCIAS_H_INCLUDED
#define DOMAIN_TITULOREFERENCIAS_H_INCLUDED
#include "domain_RegistroGenerico.h"

class TituloReferencias : public RegistroGenerico {
    public:
        TituloReferencias(unsigned int clave);
        TituloReferencias();
        ~TituloReferencias();
        virtual int serializar(SerialBuffer *buffer);
        virtual void deserializar(SerialBuffer *buffer);
        unsigned int getRef1();
        unsigned int getRef2();
        unsigned int getRef3();
        unsigned int getRefLista();
        unsigned int getCant();
        unsigned int* getRefs();
        void setRef1(unsigned int ref);
        void setRef2(unsigned int ref);
        void setRef3(unsigned int ref);
        void setRefLista(unsigned int ref);
        void setCant(unsigned int cant);
    private:
        unsigned int refs[3];
        unsigned int refLista;
        unsigned int cant;

};

#endif // DOMAIN_TITULOREFERENCIAS_H_INCLUDED
