#include "Contexto.h"
#include "CtxM1.h"
#include "CtxN.h"
#include "Ctx0.h"
#include "letraFrec.h"
#include <string>
#include <list>
#include <iostream>
#include <map>
using namespace std;

int main(){
	map< string,list<letraFrec> > aux;
	list<letraFrec> lista;
	Ctx0* primero= new Ctx0();
	primero->aumentarFrec("a");
	CtxM1 * cero = new CtxM1();
	cero->aumentarFrec("z");
	letraFrec letra("a");
	lista.push_back(letra);
	aux.insert(pair<string, list <letraFrec> >("abc",lista));
	primero->aumentarFrec("z");
	primero->aumentarFrec("z");
	primero->aumentarFrec("z");
	primero->aumentarFrec("z");
	primero->aumentarFrec("z");
	primero->aumentarFrec("c");
	primero->aumentarFrec("c");
	primero->aumentarFrec("b");
	primero->aumentarFrec("b");
	primero->aumentarFrec("a");
	primero->aumentarFrec("a");
	cout << "la frec es : " << primero->getFrec("z")<< endl;
	cout << "la frec es : " << primero->getFrec("c")<< endl;
	cout << "la frec es : " << primero->getFrec("b")<< endl;
	cout << "la frec es : " << primero->getFrec("a")<< endl;
	cout << " el total es: " << primero->getTotal(lista)<<endl;
	map< string, list<letraFrec> >::iterator it = aux.begin();
	list <letraFrec> lista2; 
	lista2= it->second;
	list<letraFrec>::iterator itt = lista2.begin();
	cout << "a ver : " << it->first <<endl;
	cout << " el (primer valor de esos es " << itt->getLetra() << endl;
	cout << " y su frecuencia es " << itt->getFrec() << endl;
	return 0;

}
