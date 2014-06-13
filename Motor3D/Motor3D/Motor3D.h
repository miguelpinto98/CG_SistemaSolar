#ifndef _MOTOR3D
#define _MOTOR3D

#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <IL/il.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "tinyxml2\tinyxml2.h"
#include "Ponto.h"
#include "Primitiva.h"
#include "Translacao.h"
#include "Rotacao.h"
#include "Escala.h"


#pragma comment(lib, "glew32.lib")

using namespace std;
using namespace tinyxml2;

vector<Primitiva> primitivas;

/* CAMARA - TECLADO */
float anguloX = 0.0f, anguloY = 0.0f, anguloZ = 0.0f;
float coordX = 0, coordY = 0, coordZ = 0;

/* CAMARA - RATO */
float camX = 0, camY, camZ = 5;
int startX, startY, tracking = 0;
int alpha = 0, beta = 0, r = 5;

/* FRAMES PER SECOND */
int timebase = 0, frame = 0;

/* LUZES */
string tipo; 
float posX, posY, posZ;

#endif