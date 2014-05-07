#include "Motor3D.h"

#define POINT_COUNT 5

float p[POINT_COUNT][3] = {{-1,-1,0},{-1,1,0},{1,1,0},{0,0,-1},{1,-1,0}};

void getCatmullRomPoint(float t, int *indices, float *res) {
    int i;
    float res_aux[4];
	// catmull-rom matrix
	float m[4][4] = {{-0.5f,  1.5f, -1.5f,  0.5f},
        { 1.0f, -2.5f,  2.0f, -0.5f},
        {-0.5f,  0.0f,  0.5f,  0.0f},
        { 0.0f,  1.0f,  0.0f,  0.0f}};
    
    
    // Calcular o ponto res = T * M * P
    // sendo Pi = p[indices[i]]
    
    
    //Sem derivada
    for (i=0; i<4; i++)
        res_aux[i]= pow(t,3) * m[0][i] +  pow(t,2) * m[1][i] + t * m[2][i] + m[3][i];
    
    /*
    //Com derivada (Esta � a vers�o para ser utilizada a derivada dos pontos, mas ainda n�o est� concluida)
    for (i=0; i<4; i++)
        res_aux[i]= 3*pow(t,2) * m[0][i] +  2*t * m[1][i] + m[2][i];
    */
    
    //Calculo do RES
	for(i=0;i<3;i++){
        res[i]=res_aux[0]*p[indices[0]][i] + res_aux[1]*p[indices[1]][i] +res_aux[2]*p[indices[2]][i] + res_aux[3]*p[indices[3]][i];
    }
}

// given  global t, returns the point in the curve
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
    // desenhar a curva usando segmentos de reta - GL_LINE_LOOP
    
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

void desenhaPrimitivas() {
	int ipr = primitivas.size();
	for (int i = 0; i<ipr; i++) {
		Primitiva p = primitivas[i];
		Transformacao t = p.getTransformacao();
		Tipo tp;

		glPushMatrix();

		if (!t.trasnformacaoVazia()) {
			Translacao trans;
			trans = t.getTranslacao(); /* FALTA ALTERAR ISTO */
			if (!tp.tipoVazio()) {
				glTranslatef(tp.getTX(), tp.getTY(), tp.getTZ());
			}

			tp = t.getRotacao();
			if (!tp.tipoVazio())
				glRotatef(tp.getTAng(), tp.getTX(), tp.getTY(), tp.getTZ());

			tp = t.getEscala();
			if (!tp.tipoVazio())
				glScalef(tp.getTX(), tp.getTY(), tp.getTZ());
		}
		/* Modo Imediato */
		//p.construir();

		/* Modo VBO */
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

	renderCatmullRomCurve();
    
	glPushMatrix();
	getGlobalCatmullRomPoint(a,res);

	glTranslatef(res[0],res[1],res[2]);
	glScalef(0.1, 0.1, 0.1);
	glutWireTeapot(1);
	glPopMatrix();
   
    
	a+=0.001;

	/*glTranslatef(xx,yy,zz);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

	framesPerSecond();

	desenhaPrimitivas();*/
	
	glutSwapBuffers();
}

void normalkeyboard(unsigned char tecla, int x, int y) {
	switch (tecla) {
		case 'a':
		case 'A': xx-=CONST; break;
		case 'd': 
		case 'D': xx+=CONST; break;
		case 'w':
		case 'W': yy+=CONST; break;
		case 's':
		case 'S': yy-=CONST; break;
		case 'e':
		case 'E': zz-=CONST; break;
		case 'q':
		case 'Q': zz+=CONST; break;
	}
	glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT: angle-=5.0f; break;
		case GLUT_KEY_RIGHT: angle+=5.0f; break;
		case GLUT_KEY_UP: yy+=CONST; break;
		case GLUT_KEY_DOWN: break;
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

void verificaTranslacoes(XMLElement* transformacao, int& t) {

	if (strcmp(transformacao->Value(), "translacao") == 0) {
		if (transformacao->Attribute("tempo"))
			t = stoi(transformacao->Attribute("tempo"));

		printf("%s - %d\n", transformacao->Value(), t);

		float transX, transY, transZ;
		for (XMLElement* ponto = transformacao->FirstChildElement("ponto"); ponto; ponto = ponto->NextSiblingElement("ponto")) {
			transX = transY = transZ = 0;
			
			if (ponto->Attribute("X"))
				transX = stof(ponto->Attribute("X"));

			if (ponto->Attribute("Y"))
				transY = stof(ponto->Attribute("Y"));

			if (ponto->Attribute("Z"))
				transZ = stof(ponto->Attribute("Z"));

			printf("ponto: %f - %f - %f\n", transX, transY, transZ);
		}
		/*Tipo x = transf.getTranslacao();
		tp = Tipo::Tipo(transX + x.getTX(), transY + x.getTY(), transZ + x.getTZ());
		tr.setTranslacao(tp);*/
	}
}

void verificaRotacao(XMLElement* transformacao){
	float rotEixoX, rotEixoY, rotEixoZ;
	int tempoR;

	if(transformacao->Attribute("tempo") == NULL) tempoR=0;
		else tempoR= stoi(transformacao->Attribute("tempo"));

		if(transformacao->Attribute("eixoX") == NULL) rotEixoX=0;
		else rotEixoX= stof(transformacao->Attribute("eixoX"));

		if(transformacao->Attribute("eixoY") == NULL) rotEixoY=0;
		else rotEixoY= stof(transformacao->Attribute("eixoY"));

		if(transformacao->Attribute("eixoZ") == NULL) rotEixoZ=0;
		else rotEixoZ= stof(transformacao->Attribute("eixoZ"));

	printf("%s - %d, %f, %f, %f \n", transformacao->Value(),tempoR, rotEixoX, rotEixoY, rotEixoZ);
	/*	t.transformacao = "rotacao";
		t.arg1=rotAng;
		t.arg2=rotEixoX;
		t.arg3=rotEixoY;
		t.arg4=rotEixoZ;

	Tipo x = transf.getRotacao();
	tp = Tipo::Tipo(rotAng + x.getTAng(), rotEixoX + x.getTX(), rotEixoY + x.getTY(), rotEixoZ + x.getTZ());
	tr.setRotacao(tp);*/

}

void verificaEscala(XMLElement* transformacao) {
	float escX, escY, escZ;

	if (transformacao->Attribute("X") == NULL)
		escX = 0;
	else
		escX = stof(transformacao->Attribute("X"));

	if (transformacao->Attribute("Y") == NULL)
		escY = 0;
	else
		escY = stof(transformacao->Attribute("Y"));

	if (transformacao->Attribute("Z") == NULL)
		escZ = 0;
	else
		escZ = stof(transformacao->Attribute("Z"));

	printf("%s - %f, %f, %f\n", transformacao->Value(), escX, escY, escZ);

//	Tipo x = transf.getEscala();
	//tp = Tipo::Tipo(escX*x.getTX(), escY*x.getTY(), escZ*x.getTZ());
	//tr.setEscala(tp);
	}


void parseXML(XMLElement* grupo, Transformacao transf) {
	int tempo = 0;
	Transformacao tr;
	Tipo tp; /* Isto vai desaparecer */


	if(strcmp(grupo->FirstChildElement()->Value(), "grupo")==0) grupo=grupo->FirstChildElement();

	//transforma��es para um grupo
	XMLElement* transformacao = grupo->FirstChildElement();

	/* Verifica se existem transformcoes antes dos modelos */
	if (strcmp(transformacao->Value(), "modelos") == 0)
		tr = transf;
	else {
		for (transformacao; (strcmp(transformacao->Value(), "modelos") != 0); transformacao = transformacao->NextSiblingElement()) {
			if (strcmp(transformacao->Value(), "translacao") == 0) verificaTranslacoes(transformacao,tempo);
			//else { tr.setRotacao(transf.getRotacao());}
	
			if (strcmp(transformacao->Value(), "rotacao") == 0) verificaRotacao(transformacao);
			//else { tr.setRotacao(transf.getRotacao());}


			if (strcmp(transformacao->Value(), "escala") == 0) verificaEscala(transformacao);
			//else { tr.setEscala(transf.getEscala());}
		}
	}

	//para o mesmo grupo, quais os modelos(ficheiros) que recebem as transforma��es
	for (XMLElement* modelo = grupo->FirstChildElement("modelos")->FirstChildElement("modelo"); modelo; modelo = modelo->NextSiblingElement("modelo")) {
		int flag;
		Primitiva p(modelo->Attribute("ficheiro"));
		cout << p.getNomePrimitiva() << endl;
		flag = lerFicheiro(p.getNomePrimitiva(),p);

		if(flag>=0) { 
		//	p.setTransformacao(tr);
			primitivas.push_back(p);

			//cout << "T: "<< tr.getTranslacao().getTX() << " - " << tr.getTranslacao().getTY() << " - " << tr.getTranslacao().getTZ() << endl;
			//cout << "R: "<< tr.getRotacao().getTAng() << " - " << tr.getRotacao().getTX() << " - " << tr.getRotacao().getTY() << " - " << tr.getRotacao().getTZ() << endl;
			//cout << "E: "<< tr.getEscala().getTX() << " - " << tr.getEscala().getTY() << " - " << tr.getEscala().getTZ() << endl;
		}
	}
	
	//faz o mesmo de cima para grupos filhos
	if(grupo->FirstChildElement("grupo")) {
		cout << "Vou para os Filhos" << endl;
		parseXML(grupo->FirstChildElement("grupo"),tr);
	}

	//faz o mesmo de cima para grupos irm�os
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
	t.setEscala(Tipo::Tipo(1, 1, 1));
	parseXML(cena, t);
}


void initPrimitivas() {
	int num = primitivas.size();

	for (int i = 0; i < num; i++)
		primitivas[i].preparar();
}


int main(int argc, char **argv) {
	string xmlmotor="exemplo1.xml";
	//string xmlmotor="exemplo2.xml";
	//string xmlmotor="exemplo3.xml";
	//string xmlmotor="exemplo4.xml";
	//string xmlmotor="exemplo5.xml";
	//string xmlmotor="exemplo6.xml";
	//string xmlmotor="exemploInv1.xml";
	//string xmlmotor="sistemasolar.xml";
	//string xmlmotor="motor.xml";

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