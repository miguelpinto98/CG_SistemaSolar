#pragma once
#include <vector>
#include <iostream>
#include "Ponto.h"

using namespace std;

class Vertices {

public:
	vector<Ponto> pontos;
	vector<Ponto> getPontos() { return pontos; }
	void adicionaPonto(Ponto p);
	virtual ~Vertices(void);
};