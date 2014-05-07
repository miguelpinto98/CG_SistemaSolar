#pragma once

#include <vector>
#include "Ponto.h"

using namespace std;

class Translacao
{
	float time;
	vector<Ponto> transPontos;
public:
	Translacao();
	Translacao(float);
	Translacao(float,vector<Ponto>);
	float getTime() { return time; }
	vector<Ponto> getTransPontos() { return transPontos; }
	void setTime(float);
	bool vazio();
	virtual ~Translacao();
};

