#include <iostream>
#include "interfaz_Menu.h"

#include "prueba_ArbolBmas.h"


int main()
{
    // prueba_ArbolBmas_3();

    Menu *m = new Menu;
    while(m->start());
    delete m;
    return 0;
}
