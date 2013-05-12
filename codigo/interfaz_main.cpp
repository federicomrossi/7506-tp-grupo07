#include <iostream>
#include "interfaz_Menu.h"
#include "logica_ArbolBmas.h"

using namespace std;

int main()
{
    Menu *m = new Menu;
    while(m->start());
    delete m;
    return 0;
}
