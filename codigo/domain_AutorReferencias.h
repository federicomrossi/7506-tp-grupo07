#ifndef DOMAIN_AUTORREFERENCIAS_H_INCLUDED
#define DOMAIN_AUTORREFERENCIAS_H_INCLUDED

#include "domain_RegistroGenerico.h"


/**
*   Autor: Pablo Rodriguez
*
*   AutorReferencias representa un de (idAutor, ref1, ref2, ref3,ref4,ref5,refLista)
*   Es lo que se inserta en el arbol de indice de autor
*/
class AutorReferencias : public RegistroGenerico {
    public:
        AutorReferencias(unsigned int clave);
        AutorReferencias();
        ~AutorReferencias();
        virtual int serializar(SerialBuffer *buffer);
        virtual void deserializar(SerialBuffer *buffer);
        unsigned int getRef1();
        unsigned int getRef2();
        unsigned int getRef3();
        unsigned int getRef4();
        unsigned int getRef5();
        unsigned int getRefLista();
        unsigned int getCant();
        unsigned int* getRefs();
        void setRef1(unsigned int ref);
        void setRef2(unsigned int ref);
        void setRef3(unsigned int ref);
        void setRef4(unsigned int ref);
        void setRef5(unsigned int ref);
        void setRefLista(unsigned int ref);
        void setCant(unsigned int cant);

        // Devuelve el tamanio en bytes que ocuparia persistir la clase.
        static size_t getTamanioEnBytes();

    private:
        unsigned int refs[5];
        unsigned int refLista;
        unsigned int cant;

};

#endif // DOMAIN_AUTORREFERENCIAS_H_INCLUDED
