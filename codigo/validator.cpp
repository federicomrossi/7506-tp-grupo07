#include "validator.h"
#include <iostream>
#include <sstream>


int Validator::validateOpcion(std::string op){
    std::stringstream s(op);
    int i;
    if ( (s >> i).fail() || (i <1 && i>6)){
        return 0;
    }else{
        return i;
    }

}
