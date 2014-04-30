#include <string>
#include <iostream>
#include <fstream>
#include <fstream>
#include <vector>
#include "LinhaIndice.h"
#include "Vertices.h"
#include "Ponto.h"


using namespace std;


int lerPatch(string fl) {
	Vertices vertices;
	string line, token, delimiter = ",";
	int pos, nrPatches, nrVertices;
	int p=0, v=0;
	float a, b, c;
	ifstream file(fl);

	if(file.is_open()) {

			if(getline(file,line) && p==0) {
				nrPatches=atoi(line.c_str());
				p=1;
			}

			for (int i=0; i<nrPatches && getline(file, line); i++){
				for(int j=0; j<16;j++){
					pos = line.find(delimiter);
					token = line.substr(0,pos);
					a = atof(token.c_str());
					line.erase(0, pos + delimiter.length());
				}
			}


			if(getline(file,line) && v==0) {
				nrVertices=atoi(line.c_str());
				v=1;
			}

			for (int i=0; i<nrVertices && getline(file, line); i++){
					pos = line.find(delimiter);
					token = line.substr(0,pos);
					a = atof(token.c_str());
					line.erase(0, pos + delimiter.length());
					

					pos = line.find(delimiter);
					token = line.substr(0,pos);
					b = atof(token.c_str());
					line.erase(0, pos + delimiter.length());

					pos = line.find(delimiter);
					token = line.substr(0,pos);
					c = atof(token.c_str());
					line.erase(0, pos + delimiter.length());
					
					Ponto ponto(a,b,c);
					vertices.adicionaPonto(ponto);
			}				

		/*	for(int i=0; i<vertices.getPontos().size(); i++){
				printf("%f\n", vertices.getPontos()[i].getX());
				printf("%f\n", vertices.getPontos()[i].getY());
				printf("%f\n", vertices.getPontos()[i].getZ());
			}*/
	
		
		file.close();
		return 0;
	} 
	
	else { cout << "Nao foi possivel ler o arquivo" << endl; return -1; }
} 


int main(int argc, char **argv) {
	lerPatch("teapot.patch");

	return 1;
}