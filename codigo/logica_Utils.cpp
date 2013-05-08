#include <iostream>
#include <sstream>
#include "Utils.h"

int Utils::splitString(std::string s, char del, std::list<std::string> *ptr){
    std::string s2;
    std::istringstream is(s);
    while (std::getline(is,s2,del)){
        ptr->push_back(s2);
    }
    return 0;
}
