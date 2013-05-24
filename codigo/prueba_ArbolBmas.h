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


void prueba_ArbolBmas_1()
{
    // Creamos el arbol
    ArbolBmas arbol;
    // Lo abrimos. Si no existe se crea con un nodo raiz inicial.
    arbol.abrir(".arbol.prueba.1");

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

        for(int i=10; i <= 200; i++)
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


void prueba_ArbolBmas_2()
{
    ArbolBmas arbol;
    arbol.abrir(".arbol.prueba.2");

    RegistroGenerico r1;
    r1.setClave(1);
    RegistroGenerico r2;
    r2.setClave(2);
    RegistroGenerico r3;
    r3.setClave(3);
    RegistroGenerico r4;
    r4.setClave(4);
    RegistroGenerico r5;
    r5.setClave(5);
    RegistroGenerico r6;
    r6.setClave(6);
    RegistroGenerico r7;
    r7.setClave(7);

    try {
        
        // Insertamos pares (clave, valor) de prueba para armado del arbol
        arbol.insertar(r1.getClave(), r1);
        arbol.insertar(r2.getClave(), r2);
        arbol.insertar(r3.getClave(), r3);
        arbol.insertar(r4.getClave(), r4);
        arbol.insertar(r5.getClave(), r5);
        arbol.insertar(r6.getClave(), r6);
        arbol.insertar(r7.getClave(), r7);
        arbol.imprimir();

        // Realizamos la busqueda de un registro
        std::cout << std::endl << "BUSQUEDA" << std::endl;

        for(unsigned int i = 0; i <= 10; i++)
        { 
            RegistroGenerico rb;

            if(arbol.buscar(i, rb))
            {
                std::cout << "ENCONTRO EL REGISTRO " << i << std::endl;
                std::cout << "CLAVE: " << rb.getClave() << std::endl;
            }
            else
            {
                std::cout << "NO ENCONTRO EL REGISTRO " << i << std::endl;
                std::cout << "CLAVE: " << rb.getClave() << std::endl;
            }
            std::cout << std::endl;
        }


    }
    catch(char const * e){
        std::cout << e << std::endl;
    }

    // Cerramos el arbol. Esto guarda los metadatos del mismo en disco
    arbol.cerrar();
    // Eliminamos el archivo que contiene el arbol.
    arbol.eliminar();
}