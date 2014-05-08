#ifndef _MOTOR3D
#define _MOTOR3D

#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
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

#endif