//
//  logica_Estadista.h
//  Estadista
//  ***************************************************************************
//
//  Clase que representa el modulo de estadisticas de las busquedas de titulos,
//  autores y y frases.
//



#ifndef ESTADISTA_H
#define ESTADISTA_H


#include <string>
#include <vector>
#include <utility>




/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class Estadista
{

private:

	// Vector de pares (titulo, veces_que_fue_censado) 
	std::vector< std::pair< std::string, int > > titulos;
	// Vector de pares (autores, veces_que_fue_censado) 
	std::vector< std::pair< std::string, int > > autores;
	// Vector de pares (frases, veces_que_fue_censado) 
	std::vector< std::pair< std::string, int > > frases;
	// Vector de pares (resultados, veces_que_fue_censado) 
	std::vector< std::pair< std::string, int > > resultados;

public:

	// Constructor
	Estadista();

	// Destructor
	~Estadista();

	// Censa un titulo para tomarla en cuenta en la estadistica de busquedas
	// por titulo.
	// PRE: 'titulo' es el titulo de la cancion que se busco.
	void censarBusquedaPorTitulo(const std::string& titulo);

	// Censa un autor para tomarlo en cuenta en la estadistica de busquedas
	// por autor.
	// PRE: 'autor' es el autor de la cancion que se busco.
	void censarBusquedaPorAutor(const std::string& autor);

	// Censa una frase para tomarla en cuenta en la estadistica de busquedas
	// por frase.
	// PRE: 'frase' es la frase que se busco.
	void censarBusquedaPorFrase(const std::string& frase);

	// Censa un resultado de una busqueda realizada.
	// PRE: 'resultado' es un resultado de la busqueda, estando esta formada
	// por el autor y el nombre de la cancion. El formato de resultados queda a
	// criterio del usuario, debiendose mantener constante el mismo para cada
	// cancion. De lo contrario, es decir, si se censa el mismo resultado con
	// distinto formato, se los consideraran distintos.
	void censarResultadoDeBusqueda(const std::string& resultado);

	// Permite obtener los titulos mas buscados segun los censos realizados
	// hasta el momento.
	// PRE: 'resultados' es una referencia a un vector externo vacia en la que
	// se insertaran los titulos mas buscados; 'cantidad' es la cantidad maxima
	// de titulos mas buscados deseada.
	// POST: los resultados se insertan en 'resultados' en orden decreciente de
	// cantidad de busquedas realizadas de ese titulo.
	void obtenerTitulosMasBuscados(std::vector< std::string >& resultados,
		int cantidad);

	// Permite obtener los autores mas buscados segun los censos realizados
	// hasta el momento.
	// PRE: 'resultados' es una referencia a un vector externo vacia en la que
	// se insertaran los autores mas buscados; 'cantidad' es la cantidad maxima
	// de autores mas buscados deseada.
	// POST: los resultados se insertan en 'resultados' en orden decreciente de
	// cantidad de busquedas realizadas de ese autor.
	void obtenerAutoresMasBuscados(std::vector< std::string >& resultados,
		int cantidad);

	// Permite obtener las frases mas buscadas segun los censos realizados
	// hasta el momento.
	// PRE: 'resultados' es una referencia a un vector externo vacia en la que
	// se insertaran las frases mas buscadas; 'cantidad' es la cantidad maxima
	// de frases mas buscadas deseada.
	// POST: los resultados se insertan en 'resultados' en orden decreciente de
	// cantidad de busquedas realizadas de esa frase.
	void obtenerFrasesMasBuscadas(std::vector< std::string >& resultados,
		int cantidad);
	
	// Devuelve el nombre y autor de la cancion que coincidio mas veces en
	// todos los resultados de busqueda censados.
	// POST: devuelve una cadena cuyo formato depende de como se haya censado
	// dicho resultado. Es decir, queda a criterio del usuario decidir como se
	// censa, de manera de poder entender que es lo que se devuelve.
	void obtenerTemaConMayorCoincidencias(std::vector< std::string >& 
		coincidentes);
};

#endif
