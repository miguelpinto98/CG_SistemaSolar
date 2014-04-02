#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
#include "tinyxml2\tinyxml2.h"

using namespace std;
using namespace tinyxml2;

void teste(XMLElement* grupo){

			//transformações para um grupo
			for (XMLElement* transformacao = grupo->FirstChildElement(); (strcmp(transformacao->Value(), "modelos")!=0); transformacao = transformacao->NextSiblingElement()) {
				if(strcmp(transformacao->Value(), "translacao")==0) {
					printf("%s - %s, %s, %s\n", transformacao->Value(), transformacao->Attribute("X"), transformacao->Attribute("Y"), transformacao->Attribute("Z"));}
 
				if(strcmp(transformacao->Value(), "rotacao")==0) {
					printf("%s - %s, %s, %s, %s \n", transformacao->Value(), transformacao->Attribute("angulo"), transformacao->Attribute("eixoX"), transformacao->Attribute("eixoY"), transformacao->Attribute("eixoZ"));}
		 
				if(strcmp(transformacao->Value(), "escala")==0) {
					printf("%s\n", transformacao->Value());}
			}
	

			//para o mesmo grupo, quais os modelos(ficheiros) que recebem as transformações
			for (XMLElement* modelo = grupo->FirstChildElement("modelos")->FirstChildElement("modelo"); modelo; modelo = modelo->NextSiblingElement("modelo")) {
				printf("%s\n", modelo->Attribute("ficheiro"));}
			


			//faz o mesmo de cima para grupos filhos
			if (grupo->FirstChildElement("grupo")) {teste(grupo->FirstChildElement("grupo"));}

			//faz o mesmo de cima para grupos irmãos
		    if (grupo->NextSiblingElement("grupo")) {teste(grupo->NextSiblingElement("grupo"));}
			

}

void readXML(string fxml) {
	XMLDocument doc;
	doc.LoadFile(fxml.c_str());
	XMLElement* cena = doc.FirstChildElement("cena")->FirstChildElement("grupo");
	teste(cena);
}

int main(int argc, char **argv) {
	string xmlmotor="teste63.xml"; //BARRIGAS, apenas mudas aqui o nome do ficheiro e botas para correr :D
	readXML(xmlmotor);
	return 1;
}