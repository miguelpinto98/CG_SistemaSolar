#include "Motor3D.h"

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

void renderCatmullRomCurve(vector<Ponto> pontos) {
	int n = pontos.size();
	float pp[3];

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++) {
		pp[0] = pontos[i].getX(); pp[1] = pontos[i].getY(); pp[2] = pontos[i].getZ();
		glVertex3fv(pp);
	}
	glEnd();
}

void renderScene(void) {
	float res[3];	
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX,camY,camZ, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
	
	framesPerSecond();

	/* Definicoes Camara */
	glRotatef(anguloX, 1, 0, 0);
	glRotatef(anguloY, 0, 1, 0);
	glRotatef(anguloZ, 0, 0, 1);
	glTranslatef(coordX, coordY, coordZ);

	float pos[4] = { 0, 60, 256, 1 },
		  diff[3] = { 1, 1, 1 },
		  amb[3] = { 0.2, 0.2, 0.2 };

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);

	/* RENDER PRIMITIVAS */
	int ipr = primitivas.size();
	for (int i = 0; i<ipr; i++) {
		Primitiva p = primitivas[i]; 
		Transformacao t = p.getTransformacao();

		glPushMatrix();
		
		if (!t.trasnformacaoVazia()) {
			Translacao tr = t.getTranslacao();
			if (!tr.vazio()) {
				int num = tr.getTamanho();
				if (num>0) {
					float te = glutGet(GLUT_ELAPSED_TIME) % (int)(tr.getTime() * 1000);
					float gt = te / (tr.getTime() * 1000);
					vector<Ponto> vp = tr.getTransPontos();
					renderCatmullRomCurve(tr.getPontosCurvas());
					tr.getGlobalCatmullRomPoint(gt, res, vp);
					glTranslatef(res[0], res[1], res[2]);
				}
			}

			if (p.numeroFilhos() == 1)
				glPushMatrix();
			
			Rotacao ro = t.getRotacao();
			if (!ro.vazio()){
				float r = glutGet(GLUT_ELAPSED_TIME) % (int)(ro.getTime() * 1000);
				float gr = (r * 360) / (ro.getTime() * 1000);
				glRotatef(gr, ro.getRx(), ro.getRy(), ro.getRz());
			}

			Escala es = t.getEscala();
			if (!es.vazio())
				glScalef(es.getEx(), es.getEy(), es.getEz());
		}
		/* Modo Imediato */
		//p.construir();

		/* Modo VBO */
		p.desenhaComImagem();

		glPopMatrix();

		if (p.numeroFilhos() == 1) { /* BAD CODE*/
			Primitiva pp = p.getFilhos()[0];
			t = pp.getTransformacao();

			if (!t.trasnformacaoVazia()) {
				Translacao tr = t.getTranslacao();
				if (!tr.vazio()) {
					int num = tr.getTamanho();
					if (num>0) {
						float te = glutGet(GLUT_ELAPSED_TIME) % (int)(tr.getTime() * 1000);
						float gt = te / (tr.getTime() * 1000);
						vector<Ponto> vp = tr.getTransPontos();
						renderCatmullRomCurve(tr.getPontosCurvas());
						tr.getGlobalCatmullRomPoint(gt, res, vp);
						glTranslatef(res[0], res[1], res[2]);
					}
				}

				Rotacao ro = t.getRotacao();
				if (!ro.vazio()){
					float r = glutGet(GLUT_ELAPSED_TIME) % (int)(ro.getTime() * 1000);
					float gr = (r * 360) / (ro.getTime() * 1000);
					glRotatef(gr, ro.getRx(), ro.getRy(), ro.getRz());
				}

				Escala es = t.getEscala();
				if (!es.vazio())
					glScalef(es.getEx(), es.getEy(), es.getEz());
			}		
			p.desenhaComImagem();

			glPopMatrix();
		}
	}
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
	int pos, nump, i=0;
	double a,b,c;
	ifstream file(fl);

	if(file.is_open()) {
		file >> nump; getline(file, line);

		getline(file, line);	pr.setCamdaHorizontal(atoi(line.c_str()));
		getline(file, line);	pr.setCamadaVertical(atoi(line.c_str()));
		
		while(getline(file,line) && i<nump) {
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
			
			i++;
			Ponto po(a,b,c);
			pr.adicionaPonto(po);
		}
		
		i = 0;
		nump = atoi(line.c_str());
		while (getline(file, line) && i < nump) {
			pos = line.find(delimiter);
			token = line.substr(0, pos);
			a = atof(token.c_str());
			line.erase(0, pos + delimiter.length());

			pos = line.find(delimiter);
			token = line.substr(0, pos);
			b = atof(token.c_str());
			line.erase(0, pos + delimiter.length());

			pos = line.find(delimiter);
			token = line.substr(0, pos);
			c = atof(token.c_str());
			line.erase(0, pos + delimiter.length());

			i++;
			Ponto po(a, b, c);
			pr.adicionaNormal(po);
		}
		
		i = 0;
		nump = atoi(line.c_str());
		while (getline(file, line) && i < nump) {
			pos = line.find(delimiter);
			token = line.substr(0, pos);
			a = atof(token.c_str());
			line.erase(0, pos + delimiter.length());

			pos = line.find(delimiter);
			token = line.substr(0, pos);
			b = atof(token.c_str());
			line.erase(0, pos + delimiter.length());

			i++;
			Ponto po(a, b, 0);
			pr.adicionaTextura(po);
		}
		file.close();
		return 0;
	} else {
		cout << "Nao foi possivel ler o arquivo" << endl;
		return -1;
	}
}

Translacao verificaTranslacoes(XMLElement* transformacao) {
	float tempo = 0;
	vector<Ponto> tr;

	if (strcmp(transformacao->Value(), "translacao") == 0) {
		if (transformacao->Attribute("tempo"))
			tempo = stof(transformacao->Attribute("tempo"));

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
			tr.push_back(pt);		
		}
	}
	Translacao trs = Translacao::Translacao(tempo, tr, tr.size());
		trs.execCurvas();
	return trs;
}

Rotacao verificaRotacao(XMLElement* transformacao){
	float rotX, rotY, rotZ, tempo;
	rotX = rotY = rotZ = tempo = 0;

	if(transformacao->Attribute("tempo"))
		tempo= stof(transformacao->Attribute("tempo"));

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
	escX = escY = escZ = 1;

	if (transformacao->Attribute("X"))
		escX = stof(transformacao->Attribute("X"));

	if (transformacao->Attribute("Y"))
		escY = stof(transformacao->Attribute("Y"));

	if (transformacao->Attribute("Z"))
		escZ = stof(transformacao->Attribute("Z"));
	
	return Escala::Escala(escX, escY, escZ);
}

void parseXML(XMLElement* grupo, Transformacao transf, char cc) {
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
			p.setImagem(modelo->Attribute("textura"));
			p.setTransformacao(trans);
			p.setTipo(cc);
			int n = primitivas.size();

			if (n > 1 && primitivas[n - 1].getTipo() == 'I' && cc == 'F') {
				primitivas[n - 1].adicionaFilho(p);
			} else
				primitivas.push_back(p);

			cout << "TIPO: " << p.getTipo() << endl;
			cout << "Translacao: "<< trans.getTranslacao().getTime() << endl;
			cout << "Rotacao   : " << trans.getRotacao().getRx() << " - " << trans.getRotacao().getRy() << " - " << trans.getRotacao().getRz() << endl;
			cout << "Escala    : " << trans.getEscala().getEx() << " - " << trans.getEscala().getEy() << " - " << trans.getEscala().getEz() << endl;
		}
	}
	
	//faz o mesmo de cima para grupos filhos
	if(grupo->FirstChildElement("grupo")) {
		cout << "Vou para os Filhos" << endl;
		parseXML(grupo->FirstChildElement("grupo"),trans,'F');
	}

	//faz o mesmo de cima para grupos irmãos
	if(grupo->NextSiblingElement("grupo")) {
		cout << "Vim para os Irmaos" << endl;
		parseXML(grupo->NextSiblingElement("grupo"),transf,'I');
	}
}

void readXML(string fxml) {
	XMLDocument doc;
	doc.LoadFile(fxml.c_str());
	XMLElement* cena = doc.FirstChildElement("cena")->FirstChildElement("grupo");
	Transformacao t = Transformacao::Transformacao();
	parseXML(cena, t,'P');
}

void initPrimitivas() {
	int num = primitivas.size();
	cout << num << endl;
	for (int i = 0; i < num; i++) {
		if (primitivas[i].numeroFilhos() == 1)
			primitivas[i].getFilhos()[0].prepararComImagem();
		
		primitivas[i].prepararComImagem();
	}
}

int main(int argc, char **argv) {
	//string file="SistemaSolar3Fase.xml";
	string file="LUA.xml";
	//string file = "SSTESTE.xml";
	//string file = "TeapotTest.xml";

	//if(argc>1) {
		//string file = argv[1];
		readXML(file);

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
		
		ilInit();
		glewInit();
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_TEXTURE_2D); /* Ativar Texturas */

		initPrimitivas();

		glutMainLoop();
	//}
	return 0;
} 