//
//  RegistroGenerico.h
//	[ Insertar documentacion ]
//


#ifndef REGISTRO_GENERICO_H
#define REGISTRO_BENERICO_H


#include "fisica_SerialBuffer.h"



/* ****************************************************************************
 * DEFINICION DE LA CLASE
 * ***************************************************************************/


class RegistroGenerico
{

private:

	unsigned int clave;			// Identificador del registro

public:

	// Constructor
	RegistroGenerico() { }

	// Setea el identificador (clave) del registro
	void setClave(unsigned int clave) { this->clave = clave; }

	// Devuelve el identificador (clave) del registro
	unsigned int getClave() { return this->clave; }

	// Serializa el registro.
	// PRE: 'buffer' es el buffer en donde se serializara el registro para 
	// poder ser almacenada en algun medio.
	void serializar(SerialBuffer *buffer) { }

	// Deserializa una lista.
	// PRE: 'buffer' es el buffer en donde se encuentra serializado el registro
	// POST: el estado del registro se actualiza con los datos obtenidos del
	// buffer.
	void deserializar(SerialBuffer *buffer) { }
};

#endif
