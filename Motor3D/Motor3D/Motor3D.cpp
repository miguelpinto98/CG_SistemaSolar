#include "Motor3D.h"

#define POINT_COUNT 4

float p[POINT_COUNT][3] = {{-1,-1,0},{1,-1,0},{1,1,0},{-1,1,0}};

void getCatmullRomPoint(float t, int *indices, float *res) {
    int i;
    float res_aux[4];
	// catmull-rom matrix (nao mexer)
	float m[4][4] = {{-0.5f,  1.5f, -1.5f,  0.5f},
					 { 1.0f, -2.5f,  2.0f, -0.5f},
					 {-0.5f,  0.0f,  0.5f,  0.0f},
					 { 0.0f,  1.0f,  0.0f,  0.0f}};
	res[0] = 0.0; res[1] = 0.0; res[2] = 0.0;
    
    
     
    //Sem derivada
    for (i=0; i<4; i++)
        res_aux[i]= pow(t,3) * m[0][i] +  pow(t,2) * m[1][i] + t * m[2][i] + m[3][i];
     
   /*
    //Com derivada (Esta é a versão para ser utilizada a derivada dos pontos, mas ainda não está concluida)
    for (i=0; i<4; i++)
        res_aux[i]= 3*pow(t,2) * m[0][i] +  2*t * m[1][i] + m[2][i]; */
  
    
    //Calculo do RES
	for(i=0;i<3;i++){
        res[i]=res_aux[0]*p[indices[0]][i] + res_aux[1]*p[indices[1]][i] +res_aux[2]*p[indices[2]][i] + res_aux[3]*p[indices[3]][i];
    }
}

void getGlobalCatmullRomPoint(float gt, float *res) {
    
	float t = gt * POINT_COUNT; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment
    
	// indices store the points
	int indices[4];
	indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;	indices[1] = (indices[0]+1)%POINT_COUNT;
	indices[2] = (indices[1]+1)%POINT_COUNT; indices[3] = (indices[2]+1)%POINT_COUNT;
    
	getCatmullRomPoint(t, indices, res);
}

void renderCatmullRomCurve() {
    float  gtt;
    float res[3];
    
    glBegin(GL_LINE_LOOP);
    for (gtt=0; gtt<1; gtt+=0.0001){
        getGlobalCatmullRomPoint(gtt,res);
        glVertex3fv(res);
    }
    glEnd();
}

void changeSize(int w, int h) {
	if(h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glViewport(0, 0, w, h);
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);
	glMatrixMode(GL_MODELVIEW);
}

void framesPerSecond() {
	float fps;
	int time;
	char s[64];

	frame++;
	time=glutGet(GLUT_ELAPSED_TIME); 
	if (time - timebase > 1000) { 
		fps = frame*1000.0/(time-timebase); 
		timebase = time; 
		frame = 0;
		sprintf_s(s, "FPS: %f6.2", fps);
		glutSetWindowTitle(s);
	}
}

void desenhaPrimitivas(float a, float* res) {
	int ipr = primitivas.size();
	for (int i = 0; i<ipr; i++) {
		Primitiva p = primitivas[i];
		Transformacao t = p.getTransformacao();

		glPushMatrix();
		
		if (!t.trasnformacaoVazia()) {
			Translacao tr = t.getTranslacao();
			if (!tr.vazio()) {
				//Fazer CatMullRom
			}

			Rotacao ro = t.getRotacao();
			if (!ro.vazio())
				glRotatef(1, ro.getRx(), ro.getRy(), ro.getRz());

			Escala es = t.getEscala();
			if (!es.vazio())
				glScalef(es.getEx(), es.getEy(), es.getEz());
		}
		/* Modo Imediato */
		//p.construir();

		/* Modo VBO */

		//getGlobalCatmullRomPoint(a, res);

		//glTranslatef(res[0], res[1], res[2]);
		//glScalef(0.1, 0.1, 0.1);

		p.desenhar();

		

		glPopMatrix();
	}
}

void renderScene(void) {
	static float a = 0;
	float res[3];
    
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX,camY,camZ, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	/* Definicoes Camara */
	glRotatef(anguloX, 1, 0, 0);
	glRotatef(anguloY, 0, 1, 0);
	glRotatef(anguloZ, 0, 0, 1);
	glTranslatef(coordX, coordY, coordZ);

	/* RENDER PRIMITIVAS */
	//renderCatmullRomCurve();
  
	framesPerSecond();

	desenhaPrimitivas(a,res);
	
	a += 0.001;

	glutSwapBuffers();
}

void resetCamara() {
	anguloX = anguloY = anguloZ = 0.0f;
	coordX = coordY = coordZ = 0;
	alpha = 0.0f;
	beta = 0.5f;
}

void normalkeyboard(unsigned char tecla, int x, int y) {
	switch (tecla) {
		case 'W':;
		case 'w': anguloX += 1; break;
		case 'S':;
		case 's': anguloX -= 1; break;
		case 'A':;
		case 'a': anguloY += 1; break;
		case 'D':;
		case 'd': anguloY -= 1; break;
		case 'q':;
		case 'Q': anguloZ += 1; break;
		case 'e':;
		case 'E': anguloZ -= 1; break;
		case 'R':;
		case 'r': resetCamara(); break;
		case '+': coordZ += 0.5f; break;
		case '-': coordZ -= 0.5f; break;
	}
	glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP: coordY += 1; break;
		case GLUT_KEY_DOWN: coordY -= 1; break;
		case GLUT_KEY_LEFT: coordX -= 1; break;
		case GLUT_KEY_RIGHT: coordX += 1; break;
	}
}

void processMouseButtons(int button, int state, int xx, int yy)
{
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {

			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}
}

void processMouseMotion(int xx, int yy) {
	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else
		if (tracking == 2) {

			alphaAux = alpha;
			betaAux = beta;
			rAux = r - deltaY;
			if (rAux < 3)
				rAux = 3;
		}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux * sin(betaAux * 3.14 / 180.0);
}

void menu(int op) {
	switch (op) {
		case 1: glPolygonMode(GL_FRONT, GL_FILL); break;
		case 2: glPolygonMode(GL_FRONT, GL_LINE); break;
		case 3: glPolygonMode(GL_FRONT, GL_POINT); break;
	}
	glutPostRedisplay();
}

void defineMenu() {
	glutCreateMenu(menu);

	glutAddMenuEntry("GL_FILL", 1);
	glutAddMenuEntry("GL_LINE", 2);
	glutAddMenuEntry("GL_POINT", 3);
	glutAddMenuEntry("GL_FRONT", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int lerFicheiro(string fl, Primitiva& pr) {
	string line, token, delimiter = ",";
	int pos;
	double a,b,c;
	ifstream file(fl);

	if(file.is_open()) {
		while(getline(file,line)) {
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
			
			Ponto po(a,b,c);
			pr.adicionaPonto(po);
		}
		file.close();
		return 0;
	} else {
		cout << "Nao foi possivel ler o arquivo" << endl;
		return -1;
	}
}

Translacao verificaTranslacoes(XMLElement* transformacao) {
	vector<Ponto> transpontos;
	float tempo = 0;

	if (strcmp(transformacao->Value(), "translacao") == 0) {
		if (transformacao->Attribute("tempo"))
			tempo = stoi(transformacao->Attribute("tempo"));

		float transX, transY, transZ;
		for (XMLElement* ponto = transformacao->FirstChildElement("ponto"); ponto; ponto = ponto->NextSiblingElement("ponto")) {
			transX = transY = transZ = 0;

			if (ponto->Attribute("X"))
				transX = stof(ponto->Attribute("X"));

			if (ponto->Attribute("Y"))
				transY = stof(ponto->Attribute("Y"));

			if (ponto->Attribute("Z"))
				transZ = stof(ponto->Attribute("Z"));

			Ponto pt = Ponto::Ponto(transX, transY, transZ);
			transpontos.push_back(pt);
		}
	}
	return Translacao::Translacao(tempo, transpontos);
}

Rotacao verificaRotacao(XMLElement* transformacao){
	float rotX, rotY, rotZ, tempo;
	rotX = rotY = rotZ = tempo = 0;

	if(transformacao->Attribute("tempo"))
		tempo= stoi(transformacao->Attribute("tempo"));

	if(transformacao->Attribute("eixoX"))
		rotX= stof(transformacao->Attribute("eixoX"));

	if(transformacao->Attribute("eixoY"))
		rotY= stof(transformacao->Attribute("eixoY"));

	if(transformacao->Attribute("eixoZ"))
		rotZ= stof(transformacao->Attribute("eixoZ"));
	
	return Rotacao::Rotacao(tempo,rotX,rotY,rotZ);
}

Escala verificaEscala(XMLElement* transformacao) {
	float escX, escY, escZ;
	escX = escY = escZ = 0;

	if (transformacao->Attribute("X"))
		escX = stof(transformacao->Attribute("X"));

	if (transformacao->Attribute("Y"))
		escY = stof(transformacao->Attribute("Y"));

	if (transformacao->Attribute("Z"))
		escZ = stof(transformacao->Attribute("Z"));
	
	return Escala::Escala(escX, escY, escZ);
}

void parseXML(XMLElement* grupo, Transformacao transf) {
	Transformacao trans;
	Translacao tr;
	Rotacao ro;
	Escala es;

	if(strcmp(grupo->FirstChildElement()->Value(), "grupo")==0)
		grupo=grupo->FirstChildElement();

	//transformações para um grupo
	XMLElement* transformacao = grupo->FirstChildElement();

	/* Verifica se existem transformcoes antes dos modelos */
	if (strcmp(transformacao->Value(), "modelos") == 0)
		trans = transf;
	else {
		for (transformacao; (strcmp(transformacao->Value(), "modelos") != 0); transformacao = transformacao->NextSiblingElement()) {
			if (strcmp(transformacao->Value(), "translacao") == 0)
				tr = verificaTranslacoes(transformacao);
			//else { tr.setRotacao(transf.getRotacao());}
	
			if (strcmp(transformacao->Value(), "rotacao") == 0)
				ro = verificaRotacao(transformacao);
			//else { tr.setRotacao(transf.getRotacao());}


			if (strcmp(transformacao->Value(), "escala") == 0) 
				es = verificaEscala(transformacao);
			//else { tr.setEscala(transf.getEscala());}
		}
		trans = Transformacao::Transformacao(tr, ro, es);
	}

	//para o mesmo grupo, quais os modelos(ficheiros) que recebem as transformações
	for (XMLElement* modelo = grupo->FirstChildElement("modelos")->FirstChildElement("modelo"); modelo; modelo = modelo->NextSiblingElement("modelo")) {
		int flag;
		Primitiva p(modelo->Attribute("ficheiro"));
		cout << p.getNomePrimitiva() << endl;
		flag = lerFicheiro(p.getNomePrimitiva(),p);

		if(flag>=0) { 
			p.setTransformacao(trans);
			primitivas.push_back(p);

			cout << "Translacao: "<< trans.getTranslacao().getTime() << endl;
			cout << "Rotacao   : " << trans.getRotacao().getRx() << " - " << trans.getRotacao().getRy() << " - " << trans.getRotacao().getRz() << endl;
			cout << "Escala    : " << trans.getEscala().getEx() << " - " << trans.getEscala().getEy() << " - " << trans.getEscala().getEz() << endl;
		}
	}
	
	//faz o mesmo de cima para grupos filhos
	if(grupo->FirstChildElement("grupo")) {
		cout << "Vou para os Filhos" << endl;
		parseXML(grupo->FirstChildElement("grupo"),trans);
	}

	//faz o mesmo de cima para grupos irmãos
	if(grupo->NextSiblingElement("grupo")) {
		cout << "Vim para os Irmaos" << endl;
		parseXML(grupo->NextSiblingElement("grupo"),transf);
	}
}

void readXML(string fxml) {
	XMLDocument doc;
	doc.LoadFile(fxml.c_str());
	XMLElement* cena = doc.FirstChildElement("cena")->FirstChildElement("grupo");
	Transformacao t = Transformacao::Transformacao();
	parseXML(cena, t);
}

void initPrimitivas() {
	int num = primitivas.size();

	for (int i = 0; i < num; i++)
		primitivas[i].preparar();
}

int main(int argc, char **argv) {
	//string xmlmotor="exemplo1.xml";
	//string xmlmotor="exemplo2.xml";
	//string xmlmotor="exemplo3.xml";
	//string xmlmotor="exemplo4.xml";
	//string xmlmotor="exemplo5.xml";
	//string xmlmotor="exemplo6.xml";
	//string xmlmotor="exemploInv1.xml";
	//string xmlmotor="sistemasolar1.xml";
	//string xmlmotor="motor.xml";
	string xmlmotor="SistemaSolar3Fase.xml";

	readXML(xmlmotor);

	//if(argc>1) { 
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
		glutInitWindowPosition(100,100);
		glutInitWindowSize(1000,600);
		glutCreateWindow("CG@DI-UM");		

		glutDisplayFunc(renderScene);
		glutIdleFunc(renderScene);
		glutReshapeFunc(changeSize);

		glutKeyboardFunc(normalkeyboard);
		glutSpecialFunc(specialKeys);

		glutMouseFunc(processMouseButtons);
		glutMotionFunc(processMouseMotion);

		defineMenu();
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		glewInit();
		initPrimitivas();

		glutMainLoop();
	//}
	return 0;
} 