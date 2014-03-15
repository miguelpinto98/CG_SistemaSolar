#include "mainGerador.h"

void plano(float larg, float compr, int cmdh, int cmdv) {
	double h = larg/cmdh, v = compr/cmdv;
	double ax = 0, az=0, x=v, z=h, y=0;
	int i=0;

	for(i=0; i<cmdh; i++) {
		ax=0;
		x=v;
		for(int j=0; j<cmdv; j++) {
			printf("Ponto %d de %d\n",i,j);
			printf("%f %f %f\n",ax,y,az); 
			printf("%f %f %f\n",ax,y,z);
			printf("%f %f %f\n",x,y,z);
			printf("\n");
			
			ax=x;
			x+=v;
		}
		az=z;
		z+=h;
	}

}


int main(int argc, char **argv) {
	/*
	cout << "argc = " << argc << endl; 
	for(int i = 0; i < argc; i++)
		cout << "argv[" << i << "] = " << argv[i] << endl;

	if(argc==7)
		cout << "Sou um Plano ou Paralelipedo" << endl;
	*/

	plano(1,4,2,4);
	
	return 0;
}