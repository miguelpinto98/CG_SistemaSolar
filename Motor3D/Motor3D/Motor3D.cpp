#include "Motor3D.h"

float xx=0, yy=0, zz=0, angle = 0.0f;
float camX = 0, camY, camZ = 5;
int startX, startY, tracking = 0;

int alpha = 0, beta = 0, r = 5;

/* FRAMES PER SECOND */
int timebase = 0, frame = 0;

/* Numero Vertices */
int nvertices;

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

void desenhaPrimitiva() {
	glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_TRIANGLES, 0, nvertices);
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

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX,camY,camZ, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	glTranslatef(xx,yy,zz);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

	framesPerSecond();

	desenhaPrimitiva();

	/* Cenário Imediato */
	/*
	int ipr = primitivas.size(), jpon;
	vector<Ponto> ress;



	for(int i=0; i<ipr; i++) {
		jpon = primitivas[i].getPontos().size();
		ress = primitivas[i].getPontos();
		Transformacao t = primitivas[i].getTransformacao();
		Tipo tp;

		if(!t.trasnformacaoVazia()) {
			tp = t.getTranslacao();
			if(!tp.tipoVazio()) {
				//cout << tp.getTX() << " - " <<tp.getTY() << " - " << tp.getTZ() << endl;
				glTranslatef(tp.getTX(),tp.getTY(),tp.getTZ()); 
			}

			tp=t.getRotacao(); 
			if(!tp.tipoVazio())
				glRotatef(tp.getTAng(), tp.getTX(),tp.getTY(),tp.getTZ());
			
			tp=t.getEscala();
			if(!tp.tipoVazio())
				glScalef(tp.getTX(),tp.getTY(),tp.getTZ()); 
		}
		
		glBegin(GL_TRIANGLES);
		for(int j=0; j< jpon; j++) {
			glVertex3f(ress.at(j).getX(), ress.at(j).getY(), ress.at(j).getZ());
		}
		glEnd();
	}
	*/
	glutSwapBuffers();
}

// escrever função de processamento do teclado
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


// escrever função de processamento do menu
void menu(int op) {
	switch (op) {
		case 1: glPolygonMode(GL_FRONT, GL_FILL); break;
		case 2: glPolygonMode(GL_FRONT, GL_LINE); break;
		case 3: glPolygonMode(GL_FRONT, GL_POINT); break;
	}
	glutPostRedisplay();
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
   } else 
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

void teste(XMLElement* grupo, Transformacao transf) {
	Transformacao tr;
	Tipo tp;

	if(strcmp(grupo->FirstChildElement()->Value(), "grupo")==0) 
		grupo=grupo->FirstChildElement();
	
	//transformações para um grupo
	for (XMLElement* transformacao = grupo->FirstChildElement(); (strcmp(transformacao->Value(), "modelos")!=0); transformacao = transformacao->NextSiblingElement()) {
		//translacao
		if(strcmp(transformacao->Value(), "translacao")==0) {
			float tmp;

			if(transformacao->Attribute("tempo") == NULL)
				tmp=0;
			else 
				tmp= stof(transformacao->Attribute("tempo"));


			//printf("%s - %f\n", transformacao->Value(), tmp);
	
			Tipo x = transf.getTranslacao();
			tp = Tipo::Tipo(transX+x.getTX(),transY+x.getTY(),transZ+x.getTZ());
			tr.setTranslacao(tp);
		}
		
		//rotacao
		if(strcmp(transformacao->Value(), "rotacao")==0) {
			float t, EixoX, EixoY, EixoZ;

			if(transformacao->Attribute("tempo") == NULL) 
				t=0;
			else 
				t= stof(transformacao->Attribute("tempo"));

			if(transformacao->Attribute("eixoX") == NULL)
				EixoX=0;
			else 
				EixoX= stof(transformacao->Attribute("eixoX"));

			if(transformacao->Attribute("eixoY") == NULL)
				EixoY=0;
			else 
				EixoY= stof(transformacao->Attribute("eixoY"));

			if(transformacao->Attribute("eixoZ") == NULL)
				EixoZ=0;
			else 
				EixoZ= stof(transformacao->Attribute("eixoZ"));

			//printf("%s - %f, %f, %f, %f \n", transformacao->Value(), t, EixoX, EixoY, EixoZ);

			Tipo x = transf.getRotacao();
			tp = Tipo::Tipo(t+x.getTt(),EixoX+x.getTX(),EixoY+x.getTY(),EixoZ+x.getTZ());
			tr.setRotacao(tp);
		} else {
			tr.setRotacao(transf.getRotacao());
		}
			
		 
		//escala
		if(strcmp(transformacao->Value(), "escala")==0) {
			float escX, escY, escZ;

			if(transformacao->Attribute("X") == NULL)
				escX=0;
			else 
				escX= stof(transformacao->Attribute("X"));

			if(transformacao->Attribute("Y") == NULL)
				escY=0;
			else 
				escY= stof(transformacao->Attribute("Y"));

			if(transformacao->Attribute("Z") == NULL)
				escZ=0;
			else 
				escZ= stof(transformacao->Attribute("Z"));

			//printf("%s - %f, %f, %f\n", transformacao->Value(), escX, escY, escZ);

			Tipo x = transf.getEscala();
			tp = Tipo::Tipo(escX*x.getTX(),escY*x.getTY(),escZ*x.getTZ());
			tr.setEscala(tp);
		} else {
			tr.setEscala(transf.getEscala());
		}
	}

	//para o mesmo grupo, quais os modelos(ficheiros) que recebem as transformações
	for (XMLElement* modelo = grupo->FirstChildElement("modelos")->FirstChildElement("modelo"); modelo; modelo = modelo->NextSiblingElement("modelo")) {
		int flag;
		Primitiva p(modelo->Attribute("ficheiro"));
		cout << p.getNomePrimitiva() << endl;
		flag = lerFicheiro(p.getNomePrimitiva(),p);

		if(flag>=0) { 
			p.setTransformacao(tr);
			primitivas.push_back(p);

			cout << tr.getTranslacao().getTX() << " - " << tr.getTranslacao().getTY() << " - " << tr.getTranslacao().getTZ() << endl;
			cout << tr.getRotacao().getTAng() << " - " << tr.getRotacao().getTX() << " - " << tr.getRotacao().getTY() << " - " << tr.getRotacao().getTZ() << endl;
			cout << tr.getEscala().getTX() << " - " << tr.getEscala().getTY() << " - " << tr.getEscala().getTZ() << endl;
		}
	}
	
	//faz o mesmo de cima para grupos filhos
	if(grupo->FirstChildElement("grupo")) {
		teste(grupo->FirstChildElement("grupo"),tr);
	}

	//faz o mesmo de cima para grupos irmãos
	if(grupo->NextSiblingElement("grupo")) {
		teste(grupo->NextSiblingElement("grupo"),transf);
	}
}


void readXML(string fxml) {
	XMLDocument doc;
	doc.LoadFile(fxml.c_str());
	XMLElement* cena = doc.FirstChildElement("cena")->FirstChildElement("grupo");
	Transformacao t = Transformacao::Transformacao();
	t.setEscala(Tipo::Tipo(1,1,1));
	teste(cena,t);
}

void defineMenu() {
	glutCreateMenu(menu);

	glutAddMenuEntry("GL_FILL",1);
	glutAddMenuEntry("GL_LINE",2);
	glutAddMenuEntry("GL_POINT",3);
	glutAddMenuEntry("GL_FRONT",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void preparaPrimitivas() {
	Primitiva p = primitivas[1];
	int tpontos = p.getPontos().size(), lados = tpontos/3, j;
	vector<Ponto> ress = p.getPontos();


	nvertices = tpontos*3;
	glEnableClientState(GL_VERTEX_ARRAY);

	float *vertexB = (float *)malloc(sizeof(float) * nvertices);

	j=0;
	for(int i=0; i<tpontos; i++) {
		Ponto xyz = ress.at(i);

		vertexB[j+0] = xyz.getX();
		vertexB[j+1] = xyz.getY();
		vertexB[j+2] = xyz.getZ();

		j+=3;
	}
	nvertices = j;

	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, nvertices*sizeof(float), vertexB, GL_STATIC_DRAW);

	free(vertexB);
}

int main(int argc, char **argv) {
	//string xmlmotor="exemplo1.xml";
	//string xmlmotor="exemplo2.xml";
	string xmlmotor="exemplo3.xml";
	//string xmlmotor="exemplo4.xml";
	//string xmlmotor="exemplo5.xml";
	//string xmlmotor="exemplo6.xml";
	//string xmlmotor="exemploInv1.xml";
	//string xmlmotor="sistemasolar1.xml";
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
			preparaPrimitivas();

	
		glutMainLoop();
	//}
	return 1;
}