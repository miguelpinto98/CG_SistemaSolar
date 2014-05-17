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
	vector<Primitiva> filhos;
	char tipo;
public:
	Primitiva(string);
	vector<Ponto> pontos;
	string getNomePrimitiva() { return nome; }
	vector<Ponto> getPontos() { return pontos; }
	Transformacao getTransformacao() { return transf; }
	void setTransformacao(Transformacao t) { transf = t; }
	void setTipo(char c) { tipo = c; }
	char getTipo() { return tipo; }
	void adicionaPonto(Ponto p);
	vector<Primitiva> getFilhos() { return filhos; }
 	Primitiva getFilho(int n) { return filhos[n]; }
	int numeroFilhos();
	void adicionaFilho(Primitiva p);
	void construir();
	void desenhar();
	void preparar();
	virtual ~Primitiva(void);
};

