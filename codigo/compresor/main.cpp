#include "Contexto.h"
#include "CtxM1.h"
#include "CtxN.h"
#include "Ctx0.h"
#include "letraFrec.h"
#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <map>
using namespace std;

int main(){
	Ctx0* Cero = new Ctx0();
	FILE *pfile;
	char c;
	pfile= fopen("a.txt","r");
	for(int i=0; c!=EOF ; i++){
	c = fgetc (pfile);
	cout<<"letra: " <<c<< " tiene frecuencia: "<<Cero->getFrec(c,"a")<<endl;
	}
	fclose (pfile);
	cout << "la frecuencia total del contexto 0 sin exclusion es "<< Cero->getTotal()<<endl;
	cout << "ver que el resultado es FrecCaracterN + FrecEscape + FrecEOF ( igual a 1 )" <<endl;

//string aux = "abcddefghiiiioiiiiii" ;
//for (unsigned int i = 0 ; i< aux.length() ; i++){
//	cout<<"letra: " <<aux[i]<< " tiene frecuencia: "<<Cero->getFrec(aux[i])<<endl;
//}

//	map< string,list<letraFrec> > aux;
//	list<letraFrec> lista;
//	Ctx0* primero= new Ctx0();
//	primero->aumentarFrec("a");
//	CtxM1 * cero = new CtxM1();
//	cero->aumentarFrec("z");
//	letraFrec letra("a");
//	lista.push_back(letra);
//	aux.insert(pair<string, list <letraFrec> >("abc",lista));
//	primero->aumentarFrec("z");
//	primero->aumentarFrec("z");
//	primero->aumentarFrec("z");
//	primero->aumentarFrec("z");
//	primero->aumentarFrec("z");
//	primero->aumentarFrec("c");
//	primero->aumentarFrec("c");
//	primero->aumentarFrec("b");
//	primero->aumentarFrec("b");
//	primero->aumentarFrec("a");
//	primero->aumentarFrec("a");
//	cout << "la frec es : " << primero->getFrec("z")<< endl;
//	cout << "la frec es : " << primero->getFrec("c")<< endl;
//	cout << "la frec es : " << primero->getFrec("b")<< endl;
//	cout << "la frec es : " << primero->getFrec("a")<< endl;
//	cout << " el total es: " << primero->getTotal(lista)<<endl;
//	map< string, list<letraFrec> >::iterator it = aux.begin();
//	list <letraFrec> lista2; 
//	lista2= it->second;
//	list<letraFrec>::iterator itt = lista2.begin();
//	cout << "a ver : " << it->first <<endl;
//	cout << " el (primer valor de esos es " << itt->getLetra() << endl;
//	cout << " y su frecuencia es " << itt->getFrec() << endl;
	return 0;

}
