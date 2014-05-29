#pragma once

#include <vector>
#include <GL\glew.h>
#include <GL\glut.h>
#include <IL\il.h>

#include "Ponto.h"
#include "Transformacao.h"

#include <fstream>
#include <iostream>
#include <string>

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
	string imagem;
	unsigned int ima;
	unsigned int texID;
	unsigned char *imageData;
public:
	Primitiva(string);
	vector<Ponto> pontos;
	vector<Ponto> normais;
	vector<Ponto> texturas;
	void adicionaNormal(Ponto p);
	void adicionaTextura(Ponto p);
	string getNomePrimitiva() { return nome; }
	void setImagem(string file) { imagem = file; }
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
	void Primitiva::prepararComImagem();
	void carregaImagem(string);
	unsigned int getTexID() { return texID; }
	void desenhaComImagem();
	virtual ~Primitiva(void);
};

