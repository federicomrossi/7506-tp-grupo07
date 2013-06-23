#include <iostream>
#include "interfaz_Menu.h"
#include "./compresor/testCompresion.h"
#include "testEstadista.h"
#include "./compresor/testPPMC.h"


int main()
{
	// testAritmetico();
	// testEstadista();

	Menu *m = new Menu;
	while(m->start());
	delete m;
	return 0;
    //testAritmetico();
	//
	//
	//
	//Para la segunda parte
    //testPPMC();
}
