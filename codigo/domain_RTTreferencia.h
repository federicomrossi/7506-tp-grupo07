#ifndef DOMAIN_RTTREFERENCIA_H_INCLUDED
#define DOMAIN_RTTREFERENCIA_H_INCLUDED

#include "domain_RegistroGenerico.h"

/**
*   Autor: Pablo Rodriguez
*
*   RTTreferncia representa un par de (idPalabra, refLista)
*
*   Es lo que se inserta en el arbol de RTT.
*/
class RTTreferencia : public RegistroGenerico {
    public:
        RTTreferencia(unsigned int clave);
        RTTreferencia();
        ~RTTreferencia();
        virtual int serializar(SerialBuffer *buffer);
        virtual void deserializar(SerialBuffer *buffer);
        unsigned int getRefLista();
        void setRefLista(unsigned int ref);

        // Devuelve el tamanio en bytes que ocuparia persistir la clase.
        static size_t getTamanioEnBytes();

    private:
        unsigned int refLista;

};

#endif // DOMAIN_RTTREFERENCIA_H_INCLUDED
