#include "logica_Estadista.h"
#include "testEstadista.h"

#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <iostream>


bool comp(const std::pair< std::string, int >& p1, 
	const std::pair< std::string, int >& p2) {
	return p1.second > p2.second;
}



void testEstadista() {

	// std::map< std::string, int > h;

	// std::vector< std::pair< std::string, int > > v;

	// v.push_back(std::make_pair("Jamiroquai", 2));
	// v.push_back(std::make_pair("Empire of the Sun", 4));
	// v.push_back(std::make_pair("Europe", 1));
	// v.push_back(std::make_pair("Keane", 3));

	// v[1].second++;

	// // std::make_heap (v.begin(),v.end(), comp);
	// std::sort(v.begin(), v.end(), &comp);

	// // show content:
	// for (unsigned int i = 0; i < v.size(); i++)
	// 	std::cout << v[i].first << " " << v[i].second << std::endl;


	Estadista e;
	std::vector< std::string > v;

	e.censarBusquedaPorAutor("Keine");
	e.censarBusquedaPorAutor("Jamiroquai");
	e.censarBusquedaPorAutor("Empire of the Sun");
	e.censarBusquedaPorAutor("Europe");
	e.censarBusquedaPorAutor("Empire of the Sun");
	e.censarBusquedaPorAutor("Jamiroquai");
	e.censarBusquedaPorAutor("Keine");
	e.censarBusquedaPorAutor("Empire of the Sun");
	e.censarBusquedaPorAutor("Empire of the Sun");
	e.censarBusquedaPorAutor("Keine");

	e.obtenerAutoresMasBuscados(v, 6);

	std::cout << "Size: " <<  v.size() << std::endl;

	for (unsigned int i = 0; i < v.size(); i++)
		std::cout << v[i] << std::endl;

}
