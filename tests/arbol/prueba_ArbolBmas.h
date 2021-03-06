#include <iostream>
#include "prueba_UnRegistroGenerico.h"
#include "domain_AutorReferencias.h"
#include "logica_ArbolBmas.h"
#include "lib_ListaFija.h"


/*  INDICACIONES PARA PRUEBAS
 *
 *  Para cambiar la cantidad de registros en nodos hoja y nodos internos deben
 *  cambiar los valores de las constantes de configuracion ubicadas en el
 *  header logica_ArbolBmas.h.
 *  Recuerden que deben borrar lo compilado con CLEAN y volver a compilar desde
 *  cero para que agarre bien...
 */


void prueba_ArbolBmas_0()
{
    ListaFija< int > *l = new ListaFija< int >(5);

    if(l->estaVacia()) std::cout << "Lista vacia" << std::endl;
    else  std::cout << "Lista no vacia" << std::endl;
    std::cout << "Tamanio: " << l->tamanio() << std::endl;

    l->insertarUltimo(1);
    if(l->estaVacia()) std::cout << "Lista vacia" << std::endl;
    else  std::cout << "Lista no vacia" << std::endl;
    std::cout << "Tamanio: " << l->tamanio() << std::endl;


    // for(int i = 0; i)
}


void prueba_ArbolBmas_1()
{
    // Creamos el arbol
    ArbolBmas< UnRegistroGenerico > arbol;
    // Lo abrimos. Si no existe se crea con un nodo raiz inicial.
    arbol.abrir(".arbol.prueba.1");

    // Creamos un unico registro de prueba vacio
    UnRegistroGenerico reg;

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
    ArbolBmas< UnRegistroGenerico > arbol;
    arbol.abrir(".arbol.prueba.2");

    UnRegistroGenerico r1;
    std::cout << "R PESA: " << r1.getTamanioEnBytes() << std::endl;
    r1.setClave(1);
    std::cout << "R PESA: " << r1.getTamanioEnBytes() << std::endl;
    r1.setAtributo(1);
    std::cout << "R PESA: " << r1.getTamanioEnBytes() << std::endl;
    UnRegistroGenerico r2;
    r2.setClave(2);
    r2.setAtributo(22);
    UnRegistroGenerico r3;
    r3.setClave(3);
    r3.setAtributo(33);
    UnRegistroGenerico r4;
    r4.setClave(4);
    r4.setAtributo(44);
    UnRegistroGenerico r5;
    r5.setClave(5);
    r5.setAtributo(55);
    UnRegistroGenerico r6;
    r6.setClave(6);
    r6.setAtributo(66);
    UnRegistroGenerico r7;
    r7.setClave(7);
    r7.setAtributo(77);

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
            UnRegistroGenerico rb;

            if(arbol.buscar(i, rb))
            {
                std::cout << "ENCONTRO EL REGISTRO " << i << std::endl;
                std::cout << "CLAVE: " << rb.getClave() << std::endl;
                std::cout << "ATTR: " << rb.getAtributo() << std::endl;
            }
            else
            {
                std::cout << "NO ENCONTRO EL REGISTRO " << i << std::endl;
                std::cout << "CLAVE: " << rb.getClave() << std::endl;
                std::cout << "ATTR: " << rb.getAtributo() << std::endl;
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


void prueba_ArbolBmas_3()
{
    ArbolBmas< AutorReferencias > arbol;
    arbol.abrir(".arbol.prueba.3");

    AutorReferencias r1(0);
    
    r1.setCant(1);
    r1.setRef1(2);
    r1.setRef2(3);
    r1.setRef3(4);
    r1.setRef4(5);
    r1.setRef5(6);
    r1.setRefLista(7);
    arbol.insertar(0,r1);
    
    AutorReferencias* a = new AutorReferencias();
    bool b = arbol.buscar(0,*a);
    
    if(b){
        std::cout << "encontrado" << std::endl;
    }else{
        std::cout<< "No encontrado" << std::endl;
    }

    for(int j = 1; j < 150; j++)
    {
        AutorReferencias r1(j);
        arbol.insertar(j,r1);
    }
    
    arbol.imprimir();
    arbol.cerrar();

    std::string comando;
    while(comando != "s")
        getline(std::cin, comando);


    arbol.abrir(".arbol.prueba.3");
    arbol.imprimir();
    
    AutorReferencias* a2 = new AutorReferencias();
    bool c = arbol.buscar(0,*a2);
    
    if(c){
        std::cout << "encontrado" << std::endl;
    }else{
        std::cout<< "No encontrado" << std::endl;
    }


    std::cout << a2->getCant() << std::endl;
    std::cout << a2->getRef1() << std::endl;
    std::cout << a2->getRef2() << std::endl;
    std::cout << a2->getRef3() << std::endl;
    std::cout << a2->getRef4() << std::endl;
    std::cout << a2->getRef5() << std::endl;
    std::cout << a2->getRefLista() << std::endl;


    std::cout << std::endl << "ACTUALIZACION" << std::endl;

    a2->setCant(8);
    a2->setRef1(9);
    a2->setRef2(10);
    a2->setRef3(11);
    a2->setRef4(12);
    a2->setRef5(13);
    a2->setRefLista(14);
    
    if(arbol.actualizar(0, *a2))
        std::cout << "Se actualizó con éxito." << std::endl;
    else
        std::cout << "Falló la actualización" << std::endl;

    AutorReferencias* a3 = new AutorReferencias();
    arbol.buscar(0,*a3);

    std::cout << a3->getCant() << std::endl;
    std::cout << a3->getRef1() << std::endl;
    std::cout << a3->getRef2() << std::endl;
    std::cout << a3->getRef3() << std::endl;
    std::cout << a3->getRef4() << std::endl;
    std::cout << a3->getRef5() << std::endl;
    std::cout << a3->getRefLista() << std::endl;

    arbol.imprimir();

    delete a;
    delete a2;
    delete a3;

    // try {

    //     for(int i = 1; i <= 2; i++)
    //     {
    //         AutorReferencias r(i);
    //         arbol.insertar(r.getClave(), r);
    //     }


    //     for(int i = 30; i <= 60; i++)
    //     {
    //         AutorReferencias r(i);
    //         arbol.insertar(r.getClave(), r);
    //     }

    //     arbol.insertar(r1.getClave(), r1);

    //     arbol.imprimir();

    //     for(unsigned int i = 25; i < 30; i++)
    //     {
    //         AutorReferencias rb;

    //         if(arbol.buscar(i, rb))
    //         {
    //             std::cout << std::endl << "ENCONTRO EL REGISTRO " << i << std::endl;
    //             std::cout << "CLAVE: " << rb.getClave() << std::endl;
    //             std::cout << "ATTR: " << rb.getCant() << std::endl;
    //             std::cout << "ATTR: " << rb.getRef1() << std::endl;
    //             std::cout << "ATTR: " << rb.getRef2() << std::endl;
    //             std::cout << "ATTR: " << rb.getRef3() << std::endl;
    //             std::cout << "ATTR: " << rb.getRef4() << std::endl;
    //             std::cout << "ATTR: " << rb.getRef5() << std::endl;
    //             std::cout << "ATTR: " << rb.getRefLista() << std::endl;
    //             std::cout << std::endl;
    //         }
    //         // else
    //         // {
    //         //     std::cout << "NO ENCONTRO EL REGISTRO " << i << std::endl;
    //         //     std::cout << "CLAVE: " << rb.getClave() << std::endl;
    //         //     std::cout << "ATTR: " << rb.getAtributo() << std::endl;
    //         // }
    //     }
    // }
    // catch(char const * e){
    //     std::cout << e << std::endl;
    // }


    arbol.cerrar();
    arbol.eliminar();
}


void prueba_ArbolBmas_4()
{
    try{

        ArbolBmas< UnRegistroGenerico > arbol1, arbol2;
        arbol1.abrir(".arbol.prueba.4");

        for(int i = 0; i < 200; i++)
        {
            UnRegistroGenerico r;
            r.setClave(i);
            r.setAtributo(i);
            arbol1.insertar(r.getClave(), r);
        }

        arbol1.imprimir();

        arbol1.cerrar();

        arbol2.abrir(".arbol.prueba.4");
        arbol2.imprimir();
        arbol2.cerrar();

        // arbol2.eliminar();
    }
    catch(char const * e)
    {
        std::cout << e << std::endl;
    }
}
