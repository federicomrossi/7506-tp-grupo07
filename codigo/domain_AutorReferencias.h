#ifndef DOMAIN_AUTORREFERENCIAS_H_INCLUDED
#define DOMAIN_AUTORREFERENCIAS_H_INCLUDED
#include "domain_RegistroGenerico.h"

class AutorReferencias : public RegistroGenerico {
    public:
        AutorReferencias(unsigned int clave);
        AutorReferencias();
        ~AutorReferencias();
        virtual void serializar(SerialBuffer *buffer);
        virtual void deserializar(SerialBuffer *buffer);
        unsigned int getRef1();
        unsigned int getRef2();
        unsigned int getRef3();
        unsigned int getRef4();
        unsigned int getRef5();
        unsigned int getRefLista();
        unsigned int getCant();
        void setRef1(unsigned int ref);
        void setRef2(unsigned int ref);
        void setRef3(unsigned int ref);
        void setRef4(unsigned int ref);
        void setRef5(unsigned int ref);
        void setRefLista(unsigned int ref);
        void setCant(unsigned int cant);
    private:
        unsigned int ref1;
        unsigned int ref2;
        unsigned int ref3;
        unsigned int ref4;
        unsigned int ref5;
        unsigned int refLista;
        unsigned int cant;

};

#endif // DOMAIN_AUTORREFERENCIAS_H_INCLUDED
