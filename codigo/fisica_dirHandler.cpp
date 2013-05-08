/*
 * dirHandler.cpp
 *
 *  Created on: Apr 24, 2013
 *      Author: rburdet
 */

#include "dirHandler.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

dirHandler::dirHandler(const char* path) {
	this->fileList= new list<string>;
	this->initialPathName=path;
}

dirHandler::~dirHandler() {
	delete this->fileList;
}

list<string>* dirHandler::getFileList() {
	return this->fileList;
}

void dirHandler::setPath(const char* path){
	this->initialPathName=path;
}

/*
 *  Metodo encargado de recorrer recursivamente el directorio, haciendo uso de la libreria de C dirent.h
 * 	En un atributo protegido guarda una lista de los nombres de los temas del directorio elegido, y de todos
 * 	los temas en los subdirectorios. El nombre ademas incluye ademas el pathname, por ejemplo para el archivo
 * 	"Yesterday.txt" guardara "home/Usuario/music/lyrics/The_Beatles/Yesterday.txt".
 *
 */
void dirHandler::getFiles(const char* dir){
	DIR *dirStream;
	struct dirent *dirEntry;
	dirStream = opendir(dir);

	if (! dirStream)
		return ;
	while (dirEntry = readdir(dirStream)){
		if (dirEntry->d_name[0]=='.')
			continue;
		if (dirEntry->d_type == DT_DIR){
			char tmpName[strlen(dir)+strlen(dirEntry->d_name)+1];
			sprintf(tmpName,"%s/%s", dir, dirEntry->d_name);
			this->setPath(tmpName);
			this->getFiles(tmpName);
		}
		else{
			string actualPath = dir;
			actualPath += "/";
			actualPath += dirEntry->d_name;
			this->fileList->push_back(actualPath);
		}
	}
	(void) closedir(dirStream);
}
