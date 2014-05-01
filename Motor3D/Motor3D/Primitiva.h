#pragma once

#include <vector>
#include <GL\glew.h>
#include <GL\glut.h>

#include "Ponto.h"
#include "Transformacao.h"

using namespace std;

class Primitiva {
	string nome;
	Transformacao transf;
	GLuint *buffer;
	int nvertices;
public:
	Primitiva(string);
	vector<Ponto> pontos;
	string getNomePrimitiva() { return nome; }
	vector<Ponto> getPontos() { return pontos; }
	Transformacao getTransformacao() { return transf; }
	void setTransformacao(Transformacao t) { transf = t; }
	void adicionaPonto(Ponto p);
	void construir();
	void desenhar();
	void preparar();
	virtual ~Primitiva(void);
};

