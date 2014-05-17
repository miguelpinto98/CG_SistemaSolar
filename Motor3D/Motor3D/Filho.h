#pragma once

#include "Transformacao.h"
#include <vector>
#include <GL\glew.h>
#include <GL\glut.h>

class Filho {
	vector<Ponto> pontos;
	Transformacao transf;
	GLuint *buffer;
	int nvertices;
public:
	void desenhar();
	void preparar();
	Filho();
	~Filho();
};

