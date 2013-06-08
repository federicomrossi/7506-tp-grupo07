#include <iostream>
#include <list>
#include "logica_Buscador.h"
#include "logica_Utils.h"


Buscador::Buscador(){
    destPath= DEST_PATH;
    this->outName=destPath+"salida.out";
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
    remove(outName.c_str());
    if(listilla->size() == 0){
        cout << "No se encontraron temas" << std::endl;
        delete listilla;
        return 0;
    }
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
        cout << header << std::endl;
        imprimirCancion(*it);
    }
    cout << "Las letras fueron impresas en el archivo salida.out de su carpeta de destino" << std::endl;
    file.close();
    delete listilla;
    return 0;
}

int Buscador::buscarPorTitulo(std::string titulo){
    std::list<unsigned int> *listilla;
    listilla = new std::list<unsigned int>;
    titulos->recuperar(titulo,listilla);
    remove(outName.c_str());
    if(listilla->size() == 0){
        cout << "No se encontraron temas" << std::endl;
        delete listilla;
        return 0;
    }
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
        cout << header << std::endl;
        imprimirCancion(*it);
    }
    cout << "Las letras fueron impresas en el archivo salida.out de su carpeta de destino" << std::endl;
    file.close();
    delete listilla;
    return 0;
}

int Buscador::buscarPorFrase(std::string frase){
    std::list<unsigned int> *listilla;
    listilla = new std::list<unsigned int>;
    rtt->recuperar(frase,listilla);
    remove(outName.c_str());
    if(listilla->size() == 0){
        cout << "No se encontraron temas" << std::endl;
        delete listilla;
        return 0;
    }
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
        cout << header << std::endl;
        imprimirCancion(*it);
    }
    cout << "Las letras fueron impresas en el archivo salida.out de su carpeta de destino" << std::endl;
    file.close();
    delete listilla;
    return 0;
}

int Buscador::imprimirCancion(unsigned int ref){
    std::ifstream file;
    std::ofstream out;
    std::string fileName = destPath + ".master";
    file.open(fileName.c_str());
    out.open(outName.c_str(),std::fstream::app);
    unsigned int largo;
    file.seekg(ref);
    file.read((char*)&largo,sizeof(largo));
    for(unsigned int i=0;i<largo;i++){
        char c;
        file.read(&c,sizeof(char));
        out.write(&c,sizeof(char));
    }
    out << std::endl;
    file.close();
    out.close();
    return 0;
}

int Buscador::listarTodo(){
    std::ifstream file;
    std::string fileName = destPath + ".master";
    file.open(fileName.c_str());
    if(!file.good()){
         cout << "No hay temas indexados." << std::endl;
         return 0;
    }
    std::string header;
    unsigned int largo =0;
    unsigned int pos=0;
    int flag = 0;
    cout << "Se encuentran indexados los siguientes temas:" << std::endl;
    file.read((char*)&largo,sizeof(largo));
    while(!file.eof()){
        flag = 1;
        pos = file.tellg();
        pos = pos + largo;
        getline(file,header);
        cout << header << std::endl;
        file.seekg(pos);
        file.read((char*)&largo,sizeof(largo));
    }
    if(!flag){
        cout << "No hay temas indexados." << std::endl;
    }
    return 0;
}
