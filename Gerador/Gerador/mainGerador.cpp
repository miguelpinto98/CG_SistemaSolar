#include "mainGerador.h"

void plano(float compr, float larg, int cmdh, int cmdv) {
	double x, y=-(larg/2), z=y;
	double vr=compr/cmdv, hr=larg/cmdh;
	double ax, ay=y+hr, az=larg/2;
	int i,j;

	ofstream file("plano.3d");
	y=larg/2, ay=-y;
	z=-(larg/2), az=z+hr;

	for(i=0; i<cmdh; i++) {
		x=-(compr/2);
		ax=x+vr;
		for(j=0; j<cmdv; j++) {
			printf("%f %f %f\n",x,ay,z); file << x << "," << ay << ","<< z << endl;
			printf("%f %f %f\n",ax,ay,z); file << ax << "," << ay << ","<< z << endl;
			printf("%f %f %f\n",ax,ay,az); file << ax << "," << ay << ","<< az << endl;

			printf("%f %f %f\n",x,ay,z); file << x << "," << ay << ","<< z << endl;
			printf("%f %f %f\n",ax,ay,az); file << ax << "," << ay << ","<< az << endl;
			printf("%f %f %f\n",x,ay,az); file << x << "," << ay << ","<< az << endl;

			x=ax;
			ax+=vr;
		}
		z=az;
		az+=hr;
	}
	file.close();
}


void paralelipipedo(double compr, double larg, double alt, int cmdh, int cmdv) {
	double x, y=-(larg/2), z=y;
	double vr=compr/cmdv, hr=larg/cmdh;
	double ax, ay=y+hr, az=larg/2;
	int i,j;
	ofstream file("paralelipipedo.3d");

	//BACK AND FRONT
	for(i=0; i<cmdh; i++) {
		x=-(compr/2);
		ax=x+vr;
		for(j=0; j<cmdv; j++) {
			printf("%f %f %f\n",x,y,z); file << x << "," << y << ","<< z << endl;
			printf("%f %f %f\n",ax,y,z); file << ax << "," << y << ","<< z << endl;
			printf("%f %f %f\n",ax,ay,z); file << ax << "," << ay << ","<< z << endl;

			printf("%f %f %f\n",x,y,z); file << x << "," << y << ","<< z << endl;
			printf("%f %f %f\n",ax,ay,z); file << ax << "," << ay << ","<< z << endl;
			printf("%f %f %f\n",x,ay,z); file << x << "," << ay << ","<< z << endl;

			printf("%f %f %f\n",x,y,az); file << x << "," << y << ","<< az << endl;
			printf("%f %f %f\n",ax,y,az); file << ax << "," << y << ","<< az << endl;
			printf("%f %f %f\n",ax,ay,az); file << ax << "," << ay << ","<< az << endl;

			printf("%f %f %f\n",x,y,az); file << x << "," << y << ","<< az << endl;
			printf("%f %f %f\n",ax,ay,az); file << ax << "," << ay << ","<< az << endl;
			printf("%f %f %f\n",x,ay,az); file << x << "," << ay << ","<< az << endl;

			x=ax;
			ax+=vr;
		}
		y=ay;
		ay+=hr;
	}
	
	//TOP AND DOWN
	y=larg/2, ay=-y;
	z=-(larg/2), az=z+hr;

	for(i=0; i<cmdh; i++) {
		x=-(compr/2);
		ax=x+vr;
		for(j=0; j<cmdv; j++) {
			printf("%f %f %f\n",x,y,z); file << x << "," << y << ","<< z << endl;
			printf("%f %f %f\n",ax,y,z); file << ax << "," << y << ","<< z << endl;
			printf("%f %f %f\n",ax,y,az); file << ax << "," << y << ","<< az << endl;

			printf("%f %f %f\n",x,y,z); file << x << "," << y << ","<< z << endl;
			printf("%f %f %f\n",ax,y,az); file << ax << "," << y << ","<< az << endl;
			printf("%f %f %f\n",x,y,az); file << x << "," << y << ","<< az << endl;

			printf("%f %f %f\n",x,ay,z); file << x << "," << ay << ","<< z << endl;
			printf("%f %f %f\n",ax,ay,z); file << ax << "," << ay << ","<< z << endl;
			printf("%f %f %f\n",ax,ay,az); file << ax << "," << ay << ","<< az << endl;

			printf("%f %f %f\n",x,ay,z); file << x << "," << ay << ","<< z << endl;
			printf("%f %f %f\n",ax,ay,az); file << ax << "," << ay << ","<< az << endl;
			printf("%f %f %f\n",x,ay,az); file << x << "," << ay << ","<< az << endl;

			x=ax;
			ax+=vr;
		}
		z=az;
		az+=hr;
	}
	
	//LEFT AND RIGHT
	x=compr/2; ax=-x;
	y=-(larg/2), ay=y+hr;

	for(i=0; i<cmdh; i++) {
		z=-(larg/2);
		az=z+hr;
		for(j=0; j<cmdv; j++) {
			printf("%f %f %f\n",x,y,z); file << x << "," << y << ","<< z << endl;
			printf("%f %f %f\n",x,y,az); file << x << "," << y << ","<< az << endl;
			printf("%f %f %f\n",x,ay,az); file << x << "," << ay << ","<< az << endl;

			printf("%f %f %f\n",x,y,z); file << x << "," << y << ","<< z << endl;
			printf("%f %f %f\n",x,ay,az); file << x << "," << ay << ","<< az << endl;
			printf("%f %f %f\n",x,ay,z); file << x << "," << ay << ","<< z << endl;
			
			printf("%f %f %f\n",ax,y,z); file << ax << "," << y << ","<< z << endl;
			printf("%f %f %f\n",ax,y,az); file << ax << "," << y << ","<< az << endl;
			printf("%f %f %f\n",ax,ay,az); file << ax << "," << ay << ","<< az << endl;

			printf("%f %f %f\n",ax,y,z); file << ax << "," << y << ","<< z << endl;
			printf("%f %f %f\n",ax,ay,az); file << ax << "," << ay << ","<< az << endl;
			printf("%f %f %f\n",ax,ay,z); file << ax << "," << ay << ","<< z << endl;

			z=az;
			az+=hr;
		}
		y=ay;
		ay+=hr;
	}
	file.close();
}

int main(int argc, char **argv) {	
	if(argc>1) {
		if(!strcmp(argv[1],"plano")) {
			cout << "PLANO\n";
			plano(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]));
		} else {
			if(!strcmp(argv[1],"paralelipipedo")) {
				cout << "PARALELIPIPEDO\n";
				paralelipipedo(atof(argv[2]), atof(argv[3]), atof(argv[4]), atoi(argv[5]), atoi(argv[6]));
			} else {
				if(!strcmp(argv[1],"cone"))
					;
				else
					;
			}
		}
	}
	return 0;
}