#ifndef DOMAIN_RTTREFERENCIA_H_INCLUDED
#define DOMAIN_RTTREFERENCIA_H_INCLUDED

#include "domain_RegistroGenerico.h"

class RTTreferencia : public RegistroGenerico {
    public:
        RTTreferencia(unsigned int clave);
        RTTreferencia();
        ~RTTreferencia();
        virtual int serializar(SerialBuffer *buffer);
        virtual void deserializar(SerialBuffer *buffer);
        unsigned int getRefLista();
        void setRefLista(unsigned int ref);
    private:
        unsigned int refLista;

};

#endif // DOMAIN_RTTREFERENCIA_H_INCLUDED
