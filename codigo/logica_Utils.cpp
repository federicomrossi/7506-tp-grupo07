#include <iostream>
#include <sstream>
#include "logica_Utils.h"

int Utils::splitString(std::string s, char del, std::list<std::string> *ptr){
    std::string s2;
    std::istringstream is(s);
    while (std::getline(is,s2,del)){
        ptr->push_back(s2);
    }
    return 0;
}


int Utils::getClaveFromHeader(std::string header, std::string* clave){
    std::list<std::string> *ptr = new std::list<std::string>;
    Utils::splitString(header,'-',ptr);
    std::ostringstream s;
    s << ptr->front() << "-";
    ptr->pop_front();
    if(ptr->size() == 3){
        ptr->pop_front();
    }
    s << ptr->front() << "-";
    ptr->pop_front();
    s << ptr->front();
    *clave = s.str();
    delete ptr;
    return 0;
}
