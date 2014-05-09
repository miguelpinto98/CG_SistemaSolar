#include <iostream>
#include <GL/glut.h>
#include <math.h>


#define POINT_COUNT 16
float a=1.3;
float p[POINT_COUNT][3] = {{-1.05*a,-1.05*a,0},{-1.4*a,-0.5*a,0*a},{-1.5*a,0,0},{-1.4*a,0.5*a,0},
						   {-1.05*a,1.05*a,0},{-0.5*a,1.4*a,0},{0,1.5*a,0},{0.5*a,1.4*a,0},
						   {1.05*a,1.05*a,0},{1.4*a,0.5*a,0},{1.5*a,0,0},{1.4*a,-0.5*a,0},
						   {1.05*a,-1.05*a,0},{0.5*a,-1.4*a,0},{0,-1.5*a,0},{-0.5*a,-1.4*a,0}};




void getCatmullRomPoint(float t, int *indices, float *res) {
   int i;
	float res_aux[4];
	
	float m[4][4] = {{-0.5f,  1.5f, -1.5f,  0.5f},
					  { 1.0f, -2.5f,  2.0f, -0.5f},
					  {-0.5f,  0.0f,  0.5f,  0.0f},
					   { 0.0f,  1.0f,  0.0f,  0.0f}};
		
	res[0] = 0.0;
	res[1] = 0.0;
	res[2] = 0.0;
     
   //TESSELACAO*M
	res_aux[0]= pow(t,3)*m[0][0] + pow(t,2)*m[1][0] + t*m[2][0] + m[3][0];
	res_aux[1]= pow(t,3)*m[0][1] + pow(t,2)*m[1][1] + t*m[2][1] + m[3][1];
	res_aux[2]= pow(t,3)*m[0][2] + pow(t,2)*m[1][2] + t*m[2][2] + m[3][2];
	res_aux[3]= pow(t,3)*m[0][3] + pow(t,2)*m[1][3] + t*m[2][3] + m[3][3];


   
    //TESSELACAO*M*P = res
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
	indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;
	indices[1] = (indices[0]+1)%POINT_COUNT;
	indices[2] = (indices[1]+1)%POINT_COUNT;
	indices[3] = (indices[2]+1)%POINT_COUNT;

	getCatmullRomPoint(t, indices, res);
}

void renderCatmullRomCurve() {
    float res[3];
    
    glBegin(GL_LINE_LOOP);
    for (float gt=0; gt<1; gt+=0.0001){
        getGlobalCatmullRomPoint(gt,res);
        glVertex3fv(res);
    }
    glEnd();
}


void changeSize(int w, int h) {
    
	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;
    
	// compute window's aspect ratio
	float ratio = w * 1.0 / h;
    
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    
	// Set the correct perspective
	gluPerspective(45,ratio,1,1000);
    
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
    
	static float a = 0;
	float res[3];
    
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
    
	renderCatmullRomCurve();
    
	glPushMatrix();
	getGlobalCatmullRomPoint(a,res);
	glTranslatef(res[0],res[1],res[2]);
	glScalef(0.1, 0.1, 0.1);
	glutWireTeapot(1);
	glPopMatrix();
    
    glutSwapBuffers();
	a+=0.01;
}

int main(int argc, char **argv) {
    
    // pÙr inicializaÁ„o aqui
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1200,800);
    glutCreateWindow("CG@DI");
    
    // registo de funÁıes
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
    
   
    
    // alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
    
    // entrar no ciclo do GLUT aqui
	glutMainLoop();
    
    return 0;
    
}