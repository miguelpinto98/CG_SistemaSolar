#pragma once
#include <vector>
#include <iostream>
#include "Ponto.h"
#include "Transformacao.h"

using namespace std;

class Primitiva {
	string nome;
	Transformacao transf;
public:
	Primitiva(string);
	vector<Ponto> pontos;
	string getNomePrimitiva() { return nome; }
	vector<Ponto> getPontos() { return pontos; }
	void adicionaPonto(Ponto p);
	virtual ~Primitiva(void);
};

