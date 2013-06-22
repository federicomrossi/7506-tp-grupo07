#include <iostream>
#include "interfaz_Menu.h"


#include "testCompresion.h"
#include "testEstadista.h"


int main()
{
	// testAritmetico();
	// testEstadista();

	Menu *m = new Menu;
	while(m->start());
	delete m;
	return 0;
}
