#include <iostream>
#include <list>
#include "logica_Buscador.h"
#include "logica_Utils.h"


Buscador::Buscador(){
    destPath="destino/";
    rtt = new RTTgenerator(destPath);
    autores = new IndiceAutor(destPath);
    titulos =  new IndiceTitulo(destPath);
}

Buscador::~Buscador(){
    delete rtt;
    delete autores;
    delete titulos;
}

int Buscador::buscarPorAutor(std::string autor){



    std::list<unsigned int> *listilla;
    listilla = new std::list<unsigned int>;
    autores->recuperar(autor,listilla);
    cout << "Se encontraron los siguientes temas" << std::endl;
    std::ifstream file;
    std::string fileName = destPath + ".master";
    file.open(fileName.c_str());
    std::string header;
    unsigned int largo;
    for (std::list<unsigned int>::iterator it = listilla->begin();it != listilla->end();it++){
        file.seekg(*it);
        file.read((char*)&largo,sizeof(largo));
        getline(file,header);
        cout << *it << std::endl;
        cout << header << std::endl;
    }
    file.close();
    delete listilla;
    return 0;
}

int Buscador::buscarPorTitulo(std::string titulo){
    std::list<unsigned int> *listilla;
    listilla = new std::list<unsigned int>;
    titulos->recuperar(titulo,listilla);
    cout << "Se encontraron los siguientes temas" << std::endl;
    std::ifstream file;
    std::string fileName = destPath + ".master";
    file.open(fileName.c_str());
    std::string header;
    unsigned int largo;
    for (std::list<unsigned int>::iterator it = listilla->begin();it != listilla->end();it++){
        file.seekg(*it);
        file.read((char*)&largo,sizeof(largo));
        getline(file,header);
        cout << *it << std::endl;
        cout << header << std::endl;
    }
    file.close();
    delete listilla;
    return 0;
}

int Buscador::buscarPorFrase(std::string frase){
    return 0;
}
