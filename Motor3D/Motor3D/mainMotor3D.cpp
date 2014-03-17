#include <stdlib.h>

#include <GL/glut.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
 #include <iostream>
 #include <string>

using namespace std;

float CONST = 0.1;

// angle of rotation for the camera direction
float angle = 0.0f;

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;

// XZ position of the camera
float x=0.0f, z=5.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
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

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void computeDir(float deltaAngle) {

	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}

void renderScene(void) {

	if (deltaMove)
		computePos(deltaMove);
	if (deltaAngle)
		computeDir(deltaAngle);

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(x,0.0,z, 
		      lx+x,0.0,lz+z,
			  0.0f,1.0f,0.0f);

	//glTranslatef(x,0,z);
    //glRotatef(angulo, 0.0f, 1.0f, 0.0f);

// pôr instruções de desenho aqui
	glBegin(GL_TRIANGLES);
	
	string line, token;
	string delimiter = ",";
	int pos;
	double a,b,c;
	ifstream file("paralelipipedo.3d");
	//ifstream file("plano.3d");
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
	glEnd();

	// End of frame
	glutSwapBuffers();
}

// escrever função de processamento do teclado
	void normalkeyboard(unsigned char tecla, int x, int y) {
		switch (tecla) {
			case 'a':
			case 'A': x-=CONST; break;
			case 'd': 
			case 'D': x+=CONST; break;
			case 'w':
			case 'W': z+=CONST; break;
			case 's':
			case 'S': z-=CONST; break;
			case 'e':
			case 'E': angle-=5.0f; break;
			case 'q':
			case 'Q': angle+=5.0f; break;
		}
		glutPostRedisplay();
	}

void pressKey(int key, int xx, int yy) {

	switch (key) {
		case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
		case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
		case GLUT_KEY_UP : deltaMove = 0.5f; break;
		case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : deltaMove = 0;break;
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

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else  {// state = GLUT_DOWN
			xOrigin = x;
		}
	}
}

void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
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
	glutSpecialFunc(pressKey);

	// here are the new entries
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);
	glutMouseFunc(mouseButton);
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