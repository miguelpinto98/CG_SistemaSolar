#include "mainGerador.h"

void plano(float larg, float compr, int cmdh, int cmdv) {
	double h = larg/cmdh, v = compr/cmdv;
	double ax = 0, az=0, x=v, z=h, y=0;
	int i=0;

	ofstream file("plano.3d");

	for(i=0; i<cmdh; i++) {
		ax=0;
		x=v;
		for(int j=0; j<cmdv; j++) {
			printf("Ponto %d de %d\n",i,j);
			printf("%f %f %f\n",ax,y,az);
			file << ax << "," << y << ","<< az << endl;
			printf("%f %f %f\n",ax,y,z);
			file << ax << "," << y << ","<< z << endl;
			printf("%f %f %f\n",x,y,z);
			file << x << "," << y << ","<< z << endl;
			
			printf("\nXXX\n");

			printf("%f %f %f\n",ax,y,az);
			file << ax << "," << y << ","<< az << endl;
			printf("%f %f %f\n",x,y,az);
			file << x << "," << y << ","<< az << endl;
			printf("%f %f %f\n",x,y,z); 
			file << x << "," << y << ","<< z << endl;
			printf("\n");
			
			ax=x;
			x+=v;
		}
		az=z;
		z+=h;
	}

	file.close();
}


void paralelipipedo(double compr, double larg, int cmdh, int cmdv) {
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
/*
int main(int argc, char **argv) {
	/*
	cout << "argc = " << argc << endl; 
	for(int i = 0; i < argc; i++)
		cout << "argv[" << i << "] = " << argv[i] << endl;

	if(argc==7)
		cout << "Sou um Plano ou Paralelipedo" << endl;
	
	
	//plano(1,4,2,4);
	paralelipipedo(1,0.5,10,10);
	
	/*
	string line, token;
	string delimiter = ",";
	int pos;
	double a,b,c;
	ifstream file("paralelipipedo.3d");
	if(file.is_open()) {
		while(getline(file,line)) {
			//i=0;
			//while(i<=2) {
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


				cout<< a << " - " << b << " - " << c << '\n';
				//i++;
			//}
		}
		file.close();
	} else {
		cout << "Not OK!";
	}

	return 0;
}*/