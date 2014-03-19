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

void esfera(double raio, int camadasV, int camadasH){
	double camada = M_PI / camadasV; //pi=180
	double rotacoes = 2 * M_PI / camadasH;
	int count = 1;
	ofstream file("esfera.3d");

	for (int i = 0; i<camadasV; i++){
		double angYX = camada*i; // 0 a 180º na vertical

		for (int j = 0; j<camadasH; j++){
			double angZX = rotacoes*j; // 0 a 360º na horizontal
			count++;

			double x1 = raio * sin(angYX) * sin(angZX);
			double x2 = raio * sin(angYX + camada) * sin(angZX);
			double x3 = raio * sin(angYX + camada) * sin(angZX + rotacoes);
			double x4 = raio * sin(angYX) * sin(angZX + rotacoes);

			double y1 = raio * cos(angYX);
			double y2 = raio * cos(angYX + camada);

			double z1 = raio * sin(angYX) * cos(angZX);
			double z2 = raio * sin(angYX + camada) * cos(angZX);
			double z3 = raio * sin(angYX + camada) * cos(angZX + rotacoes);
			double z4 = raio * sin(angYX) * cos(angZX + rotacoes);


			printf("\n\n-- ITERACAO %d de %d --\n", count - 1, camadasV*camadasH);
			printf("%f, %f, %f\n", x1, y1, z1); file << x1 << "," << y1 << "," << z1 << endl;
			printf("%f, %f, %f\n", x2, y2, z2); file << x2 << "," << y2 << "," << z2 << endl;
			printf("%f, %f, %f\n", x3, y2, z3); file << x3 << "," << y2 << "," << z3 << endl;

			printf("%f, %f, %f\n", x1, y1, z1); file << x1 << "," << y1 << "," << z1 << endl;
			printf("%f, %f, %f\n", x3, y2, z3); file << x3 << "," << y2 << "," << z3 << endl;
			printf("%f, %f, %f\n", x4, y1, z4); file << x4 << "," << y1 << "," << z4 << endl;
		}
	}
	file.close();
}

void cone(double raio, double altura, double camadasV, double camadasH){

	double deltaV = (2*M_PI)/camadasV;
	double deltaH = altura/camadasH;
	double alt = -altura/2;

	ofstream file("cone.3d");

	// a base (desenhado em y = alt = -altura/2)
		for(double alpha = 0; alpha < 2*M_PI; alpha += deltaV){
			
			double x1 = 0;
			double y1 = alt;
			double z1 = 0;

			double x2 = raio * sin(alpha+deltaV);
			double y2 = alt;
			double z2 = raio * cos(alpha+deltaV);

			double x2 = raio * sin(alpha);
			double y2 = alt;
			double z2 = raio * cos(alpha);

			printf("%f, %f, %f\n", x1, y1, z1); file << x1 << "," << y1 << "," << z1 << endl;
			printf("%f, %f, %f\n", x2, y2, z2); file << x2 << "," << y2 << "," << z2 << endl;
			printf("%f, %f, %f\n", x3, y3, z3); file << x3 << "," << y3 << "," << z3 << endl;
		}

	// as várias camadas de altura (para que os triangulos nao fiquem muito esticados)
	for(int i = 0; i<camadasH; i++){

			for(double alpha = 0; alpha < camadasV; alpha += deltaV){
				
				double camada = alt+i*deltaH;
				double camadaSeg = alt+(i+1)*deltaH;

				double raio1= raio - (raio*i)/camadasH;
				double raio2= raio - (raio*(i+1))/camadasH;

				double x4 = raio2 * sin(alpha);
				double y4 = camadaSeg;
				double z4 = raio2 * cos(alpha);

				double x5 = raio1 * sin(alpha);
				double y5 = camada;
				double z5 = raio1 * cos(alpha);

				double x6 = raio2 * sin(alpha+deltaV);
				double y6 = camadaSeg;
				double z6 = raio2 * cos(alpha+deltaV);

				printf("%f, %f, %f\n", x4, y4, z4); file << x4 << "," << y4 << "," << z4 << endl;
				printf("%f, %f, %f\n", x5, y5, z5); file << x5 << "," << y5 << "," << z5 << endl;
				printf("%f, %f, %f\n", x6, y6, z6); file << x6 << "," << y6 << "," << z6 << endl;

				double x7 = raio1 * sin(alpha);
				double y7 = camada;
				double z7 = raio1 * cos(alpha);

				double x8 = raio1 * sin(alpha+deltaV);
				double y8 = camada;
				double z8 = raio1 * cos(alpha+deltaV);

				double x9 = raio2 * sin(alpha+deltaV);
				double y9 = camadaSeg;
				double z9 = raio2 * cos(alpha+deltaV);

				printf("%f, %f, %f\n", x7, y7, z7); file << x7 << "," << y7 << "," << z7 << endl;
				printf("%f, %f, %f\n", x8, y8, z8); file << x8 << "," << y8 << "," << z8 << endl;
				printf("%f, %f, %f\n", x9, y9, z9); file << x9 << "," << y9 << "," << z9 << endl;
			}
	}	
	file.close();
}

int main(int argc, char **argv) {	
	if(argc>1) {
		if(!strcmp(argv[1],"plano")){ cout << "PLANO\n"; plano(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]));}		
		else {
			if(!strcmp(argv[1],"paralelipipedo")){cout << "PARALELIPIPEDO\n";paralelipipedo(atof(argv[2]), atof(argv[3]), atof(argv[4]), atoi(argv[5]), atoi(argv[6]));} 
			else {
				if(!strcmp(argv[1],"cone")){cout << "CONE\n";	cone(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]));}
				else {
					if (!strcmp(argv[1], "esfera")) {cout << "ESFERA\n";	esfera(atof(argv[2]), atof(argv[3]), atof(argv[4]));}
				}
					
			}
		}
	}
	return 0;
}