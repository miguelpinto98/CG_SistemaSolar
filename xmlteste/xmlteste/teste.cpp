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
				
				//translacao
				if(strcmp(transformacao->Value(), "translacao")==0) {
					float transX, transY, transZ;

					if(transformacao->Attribute("X") == NULL) transX=0;
					else transX= stof(transformacao->Attribute("X"));

					if(transformacao->Attribute("Y") == NULL) transY=0;
					else transY= stof(transformacao->Attribute("Y"));

					if(transformacao->Attribute("Z") == NULL) transZ=0;
					else transZ= stof(transformacao->Attribute("Z"));

					printf("%s - %f, %f, %f\n", transformacao->Value(), transX, transY, transZ);	
				}



				//rotacao
				if(strcmp(transformacao->Value(), "rotacao")==0) {
					float rotAng, rotEixoX, rotEixoY, rotEixoZ;

					if(transformacao->Attribute("angulo") == NULL) rotAng=0;
					else rotAng= stof(transformacao->Attribute("angulo"));

					if(transformacao->Attribute("eixoX") == NULL) rotEixoX=0;
					else rotEixoX= stof(transformacao->Attribute("eixoX"));

					if(transformacao->Attribute("eixoY") == NULL) rotEixoY=0;
					else rotEixoY= stof(transformacao->Attribute("eixoY"));

					if(transformacao->Attribute("eixoZ") == NULL) rotEixoZ=0;
					else rotEixoZ= stof(transformacao->Attribute("eixoZ"));

					printf("%s - %f, %f, %f, %f \n", transformacao->Value(),rotAng, rotEixoX, rotEixoY, rotEixoZ);
				}
		 


				//escala
				if(strcmp(transformacao->Value(), "escala")==0) {
					float escX, escY, escZ;

					if(transformacao->Attribute("angulo") == NULL) escX=0;
					else escX= stof(transformacao->Attribute("angulo"));

					if(transformacao->Attribute("eixoX") == NULL) escY=0;
					else escY= stof(transformacao->Attribute("eixoX"));

					if(transformacao->Attribute("eixoY") == NULL) escZ=0;
					else escZ= stof(transformacao->Attribute("eixoY"));

					printf("%s - %f, %f, %f\n", transformacao->Value(), escX, escY, escZ);
				}
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
	string xmlmotor="outro.xml"; //BARRIGAS, apenas mudas aqui o nome do ficheiro e botas para correr :D
	readXML(xmlmotor);
	return 1;
}