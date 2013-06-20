#include <string>
#include "Ctx1.h"

using namespace std;

Ctx1::Ctx1(){
	this->ordenContexto=1;	
}

unsigned int Ctx1::getFrec(string letra, string letrasContexto){
	return 0;
}

unsigned int Ctx1::getTotal(list<letraFrec>, string letrasContexto){
return 0;}


//Al mapa llamado distintosContextos que relacione un contexto con una lista de caracteres con su frecuencia, se le asigna un iterador, 
//si se encuentra el contexto deseado, busco con el iterador it2 sobre la clave que devolvio el contexto (it->first) si matchea, sumo uno, si no se agrega y se emite escape.
//si no se encuentra el contexto deseado, se lo crea con un caracter de escape y se va al contexto mas bajo
//TODO: esto
void Ctx1::aumentarFrec(string letra, string letrasContexto){ 
	map<string, list<letraFrec> >::iterator it;
	list<letraFrec>::iterator it2;
	list<letraFrec> lista;
	for (it = distintosContextos.begin(); it != distintosContextos.end(); it++){
		if (it->first == letrasContexto){
			lista=it->second;		
			for (it2=lista.begin();it2!=lista.end();it2++){
				if (it2->getLetra()==letra){
					it2->aumentarFrec();
				}else{
					lista.push_back(letra);
				}
			}
		}else{
			letraFrec esc("ESC");
			lista.push_back(esc);
			distintosContextos.insert(pair<string, list <letraFrec> >(letrasContexto,lista));
		}

	}
}

void Ctx1::exclusion(list<letraFrec>){  }
