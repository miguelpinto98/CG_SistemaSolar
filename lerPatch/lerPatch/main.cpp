#include <string>
#include <iostream>
#include <fstream>

using namespace std;


int lerPatch(string fl) {
	string line, token, delimiter = ",";
	int pos, nrPatches, nrVertices;
	int p=0, v=0;
	double a;
	ifstream file(fl);

	if(file.is_open()) {

			if(getline(file,line) && p==0) {
				nrPatches=atoi(line.c_str());
				printf("%d\n", nrPatches);
				p=1;
			}

			for (int i=0; i<nrPatches && getline(file, line); i++){
				for(int j=0; j<16;j++){
					pos = line.find(delimiter);
					token = line.substr(0,pos);
					a = atof(token.c_str());
					line.erase(0, pos + delimiter.length());
					printf("%f - ",a);
				}
			}


			if(getline(file,line) && v==0) {
				nrVertices=atoi(line.c_str());
				printf("%d\n", nrVertices);
				v=1;
			}

			for (int i=0; i<nrVertices && getline(file, line); i++){
				for(int j=0; j<3;j++){
					pos = line.find(delimiter);
					token = line.substr(0,pos);
					a = atof(token.c_str());
					line.erase(0, pos + delimiter.length());
					printf("%f - ",a);
				}
			}
	
		
		file.close();
		return 0;
	} 
	
	else { cout << "Nao foi possivel ler o arquivo" << endl; return -1; }
} 


int main(int argc, char **argv) {
	lerPatch("teapot.patch");

	return 1;
}