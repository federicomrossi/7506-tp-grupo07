//
//  logica_Estadista.cpp
//  Estadista
//  ***************************************************************************
//
//  Clase que representa el modulo de estadisticas de las busquedas de titulos,
//  autores y y frases.
//



#include <algorithm>
#include "logica_Estadista.h"




/* ****************************************************************************
 * FUNCIONES AUXILIARES DE LA CLASE
 * ***************************************************************************/


// Funcion que compara dos pares (string, int), devolviendo true si el primer
// argumento es mas grande que el segundo, y false en caso contrario;
bool comparador_pairs(const std::pair< std::string, int >& p1, 
	const std::pair< std::string, int >& p2) {
	return p1.second > p2.second;
}


// Funcion que se encarga de censar un elemento en un vector de censos, ambos 
// especificados por el usuario. Además se encarga de mantener ordenado de 
// forma decreciente a dicho vector para su tratamiento externo.
void censar(std::vector< std::pair< std::string, int > >& vCensos,
	const std::string& elementoACensar) {
	// Buscamos el titulo en el vector
	for(unsigned int i = 0; i < vCensos.size(); i++) {

		// Si existe, incrementamos en una unidad al contador de censos
		if(vCensos[i].first == elementoACensar) {
			vCensos[i].second++;

			// Ordenamos el vector
			std::sort(vCensos.begin(), vCensos.end(),
				&comparador_pairs);

			return;
		}
	}

	// Si no existe, lo insertamos como nuevo elemento en el vector
	vCensos.push_back(std::make_pair(elementoACensar, 1));

	// Ordenamos el vector
	std::sort(vCensos.begin(), vCensos.end(), &comparador_pairs);
}


// Funcion que se encarga de insertar en un vector externo 'cantidad' de 
// elementos que fueron buscados, insertandolos en forma decreciente, es decir,
// se inserta en el primer indice aquel que posee el mayor numero de censos.
void obtenerMasBuscados(std::vector< std::pair< std::string, int > >& vCensos,
	std::vector< std::string >& resultados, int cantidad) {

	// Si el vector de censos esta vacio, retornamos sin agregar nada
	if(vCensos.empty()) return;

	// Variable auxiliar
	unsigned int i = 0;

	// Iteramos sobre los elementos desde el que posee mayor numero de censos
	while((i < vCensos.size()) && (i < (unsigned int) cantidad)) {

		// Insertamos en el vector externo
		resultados.push_back(vCensos[i].first);

		i++;
	}
}


// Convierte una cadena a un formato estandar, haciendo que la primer letra
// sea mayuscula y las demas minusuclas.
std::string formatearCadena(const std::string &s) {
	std::string d;

	// Primer letra en mayuscula
	d += (char)toupper(s[0]);

	// Letras restantes en minuscula
	int i;
	for (i = 1; i < (int)s.length(); i++) {
		if (isalpha(s[i]))
			d += (char)tolower(s[i]);
		else
			d += s[i];
	}
	return d;
}






/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
Estadista::Estadista() { }


// Destructor
Estadista::~Estadista() { }


// Censa un titulo para tomarla en cuenta en la estadistica de busquedas
// por titulo. Se le da formato al titulo (primera letra en mayuscula y
// letras restantes en minuscula) para poder censar de forma correcta.
// PRE: 'titulo' es el titulo de la cancion que se busco.
void Estadista::censarBusquedaPorTitulo(const std::string& titulo) {
	
	// Censamos sobre el vector de titulos
	censar(this->titulos, formatearCadena(titulo));
}


// Censa un autor para tomarlo en cuenta en la estadistica de busquedas
// por autor. Se le da formato al autor (primera letra en mayuscula y
// letras restantes en minuscula) para poder censar de forma correcta.
// PRE: 'autor' es el autor de la cancion que se busco.
void Estadista::censarBusquedaPorAutor(const std::string& autor) {
	
	// Censamos sobre el vector de autores
	censar(this->autores, formatearCadena(autor));
}


// Censa una frase para tomarla en cuenta en la estadistica de busquedas
// por frase. Se le da formato a la frase (primera letra en mayuscula y
// letras restantes en minuscula) para poder censar de forma correcta.
// PRE: 'frase' es la frase que se busco.
void Estadista::censarBusquedaPorFrase(const std::string& frase) {
	
	// Censamos sobre el vector de frases
	censar(this->frases, formatearCadena(frase));
}


// Censa un resultado de una busqueda realizada.
// PRE: 'resultado' es un resultado de la busqueda, estando esta formada
// por el autor y el nombre de la cancion. El formato de resultados queda a
// criterio del usuario, debiendose mantener constante el mismo para cada
// cancion. De lo contrario, es decir, si se censa el mismo resultado con
// distinto formato, se los consideraran distintos.
void Estadista::censarResultadoDeBusqueda(const std::string& resultado) {
	
	// Censamos sobre el vector de frases
	censar(this->resultados, resultado);
}


// Permite obtener los titulos mas buscados segun los censos realizados
// hasta el momento.
// PRE: 'resultados' es una referencia a un vector externo vacia en la que
// se insertaran los titulos mas buscados; 'cantidad' es la cantidad maxima
// de titulos mas buscados deseada.
// POST: los resultados se insertan en 'resultados' en orden decreciente de
// cantidad de busquedas realizadas de ese titulo.
void Estadista::obtenerTitulosMasBuscados(std::vector< std::string >& 
	resultados, int cantidad) {

	// Obtenemos mas buscados del vector de titulos
	obtenerMasBuscados(this->titulos, resultados, cantidad);
}


// Permite obtener los autores mas buscados segun los censos realizados
// hasta el momento.
// PRE: 'resultados' es una referencia a un vector externo vacia en la que
// se insertaran los autores mas buscados; 'cantidad' es la cantidad maxima
// de autores mas buscados deseada.
// POST: los resultados se insertan en 'resultados' en orden decreciente de
// cantidad de busquedas realizadas de ese autor.
void Estadista::obtenerAutoresMasBuscados(std::vector< std::string >&
	resultados, int cantidad) {

	// Obtenemos mas buscados del vector de autores
	obtenerMasBuscados(this->autores, resultados, cantidad);
}


// Permite obtener las frases mas buscadas segun los censos realizados
// hasta el momento.
// PRE: 'resultados' es una referencia a un vector externo vacia en la que
// se insertaran las frases mas buscadas; 'cantidad' es la cantidad maxima
// de frases mas buscadas deseada.
// POST: los resultados se insertan en 'resultados' en orden decreciente de
// cantidad de busquedas realizadas de esa frase.
void Estadista::obtenerFrasesMasBuscadas(std::vector< std::string >&
	resultados, int cantidad) {

	// Obtenemos mas buscados del vector de frases
	obtenerMasBuscados(this->frases, resultados, cantidad);
}


// Devuelve el nombre y autor de la cancion que coincidio mas veces en
// todos los resultados de busqueda censados.
// POST: devuelve una cadena cuyo formato depende de como se haya censado
// dicho resultado. Es decir, queda a criterio del usuario decidir como se
// censa, de manera de poder entender que es lo que se devuelve.
// Si no hay ningun tema devuelve una cadena vacia.
void Estadista::obtenerTemaConMayorCoincidencias(
	std::vector< std::string >& coincidentes) {

	// Si no hay resultados en el vector, devolvemos una cadena vacia
	if(this->resultados.empty()) return;

	// Insertamos en el vector externo el primero de los mas coincidentes
	coincidentes.push_back(this->resultados[0].first);

	int censos = this->resultados[0].second; 

	// Corroboramos si hay mas resultados con la misma cantidad de 
	// coincidencias que deba ser devuelto
	for(unsigned int i = 1; i < this->resultados.size(); i++) {
		if(this->resultados[i].second < censos) return;

		// Insertamos en el vector externo de coincidentes
		coincidentes.push_back(this->resultados[i].first);
	}
}

