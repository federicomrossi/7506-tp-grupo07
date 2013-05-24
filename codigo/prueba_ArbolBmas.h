#include <iostream>
#include "domain_RegistroGenerico.h"
#include "logica_ArbolBmas.h"


/*  INDICACIONES PARA PRUEBAS
 *  
 *  Para cambiar la cantidad de registros en nodos hoja y nodos internos deben
 *  cambiar los valores de las constantes de configuracion ubicadas en el
 *  header logica_ArbolBmas.h.
 *  Recuerden que deben borrar lo compilado con CLEAN y volver a compilar desde
 *  cero para que agarre bien...
 */


void prueba_ArbolBmas()
{
    // Creamos el arbol
    ArbolBmas arbol;
    // Lo abrimos. Si no existe se crea con un nodo raiz inicial.
    arbol.abrir(".arbol");

    // Creamos un unico registro de prueba vacio
    RegistroGenerico reg;
    
    // Insertamos pares (clave, valor) de prueba para armado del arbol
    try {
	    arbol.insertar(4, reg);
	    arbol.insertar(6, reg);
	    arbol.insertar(5, reg);
	    arbol.insertar(2, reg);
	    arbol.insertar(1, reg);
	    arbol.insertar(3, reg);
        arbol.insertar(7, reg);
	    arbol.insertar(8, reg);
	    arbol.insertar(9, reg);

        for(int i=10; i <= 82; i++)
            arbol.insertar(i, reg);

	    arbol.imprimir();
    }
    catch(char const * e){
    	std::cout << e << std::endl;
    }

    // Cerramos el arbol. Esto guarda los metadatos del mismo en disco
    arbol.cerrar();
    // Eliminamos el archivo que contiene el arbol.
    arbol.eliminar();
}
