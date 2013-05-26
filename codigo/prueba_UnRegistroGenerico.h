//
//  UnRegistroGenerico.h
//	[ Insertar documentacion ]
//


#ifndef UN_REGISTRO_GENERICO_H
#define UN_REGISTRO_BENERICO_H

#include "domain_RegistroGenerico.h"


/* ****************************************************************************
 * DEFINICION DE LA CLASE
 * ***************************************************************************/


class UnRegistroGenerico : public RegistroGenerico
{

private:

	int unAtributo;

public:

	// Constructor
	UnRegistroGenerico() { }

	// Serializa el registro.
	// PRE: 'buffer' es el buffer en donde se serializara el registro para 
	// poder ser almacenada en algun medio.
	void serializar(SerialBuffer *buffer)
	{
		// Serializamos clase padre
		RegistroGenerico::serializar(buffer);
		
		// Serializamos atributos propios
		int attr = this->unAtributo;
		buffer->pack(&attr, sizeof(int));
	}

	// Deserializa una lista.
	// PRE: 'buffer' es el buffer en donde se encuentra serializado el registro
	// POST: el estado del registro se actualiza con los datos obtenidos del
	// buffer.
	void deserializar(SerialBuffer *buffer) 
	{ 
		// Deserializamos clase padre
		RegistroGenerico::deserializar(buffer);

		// Deserializamos atributos propios
		int attr;
		buffer->unpack(&attr);
		this->unAtributo = attr;
	}

	void setAtributo(int v)
	{
		this->unAtributo = v;
	}

	int getAtributo()
	{
		return this->unAtributo;
	}

	// Devuelve el tamanio en bytes que ocuparia persistir la clase.
	static size_t getTamanioEnBytes()
	{
		size_t bytes = 0;

		// Contamos el tamanio de la clase padre
		bytes += RegistroGenerico::getTamanioEnBytes();
		
		// Agregamos el tamanio de los atributos de esta clase
		bytes += sizeof(int) + sizeof(unsigned short int);

		return bytes;
	}
};

#endif
