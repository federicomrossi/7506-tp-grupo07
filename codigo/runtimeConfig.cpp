//
//  runtimeConfig.cpp
//  
//
//  Created by Federico Colangelo on 15/06/13.
//
//

#include "runtimeConfig.h"
#include <sstream>

/* Funcion auxiliar para generalizar la extraccion del parametro.
// No es parte de la interfaz
*/
std::string readParam(std::string param)
{
    std::ifstream configFile;
    configFile.open(ARCH_CONFIG);
    std::string auxString;
    std::string paramName;
    
    while (!configFile.eof()) {
        std::getline(configFile,auxString);
        size_t pos = auxString.find_first_of("=");
        paramName = auxString.substr(0,pos);
        if (paramName==param) {
            auxString = auxString.substr(pos+1);
            return auxString;
        }
    }
    
    std::cerr<<"No se encuentra el parametro buscado"<<std::endl;
    return "";
}

/* Funcion auxiliar para convertir a enteros los parametros numericos.
// No es parte de la interfaz
*/
int stoi(const std::string& s) {
    int i;
    std::stringstream ss(s);
    ss >> i;
    return i;
}



std::string sourcePath()
{
    return readParam("SOURCE_PATH");
}

std::string destPath()
{
    return readParam("DEST_PATH");
}

std::string  testFile()
{
    return readParam("TEST_FILE");
}

std::string testFileTable()
{
    return readParam("TEST_FILE_TABLE");
}

unsigned int maxDedupTimes()
{
    return stoi(readParam("MAX_DUPLICATION_TIMES"));
}

unsigned int hashBlockSize()
{
    return stoi(readParam("HASH_MAX_BLOCK_SIZE"));
}

unsigned int arbolBlockSize()
{
    return stoi(readParam("ARBOL_TAMANIO_BLOQUE_CONFIG"));
}

unsigned int PPMCOrder()
{
    return stoi(readParam("PPMC_ORDER"));
}




