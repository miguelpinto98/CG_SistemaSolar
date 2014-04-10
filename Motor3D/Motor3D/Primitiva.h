#pragma once
#include <vector>
#include <iostream>
#include "Ponto.h"
#include "Estado.h"

using namespace std;

class Primitiva {
	string nome;
	Estado estado;
public:
	Primitiva(string);
	vector<Ponto> pontos;
	string getNomePrimitiva() { return nome; }
	vector<Ponto> getPontos() { return pontos; }
	void adicionaPonto(Ponto p);
	virtual ~Primitiva(void);
};

