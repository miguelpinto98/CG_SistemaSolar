 #include "main.h"

void plano(float compr, float larg, int cmdh, int cmdv, string str) {
	float x,y,z;
	int i, j;

	Ponto p;
	ofstream file(str);
	vector<Ponto> normais;
	vector<Ponto> texturas;

	y = 0;
	z = -(larg / 2);
	x = -(compr / 2);

	float XX = compr / cmdh;
	float ZZ = larg / cmdv;

	float texV = 1 / (float)cmdh;
	float texH = 1 / (float)cmdv;

	file << (cmdh+1)*(cmdv+1) << endl;
	file << (cmdh) << endl;
	file << (cmdv) << endl;

	for (i = 0; i<=cmdh; i++) {
		z = -larg / 2 + i*ZZ;
		for (j = 0; j<=cmdv; j++) {
			x = -compr / 2 + j*XX;
			file << x << "," << y << "," << z << endl;

			p = Ponto::Ponto(0, 1, 0);
			normais.push_back(p);

			p = Ponto::Ponto(1 - i* texH, j*texV, 0);
			texturas.push_back(p);
		}
	}

	int nn = normais.size();
	file << nn << endl;

	for (int i = 0; i < nn; i++) {
		Ponto p = normais[i];
		file << p.getX() << "," << p.getY() << "," << p.getZ() << endl;
	}

	nn = texturas.size();
	file << nn << endl;

	for (int i = 0; i < nn; i++) {
		Ponto p = texturas[i];
		file << p.getX() << "," << p.getY() << endl;
	}

	file.close();
}

void paralelipipedo(double compr, double larg, double alt, int cmdh, int cmdv, int cmdl, string str) {
	int i, j;
	ofstream file(str);
	vector<Ponto> normais;
	vector<Ponto> texturas;

	double x = -(double)(compr / 2);
	double y = -(double)(alt / 2);
	double z = -(double)(larg / 2);

	double vr = (double)(compr / cmdv);
	double hr = (double)(alt / cmdh);
	double lr = (double)(larg / cmdl);

	double ax = x + vr;
	double ay = y + hr;
	double az = z + lr;

	file << (cmdh*cmdv * 12 + cmdl*cmdv * 12 + cmdl*cmdh * 12) << endl;
	file << (cmdh) << endl;
	file << (cmdv) << endl;

	//BACK AND FRONT: x e y
	z = (larg / 2); az = -z;
	y = -(alt / 2); ay = y + hr;

	for (i = 0; i < cmdh; i++) {
		x = -(compr / 2); ax = x + vr;
		for (j = 0; j < cmdv; j++) {
			Ponto p = Ponto::Ponto(0, 0, -1);
			// (x,ay,az)      (ax,ay,az)
			//(x,y,az)        (ax, y, az)
			printf("%f %f %f\n", ax, ay, az); file << ax << "," << ay << "," << az << endl;	normais.push_back(p);
			printf("%f %f %f\n", ax, y, az); file << ax << "," << y << "," << az << endl;	normais.push_back(p);
			printf("%f %f %f\n", x, y, az); file << x << "," << y << "," << az << endl;		normais.push_back(p);

			printf("%f %f %f\n", x, ay, az); file << x << "," << ay << "," << az << endl;	normais.push_back(p);
			printf("%f %f %f\n", ax, ay, az); file << ax << "," << ay << "," << az << endl; normais.push_back(p);
			printf("%f %f %f\n", x, y, az); file << x << "," << y << "," << az << endl;		normais.push_back(p);


			// (x,ay,z)      (ax,ay,z)
			//(x,y,z)        (ax, y, z)
			p = Ponto::Ponto(0, 0, -1);
			printf("%f %f %f\n", x, y, z); file << x << "," << y << "," << z << endl;		normais.push_back(p);
			printf("%f %f %f\n", ax, y, z); file << ax << "," << y << "," << z << endl;		normais.push_back(p);
			printf("%f %f %f\n", ax, ay, z); file << ax << "," << ay << "," << z << endl;	normais.push_back(p);

			printf("%f %f %f\n", x, y, z); file << x << "," << y << "," << z << endl;		normais.push_back(p);
			printf("%f %f %f\n", ax, ay, z); file << ax << "," << ay << "," << z << endl;	normais.push_back(p);
			printf("%f %f %f\n", x, ay, z); file << x << "," << ay << "," << z << endl;		normais.push_back(p);

			x = ax;	ax += vr;
		}
		y = ay; ay += hr;
	}

	//TOP AND DOWN: z e x
	y = alt / 2; ay = -y;
	z = -(larg / 2); az = z + lr;

	for (i = 0; i < cmdl; i++) {
		x = -(compr / 2); ax = x + vr;
		for (j = 0; j < cmdv; j++) {
			Ponto p = Ponto::Ponto(0, 1, 0);
			// (x,y,z)      (ax,y,z)
			//(x,y,az)      (ax, y, az)

			printf("%f %f %f\n", ax, y, az); file << ax << "," << y << "," << az << endl;	normais.push_back(p);
			printf("%f %f %f\n", ax, y, z); file << ax << "," << y << "," << z << endl;		normais.push_back(p);
			printf("%f %f %f\n", x, y, z); file << x << "," << y << "," << z << endl;		normais.push_back(p);

			printf("%f %f %f\n", x, y, az); file << x << "," << y << "," << az << endl;		normais.push_back(p);
			printf("%f %f %f\n", ax, y, az); file << ax << "," << y << "," << az << endl;	normais.push_back(p);
			printf("%f %f %f\n", x, y, z); file << x << "," << y << "," << z << endl;		normais.push_back(p);

			// (x,ay,z)      (ax,ay,z)
			//(x,ay,az)      (ax, ay, az)
			p = Ponto::Ponto(0, -1, 0);
			printf("%f %f %f\n", x, ay, z); file << x << "," << ay << "," << z << endl;		normais.push_back(p);
			printf("%f %f %f\n", ax, ay, z); file << ax << "," << ay << "," << z << endl;	normais.push_back(p);
			printf("%f %f %f\n", ax, ay, az); file << ax << "," << ay << "," << az << endl;	normais.push_back(p);

			printf("%f %f %f\n", x, ay, z); file << x << "," << ay << "," << z << endl;		normais.push_back(p);
			printf("%f %f %f\n", ax, ay, z); file << ax << "," << ay << "," << az << endl;	normais.push_back(p);
			printf("%f %f %f\n", x, ay, az); file << x << "," << ay << "," << az << endl;	normais.push_back(p);
			x = ax; ax += vr;
		}
		z = az; az += lr;
	}


	//LEFT AND RIGHT: z e y
	x = compr / 2; ax = -x;
	y = -(alt / 2); ay = y + hr;

	for (i = 0; i < cmdh; i++) {
		z = -(larg / 2); az = z + lr;

		for (j = 0; j < cmdl; j++) {
			Ponto p = Ponto::Ponto(-1, 0, 0);
			// (x,ay,az)      (x,ay,z)
			//(x,y,az)        (x,y,z)

			printf("%f %f %f\n", x, ay, az); file << x << "," << ay << "," << az << endl;	normais.push_back(p);
			printf("%f %f %f\n", x, y, az); file << x << "," << y << "," << az << endl;		normais.push_back(p);
			printf("%f %f %f\n", x, y, z); file << x << "," << y << "," << z << endl;		normais.push_back(p);

			printf("%f %f %f\n", x, ay, z); file << x << "," << ay << "," << z << endl;		normais.push_back(p);
			printf("%f %f %f\n", x, ay, az); file << x << "," << ay << "," << az << endl;	normais.push_back(p);
			printf("%f %f %f\n", x, y, z); file << x << "," << y << "," << z << endl;		normais.push_back(p);

			p = Ponto::Ponto(1, 0, 0);
			printf("%f %f %f\n", ax, y, z); file << ax << "," << y << "," << z << endl;		normais.push_back(p);
			printf("%f %f %f\n", ax, y, az); file << ax << "," << y << "," << az << endl;	normais.push_back(p);
			printf("%f %f %f\n", ax, ay, az); file << ax << "," << ay << "," << az << endl;	normais.push_back(p);

			printf("%f %f %f\n", ax, y, z); file << ax << "," << y << "," << z << endl;		normais.push_back(p);
			printf("%f %f %f\n", ax, ay, az); file << ax << "," << ay << "," << az << endl; normais.push_back(p);
			printf("%f %f %f\n", ax, ay, z); file << ax << "," << ay << "," << z << endl;	normais.push_back(p);
			z = az; az += lr;
		}
		y = ay; ay += hr;
	}

	int nn = normais.size();
	file << nn << endl;

	for (int i = 0; i < nn; i++) {
		Ponto p = normais[i];
		file << p.getX() << "," << p.getY() << "," << p.getZ() << endl;
	}

	nn = texturas.size();
	file << nn << endl;

	for (int i = 0; i < nn; i++) {
		Ponto p = texturas[i];
		file << p.getX() << "," << p.getY() << endl;
	}
}

void esfera(double raio, int camadasV, int camadasH, string str){
	double camada = M_PI / camadasV; //pi=180
	double rotacoes = 2 * M_PI / camadasH;
	Ponto p = Ponto::Ponto();
	ofstream file(str);
	vector<Ponto> normais;

	float texV = 1 / (float)camadasV;
	float texH = 1 / (float)camadasH;
	vector<Ponto> texturas;
	
	file << ((camadasH+1)*(camadasV+1)) << endl;
	file << (camadasH) << endl;
	file << (camadasV) << endl;

	for (int i = 0; i<=camadasV; i++){
		double angYX = camada*i; // 0 a 180� na vertical

		for (int j = 0; j<=camadasH; j++){
			double angZX = rotacoes*j; // 0 a 360� na horizontal

			double x1 = raio * sin(angYX) * sin(angZX);
			double y1 = raio * cos(angYX);
			double z1 = raio * sin(angYX) * cos(angZX);

			file << x1 << "," << y1 << "," << z1 << endl;
			
			p = Ponto(x1 / raio, y1 / raio, z1 / raio);
			normais.push_back(p);

			p = Ponto(j*texH, i*texV, 0);
			texturas.push_back(p);
		}
	}

	int nn = normais.size();
	file << nn << endl;

	for (int i = 0; i < nn; i++) {
		Ponto p = normais[i];
		file << p.getX() << "," << p.getY() << "," << p.getZ() << endl;
	}

	nn = texturas.size();
	file << nn << endl;

	for (int i = 0; i < nn; i++) {
		Ponto p = texturas[i];
		file << p.getX() << "," << p.getY() << endl;
	}

	file.close();
}

void cone(double raio, double altura, double camadasV, double camadasH, string str){

	double deltaV = (2 * M_PI) / camadasV;
	double deltaH = altura / camadasH;
	double alt = -altura / 2;

	ofstream file(str);
	vector<Ponto> normais;
	vector<Ponto> texturas;

	file << (camadasH) << endl;
	file << (camadasH) << endl;
	file << (camadasV) << endl;

	// a base (desenhado em y = alt = -altura/2)
	for (double alpha = 0; alpha < 2 * M_PI; alpha += deltaV){

		double x1 = 0;
		double y1 = alt;
		double z1 = 0;

		double x2 = raio * sin(alpha + deltaV);
		double y2 = alt;
		double z2 = raio * cos(alpha + deltaV);

		double x3 = raio * sin(alpha);
		double y3 = alt;
		double z3 = raio * cos(alpha);

		printf("%f, %f, %f\n", x1, y1, z1); file << x1 << "," << y1 << "," << z1 << endl;
		printf("%f, %f, %f\n", x2, y2, z2); file << x2 << "," << y2 << "," << z2 << endl;
		printf("%f, %f, %f\n", x3, y3, z3); file << x3 << "," << y3 << "," << z3 << endl;
	}

	// as v�rias camadas de altura (para que os triangulos nao fiquem muito esticados)
	for (int i = 0; i<camadasH; i++){

		for (double alpha = 0; alpha < camadasV; alpha += deltaV){

			double camada = alt + i*deltaH;
			double camadaSeg = alt + (i + 1)*deltaH;

			double raio1 = raio - (raio*i) / camadasH;
			double raio2 = raio - (raio*(i + 1)) / camadasH;

			double x4 = raio2 * sin(alpha);
			double y4 = camadaSeg;
			double z4 = raio2 * cos(alpha);

			double x5 = raio1 * sin(alpha);
			double y5 = camada;
			double z5 = raio1 * cos(alpha);

			double x6 = raio2 * sin(alpha + deltaV);
			double y6 = camadaSeg;
			double z6 = raio2 * cos(alpha + deltaV);

			printf("%f, %f, %f\n", x4, y4, z4); file << x4 << "," << y4 << "," << z4 << endl;
			printf("%f, %f, %f\n", x5, y5, z5); file << x5 << "," << y5 << "," << z5 << endl;
			printf("%f, %f, %f\n", x6, y6, z6); file << x6 << "," << y6 << "," << z6 << endl;

			double x7 = raio1 * sin(alpha);
			double y7 = camada;
			double z7 = raio1 * cos(alpha);

			double x8 = raio1 * sin(alpha + deltaV);
			double y8 = camada;
			double z8 = raio1 * cos(alpha + deltaV);

			double x9 = raio2 * sin(alpha + deltaV);
			double y9 = camadaSeg;
			double z9 = raio2 * cos(alpha + deltaV);

			printf("%f, %f, %f\n", x7, y7, z7); file << x7 << "," << y7 << "," << z7 << endl;
			printf("%f, %f, %f\n", x8, y8, z8); file << x8 << "," << y8 << "," << z8 << endl;
			printf("%f, %f, %f\n", x9, y9, z9); file << x9 << "," << y9 << "," << z9 << endl;
		}
	}

	int nn = normais.size();
	file << nn << endl;

	for (int i = 0; i < nn; i++) {
		Ponto p = normais[i];
		file << p.getX() << "," << p.getY() << "," << p.getZ() << endl;
	}

	nn = texturas.size();
	file << nn << endl;

	for (int i = 0; i < nn; i++) {
		Ponto p = texturas[i];
		file << p.getX() << "," << p.getY() << endl;
	}
}

void readPatch(string path) {
	int i , j, pos, ind, np, nv;
	float ponto[3], n;
	string line, token;

	ifstream ifile;
	ifile.open(path, ios::in);

	if (ifile.is_open()) {
		ifile >> np; getline(ifile, line);

		for (i = 0; i < np && getline(ifile, line); i++) {
			Patch pa = Patch::Patch();
			for (j = 0; j < 16; j++) {
				pos = line.find(",");
				token = line.substr(0, pos);
				ind = atof(token.c_str());
				line.erase(0, pos + 1);

				pa.adicionaIndice(ind);
			}
			patchs.push_back(pa);
		}

		ifile >> nv; getline(ifile, line);

		for (i = 0; i < nv && getline(ifile, line); i++) {
			for (j = 0; j < 3; j++) {
				pos = line.find(",");
				token = line.substr(0, pos);
				n = atof(token.c_str());
				line.erase(0, pos + 1);

				ponto[j] = n;
			}
			vertices.push_back(Ponto::Ponto(ponto[0], ponto[1], ponto[2]));
		}
		ifile.close();
	} else {
		cout << "Ficheiro *.patch nao encontrado!" << endl;
	}
}

Ponto Calculate(float t, float *p1, float *p2, float *p3, float *p4) {
	float res[3];

	float it = 1.0 - t;

	float b0 = it*it*it;
	float b1 = 3*t*it*it;
	float b2 = 3*t*t*it;
	float b3 = t*t*t;

	res[0] = b0*p1[0] + b1*p2[0] + b2*p3[0] + b3*p4[0];
	res[1] = b0*p1[1] + b1*p2[1] + b2*p3[1] + b3*p4[1];
	res[2] = b0*p1[2] + b1*p2[2] + b2*p3[2] + b3*p4[2];

	return Ponto::Ponto(res[0], res[1], res[2]);
}

Ponto bezier(float u, float v, vector<int> pat) {
	float bz[4][3], res[4][3];
	int i, j = 0, k=0;

	for (i = 0; i < 16; i ++) {
		bz[j][0] = vertices[pat[i]].getX();
		bz[j][1] = vertices[pat[i]].getY();
		bz[j][2] = vertices[pat[i]].getZ();

		j++;

		if (j % 4 == 0) {
			Ponto p = Calculate(u, bz[0], bz[1], bz[2], bz[3]);
			res[k][0] = p.getX();
			res[k][1] = p.getY();
			res[k][2] = p.getZ();
			
			k++;
			j = 0;
		}
	} 
	return Calculate(v, res[0], res[1], res[2], res[3]);
}

void escreveTriangulos(Ponto p1, Ponto p2, Ponto p3, ofstream& file) {
	file << p1.getX() << "," << p1.getY() << "," << p1.getZ() << endl;
	file << p2.getX() << "," << p2.getY() << "," << p2.getZ() << endl;
	file << p3.getX() << "," << p3.getY() << "," << p3.getZ() << endl;
}

void patchBezier(int tess, int ip, ofstream& file) {
	float inc = 1.0 / tess, u, v, u2, v2;
	
	for (int i = 0; i < tess; i++) {
		for (int j = 0; j < tess; j++) {
			u = i*inc;
			v = j*inc;
			u2 = (i + 1)*inc;
			v2 = (j + 1)*inc;

			Ponto p0 = bezier(u, v, patchs[ip].getPatch());
			Ponto p1 = bezier(u, v2, patchs[ip].getPatch());
			Ponto p2 = bezier(u2, v, patchs[ip].getPatch());
			Ponto p3 = bezier(u2, v2, patchs[ip].getPatch());

			escreveTriangulos(p0, p2, p3,file);
			escreveTriangulos(p0, p3, p1,file);
		}
	}
}

void initSupBezier(int tess, string nameFile) {
	ofstream file;
	file.open(nameFile);

	int num = patchs.size();

	file << (num*tess*tess * 6) << endl;
	file << tess << endl;
	file << tess << endl;

	for (int i = 0; i < num; i++)
		patchBezier(tess, i,file);

	file << 0 << endl;
	file << 0 << endl;
	file.close();
}

int main(int argc, char **argv) {
	if (argc>1) {
		if (!strcmp(argv[1], "plano") && argc == 7) {
			cout << "PLANO\n" << endl;
			plano(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
		}
		else {
			if (!strcmp(argv[1], "paralelipipedo") && argc == 9) {
				cout << "PARALELIPIPEDO\n" << endl;
				paralelipipedo(atof(argv[2]), atof(argv[3]), atof(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), argv[8]);
			}
			else {
				if (!strcmp(argv[1], "cone") && argc == 7) {
					cout << "CONE\n" << endl;
					cone(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
				}
				else {
					if (!strcmp(argv[1], "esfera") && argc == 6) {
						cout << "ESFERA\n" << endl;
						esfera(atof(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);
					}
					else {
						char token[7];
						if (argc == 4) {
							string abc = argv[1];
							int pos = abc.find(".");
							abc = abc.substr(pos, pos+6);
							strcpy_s(token,size_t(7),abc.c_str());
						}
						if (!strcmp(token, ".patch") && argc == 4) { 
							cout << argv[1] << endl;
							readPatch(argv[1]);	//Nome Ficheiro = Path
							initSupBezier(atoi(argv[2]), argv[3]); //Inteiro e Nome do Ficheiro a Ser Gerado
						}
						else {
							cout << "PRIMITIVA NAO DESENHADA - DADOS INSERIDOS INVALIDOS!" << endl;
						}
					}
				}
			}
		}
	}
	return 0;
}