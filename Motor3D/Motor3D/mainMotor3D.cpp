#include <stdlib.h>

#include <GL/glut.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
 #include <iostream>
 #include <string>

using namespace std;

#define CONST 0.1f;

float xx = 0.0f, zz = 0.0f, angulo = 0.0f, altura = 1.5;

// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=5.0f;

float deltaAngle = 0.0f;
int xOrigin = -1;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
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

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(x,0.0,z, 
		      lx+x,0.0,lz+z,
			  0.0f,1.0f,0.0f);
	

	glTranslatef(xx,0,zz);
    glRotatef(angulo, 0.0f, 1.0f, 0.0f);

// pôr instruções de desenho aqui
	double larg=2, compr=6;
	int cmdh=2,cmdv=2;
	string str;
	glBegin(GL_TRIANGLES);

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

				glVertex3f(a,b,c);
				//cout<< a << " - " << b << " - " << c << '\n';
				//i++;
			//}
		}
		file.close();
	} else {
		cout << "Not OK!";
	}
	/*
	double x, y=-(larg/2), z=y;
	double vr=compr/cmdv, hr=larg/cmdh;
	double ax, ay=y+hr, az=larg/2;
	int i,j;

	//BACK AND FRONT
	for(i=0; i<cmdh; i++) {
		x=-(compr/2);
		ax=x+vr;
		for(j=0; j<cmdv; j++) {
			glVertex3f(x,y,z);
			glVertex3f(ax,y,z);
			glVertex3f(ax,ay,z);

			glVertex3f(x,y,z);
			glVertex3f(ax,ay,z);
			glVertex3f(x,ay,z);

			glVertex3f(x,y,az);
			glVertex3f(ax,y,az);
			glVertex3f(ax,ay,az);

			glVertex3f(x,y,az);
			glVertex3f(ax,ay,az);
			glVertex3f(x,ay,az);

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
			glVertex3f(x,y,z);
			glVertex3f(ax,y,z);
			glVertex3f(ax,y,az);

			glVertex3f(x,y,z);
			glVertex3f(ax,y,az);
			glVertex3f(x,y,az);

			glVertex3f(x,ay,z);
			glVertex3f(ax,ay,z);
			glVertex3f(ax,ay,az);

			glVertex3f(x,ay,z);
			glVertex3f(ax,ay,az);
			glVertex3f(x,ay,az);

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
			glVertex3f(x,y,z);
			glVertex3f(x,y,az);
			glVertex3f(x,ay,az);

			glVertex3f(x,y,z);
			glVertex3f(x,ay,az);
			glVertex3f(x,ay,z);
			
			glVertex3f(ax,y,z);
			glVertex3f(ax,y,az);
			glVertex3f(ax,ay,az);

			glVertex3f(ax,y,z);
			glVertex3f(ax,ay,az);
			glVertex3f(ax,ay,z);

			z=az;
			az+=hr;
		}
		y=ay;
		ay+=hr;
	} */

	glEnd();

	// End of frame
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
			case 'W': zz+=CONST; break;
			case 's':
			case 'S': zz-=CONST; break;
			case 'e':
			case 'E': angulo-=5.0f; break;
			case 'q':
			case 'Q': angulo+=5.0f; break;
		}
		glutPostRedisplay();
	}

	void arrowKeyboards(int tecla, int x, int y) {
		switch (tecla) {
		case GLUT_KEY_LEFT: break;
		case GLUT_KEY_RIGHT: break;
		case GLUT_KEY_UP: angulo+=0.1f; break;
		case GLUT_KEY_DOWN: altura-=0.1f; break;
		}
		glutPostRedisplay();
	}

	void mouseMove(int x, int y) {
		if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
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


int main(int argc, char **argv) {


// inicialização
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		

// registo de funções 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

// pôr aqui registo da funções do teclado e rato
	glutKeyboardFunc(normalkeyboard);
	glutSpecialFunc(arrowKeyboards);

	glutMotionFunc(mouseMove);

// pôr aqui a criação do menu
	glutCreateMenu(menu);
	glutAddMenuEntry("GL_FILL",1);
	glutAddMenuEntry("GL_LINE",2);
	glutAddMenuEntry("GL_POINT",3);
	glutAddMenuEntry("GL_FRONT",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


// alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// entrar no ciclo do GLUT 
	glutMainLoop();

	return 1;
}