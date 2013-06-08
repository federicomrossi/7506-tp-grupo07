//
//	config.h
//	ARCHIVO DE CONFIGURACIÓN
//	***************************************************************************
//	
//	En este archivo se encuentran los parametros configurables del programa.
//


#ifndef CONFIG_H_
#define CONFIG_H_


// Directorio de temas de canciones
#define SOURCE_PATH "../temas"

// Directorio destino en donde se generarán archivos de persistencia de las
// distintas estructuras, como así también el archivo salida.out en el cual
// se depositan las letras de canciones, resultado de la busqueda
#define DEST_PATH "./destino/"

// Tamano del bloque en el hash
#define HASH_MAX_BLOCK_SIZE (128)

// Constante para el tamanio de bloque utilizado por los nodos del Arbol B+
#define ARBOL_TAMANIO_BLOQUE_CONFIG
const int ARBOL_TAMANIO_BLOQUE = 256;

//Archivo para guardar los bloques
#define TEST_FILE "./test_file_TESTBLOCKFILE"

// Archivo para guardar la tabla de referencia
#define TEST_FILE_TABLE "./test_file_TESTTABLEFILE"

//Maximo numero de veces que se puede dispersar la tabla
#define MAX_DUPLICATION_TIMES (25)
#endif
