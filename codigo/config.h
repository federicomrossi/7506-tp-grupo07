/*
 * config.h
 *
 *  Created on: May 14, 2013
 *      Author: rburdet
 */
/*
 * 			ARCHIVO DE CONFIGURACION PARA LA COMPILACION
 *
 * */


#ifndef CONFIG_H_
#define CONFIG_H_

#define SOURCE_PATH "../temas"
#define DEST_PATH "./destino/"

//Archivo para guardar los bloques
#define TEST_FILE "./test_file_TESTBLOCKFILE"

// Archivo para guardar la tabla de referencia
#define TEST_FILE_TABLE "./test_file_TESTTABLEFILE"

// Tamano del bloque
#define HASH_MAX_BLOCK_SIZE (128)

// Constante para el tamanio de bloque utilizado por los nodos en el arbol
#define ARBOL_TAMANIO_BLOQUE_CONFIG
const int ARBOL_TAMANIO_BLOQUE = 256;

#endif /* CONFIG_H_ */
