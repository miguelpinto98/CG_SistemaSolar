#ifndef _MOTOR3D
#define _MOTOR3D

#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <glew.h>
#include <GL/glut.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "tinyxml2\tinyxml2.h"
#include "Ponto.h"
#include "Primitiva.h"
#include "Estado.h"

#pragma comment(lib, "glew32.lib")

using namespace std;
using namespace tinyxml2;

vector<Primitiva> primitivas;

GLuint buffer[1];


#define CONST 0.1f;

#endif