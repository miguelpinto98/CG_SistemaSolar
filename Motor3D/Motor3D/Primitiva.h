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
	GLuint buffers[3];
	int nvertices;
	int *indices;
	vector<Primitiva> filhos;
	char tipo;
	int cmdHor;
	int cmdVer;
	int numsInd;
public:
	Primitiva(string);
	vector<Ponto> pontos;
	vector<Ponto> normais;
	vector<Ponto> texturas;
	void adicionaNormal(Ponto p);
	void adicionaTextura(Ponto p);
	string getNomePrimitiva() { return nome; }
	vector<Ponto> getPontos() { return pontos; }
	Transformacao getTransformacao() { return transf; }
	void setTransformacao(Transformacao t) { transf = t; }
	void setTipo(char c) { tipo = c; }
	void setCamdaHorizontal(int c) { cmdHor = c; }
	void setCamadaVertical(int c) { cmdVer= c; }
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

