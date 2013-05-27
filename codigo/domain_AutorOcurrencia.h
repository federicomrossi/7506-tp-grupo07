#ifndef DOMAIN_OCURRENCIAAUTOR_H_INCLUDED
#define DOMAIN_OCURRENCIAAUTOR_H_INCLUDED
#include "logica_Comparable.h"
#include <iostream>



/**
*   Autor: Pablo Rodriguez
*
*   AutorOcurrencia representa un par de (idAutor, refDocumento)
*/
class AutorOcurrencia : public Comparable{
    public:
        AutorOcurrencia(unsigned int autorId, unsigned int documentoId);
        AutorOcurrencia();
        virtual ~AutorOcurrencia();
        virtual int comparar(Comparable *c) const;
        unsigned int getAutorId() const;
        unsigned int getDocumentoId() const;
        friend std::istream& operator >> (std::istream &out, AutorOcurrencia &ocur);
        friend std::ostream& operator << (std::ostream &out, AutorOcurrencia &ocur);
    private:
        unsigned int documentoId;
        unsigned int autorId;

};

#endif // DOMAIN_OCURRENCIAAUTOR_H_INCLUDED
