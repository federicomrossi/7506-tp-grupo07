#include <iostream>
#include "Menu.h"

using namespace std;

int main()
{
    Menu *m = new Menu;
    while(m->start());
    delete m;
    return 0;
}
