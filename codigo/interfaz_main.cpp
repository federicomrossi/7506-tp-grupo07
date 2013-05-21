#include <iostream>
#include "interfaz_Menu.h"
#include "logica_ArbolBmas.h"

using namespace std;

int main()
{
    //ArbolBmas arbol;
    //arbol.abrir("aaa");
    std::cout << "Volvio" << std::endl;
    //arbol.cerrar();

    Menu *m = new Menu;
    while(m->start());
    delete m;
    return 0;
}
