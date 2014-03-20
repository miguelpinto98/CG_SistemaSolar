#include "tinyxml2.h"
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>
#include <iostream>


using namespace std;
using namespace tinyxml2;

void teste1(char* xmlFile){	
	XMLDocument doc;
	doc.LoadFile(xmlFile);
	doc.Parse(xmlFile);


	XMLElement* raiz = doc.FirstChildElement("cena");
	XMLElement* modelo = raiz->FirstChildElement("modelo");
	printf("ok");


	/*for (XMLElement* modelo = raiz->FirstChildElement("modelo"); modelo; modelo = modelo->NextSiblingElement("modelo"))
	{
		printf("cena");
		string filename = modelo->Attribute("ficheiro");
		printf("ATRIBUTO: %s\n\n", filename.c_str());
	}*/
	
}


int main( int argc, const char ** argv ){
	teste1("motor.xml");
	
}
