#include <iostream>
#include "interfaz_Menu.h"
#include "logica_ArbolBmas.h"
#include "domain_RegistroGenerico.h"

using namespace std;

int main()
{
<<<<<<< HEAD
    ArbolBmas arbol;
    arbol.abrir("aaa");

    RegistroGenerico reg;
    try {
	    arbol.insertar(4, reg);
	    arbol.insertar(6, reg);
	    arbol.insertar(5, reg);
	    arbol.insertar(2, reg);
	    arbol.insertar(1, reg);
	    arbol.insertar(3, reg);
	    arbol.insertar(7, reg);
	    // arbol.insertar(8, reg);
	    // arbol.insertar(9, reg);
	    // arbol.insertar(10, reg);
	    // arbol.insertar(11, reg);
	    // arbol.insertar(12, reg);
	    // arbol.insertar(13, reg);
	    // arbol.insertar(14, reg);
	    arbol.imprimir();
    }
    catch(char const * e){
    	std::cout << e << std::endl;
    }

=======
    //ArbolBmas arbol;
    //arbol.abrir("aaa");
>>>>>>> 7f70581c25e38c7da24a315ae01546e33faa1f8b
    std::cout << "Volvio" << std::endl;
    //arbol.cerrar();

    Menu *m = new Menu;
    while(m->start());
    delete m;
    return 0;
}
