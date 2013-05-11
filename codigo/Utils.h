#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <iostream>
#include <list>

class Utils{
    public:
        static int splitString(std::string s, char delimitador, std::list<std::string> *ptr);
        static int getClaveFromHeader(std::string header, std::string* clave);
};

#endif // UTILS_H_INCLUDED
