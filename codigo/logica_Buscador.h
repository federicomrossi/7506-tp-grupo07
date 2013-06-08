#ifndef BUSCADOR_H_INCLUDED
#define BUSCADOR_H_INCLUDED

#include "config.h"
#include "logica_IndiceAutor.h"
#include "logica_IndiceTitulo.h"
#include "logica_RTTgenerator.h"


/**
*   Autor: Pablo Rodriguez
*
*   Es la clase madre en donde se resuelven las busquedas por autor, titulo y RTT. Delega parte de su
*   comportamiento en los diferentes indices.
*/
class Buscador{
    public:
        Buscador();
        ~Buscador();
        int buscarPorAutor(std::string autor);
        int buscarPorTitulo(std::string titulo);
        int buscarPorFrase(std::string frase);
        int listarTodo();
    private:
        int imprimirCancion(unsigned int ref);
        IndiceAutor *autores;
        IndiceTitulo *titulos;
        RTTgenerator *rtt;
        std::string destPath;
        std::string outName;

};


#endif // BUSCADOR_H_INCLUDED
