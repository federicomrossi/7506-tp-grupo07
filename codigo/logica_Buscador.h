#ifndef BUSCADOR_H_INCLUDED
#define BUSCADOR_H_INCLUDED

#include "logica_IndiceAutor.h"
#include "logica_IndiceTitulo.h"
#include "logica_RTTgenerator.h"

class Buscador{
    public:
        Buscador();
        ~Buscador();
        int buscarPorAutor(std::string autor);
        int buscarPorTitulo(std::string titulo);
        int buscarPorFrase(std::string frase);
    private:
        IndiceAutor *autores;
        IndiceTitulo *titulos;
        RTTgenerator *rtt;
        std::string destPath;

};


#endif // BUSCADOR_H_INCLUDED
