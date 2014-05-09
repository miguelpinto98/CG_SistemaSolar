#pragma once

#include <vector>
#include "Ponto.h"

using namespace std;

class Translacao
{
	float time;
	vector<Ponto> transPontos;
	int tam;
public:
	Translacao();
	Translacao(float);
	Translacao(float,vector<Ponto>,int);
	float getTime() { return time; }
	int getTamanho() { return tam; }
 	vector<Ponto> getTransPontos() { return transPontos; }
	void setTime(float);
	bool vazio();
	virtual ~Translacao();
};

