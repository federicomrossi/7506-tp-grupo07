#ifndef INDEXER_H_INCLUDED
#define INDEXER_H_INCLUDED

#include <iostream>
#include "config.h"
#include "logica_IndiceAutor.h"
#include "logica_IndiceTitulo.h"
#include "logica_RTTgenerator.h"

class Indexer{
    public:
        Indexer();
        ~Indexer();
        int indexarCancionesDesde(int mode); //0 scratch ; 1 append
        int eliminarTodo();
    private:
        int estaIndexado(std::string);
        int copyToMaster(std::string from, std::string to);
        int indexarAutores(std::string header, unsigned int songPosition);
        int indexarTitulo(std::string header, unsigned int songPosition);
        int generateRTT(std::string songPath, unsigned int songPosition);
        IndiceAutor *autores;
        IndiceTitulo *titulos;
        RTTgenerator *rtt;
        std::string fromPath;
        std::string destPath;
        std::string masterName;
};



#endif // INDEXER_H_INCLUDED
