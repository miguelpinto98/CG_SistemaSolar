#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <GLUT/glut.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "tinyxml2\tinyxml2.h"

using namespace std;
using namespace tinyxml2;

struct sPonto {
	double x;
	double y;
	double z;
};

vector<sPonto> pontos;

#define CONST 0.1f;
float xx=0, yy=0, zz=0, angle = 0.0f;
float camX = 0, camY, camZ = 5;
int startX, startY, tracking = 0;

int alpha = 0, beta = 0, r = 5;

void changeSize(int w, int h) {
	// Prevent a divide by zero, when window is too short (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX,camY,camZ, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	glTranslatef(xx,yy,zz);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
		for(int i=0; i<pontos.size(); i++)
			glVertex3f(pontos[i].x,pontos[i].y,pontos[i].z);
	glEnd();

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

void lerFicheiro(string fl) {
	string line, token, delimiter = ",";
	int pos;
	double a,b,c;
	ifstream file(fl);
	sPonto pp;

	if(file.is_open()) {
		while(getline(file,line)) {
			pos = line.find(delimiter);
			token = line.substr(0,pos);
			a = atof(token.c_str());
			line.erase(0, pos + delimiter.length());
			pp.x=a;

			pos = line.find(delimiter);
			token = line.substr(0,pos);
			b = atof(token.c_str());
			line.erase(0, pos + delimiter.length());
			pp.y=b;

			pos = line.find(delimiter);
			token = line.substr(0,pos);
			c = atof(token.c_str());
			line.erase(0, pos + delimiter.length());
			pp.z=c;
			
			pontos.push_back(pp);
			//cout<< a << " - " << b << " - " << c << '\n';
		}
		file.close();
	} else {
		cout << "Nao foi possivel ler o arquivo" << endl;
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


void processMouseMotion(int xx, int yy)
{

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
   else if (tracking == 2) {

      alphaAux = alpha;
      betaAux = beta;
      rAux = r - deltaY;
      if (rAux < 3)
         rAux = 3;
   }
   camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
   camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
   camY = rAux *                          sin(betaAux * 3.14 / 180.0);

}

void readXML(string fxml) {
	XMLDocument doc;
	doc.LoadFile(fxml.c_str());
    XMLElement* cena = doc.FirstChildElement("cena");
	XMLElement* grupo = cena->FirstChildElement("grupo");
	XMLElement* grupo2 = grupo->FirstChildElement("grupo");
	  
		for (XMLElement* transformacao = grupo->FirstChildElement(); (strcmp(transformacao->Value(), "modelos")!=0); transformacao = transformacao->NextSiblingElement()) {
		
			if(strcmp(transformacao->Value(), "translacao")==0) {printf("%s - %s, %s, %s\n", transformacao->Value(), transformacao->Attribute("X"), transformacao->Attribute("Y"), transformacao->Attribute("Z"));}
 
			if(strcmp(transformacao->Value(), "rotacao")==0) {printf("%s - %s, %s, %s, %s \n", transformacao->Value(), transformacao->Attribute("angulo"), transformacao->Attribute("eixoX"), transformacao->Attribute("eixoY"), transformacao->Attribute("eixoZ"));}
		 
			if(strcmp(transformacao->Value(), "escala")==0) { printf("%s\n", transformacao->Value());}
		}



		for (XMLElement* modelo = grupo->FirstChildElement("modelos")->FirstChildElement("modelo"); modelo; modelo = modelo->NextSiblingElement()) {
			printf("%s\n", modelo->Attribute("ficheiro"));
		}



		for (XMLElement* transformacao2 = grupo2->FirstChildElement(); (strcmp(transformacao2->Value(), "modelos")!=0); transformacao2 = transformacao2->NextSiblingElement()) {
		
			if(strcmp(transformacao2->Value(), "translacao")==0) {printf("%s - %s, %s, %s\n", transformacao2->Value(), transformacao2->Attribute("X"), transformacao2->Attribute("Y"), transformacao2->Attribute("Z"));}
 
			if(strcmp(transformacao2->Value(), "rotacao")==0) {printf("%s - %s, %s, %s, %s \n", transformacao2->Value(), transformacao2->Attribute("angulo"), transformacao2->Attribute("eixoX"), transformacao2->Attribute("eixoY"), transformacao2->Attribute("eixoZ"));}
		 
			if(strcmp(transformacao2->Value(), "escala")==0) { printf("%s\n", transformacao2->Value());}
		}
	
		
		for (XMLElement* modelo2 = grupo2->FirstChildElement("modelos")->FirstChildElement("modelo"); modelo2; modelo2 = modelo2->NextSiblingElement()) {
			printf("%s\n", modelo2->Attribute("ficheiro"));
		}

}


//cout << str << endl;
//lerFicheiro(str);
int main(int argc, char **argv) {
	if(argc>1) { 
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
		glutInitWindowPosition(100,100);
		glutInitWindowSize(800,800);
		glutCreateWindow("CG@DI-UM");		

		//readXML(argv[1]);
		string xmlmotor="teste63.xml";
		readXML(xmlmotor);

		glutDisplayFunc(renderScene);
		glutIdleFunc(renderScene);
		glutReshapeFunc(changeSize);

		glutKeyboardFunc(normalkeyboard);
		glutSpecialFunc(specialKeys);

		/*Código 28*/
		glutMouseFunc(processMouseButtons);
		glutMotionFunc(processMouseMotion);

		glutCreateMenu(menu);
		glutAddMenuEntry("GL_FILL",1);
		glutAddMenuEntry("GL_LINE",2);
		glutAddMenuEntry("GL_POINT",3);
		glutAddMenuEntry("GL_FRONT",4);
		glutAttachMenu(GLUT_RIGHT_BUTTON);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	
		glutMainLoop();
	}
	return 1;
}