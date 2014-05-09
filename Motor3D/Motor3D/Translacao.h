#pragma once

#include <vector>
#include "Ponto.h"

using namespace std;

class Translacao
{
	float time;
	vector<Ponto> transPontos;
	vector<Ponto> curvasPontos;
	int tam;
public:
	Translacao();
	Translacao(float);
	Translacao(float,vector<Ponto>,int);
	float getTime() { return time; }
	int getTamanho() { return tam; }
 	vector<Ponto> getTransPontos() { return transPontos; }
	vector<Ponto> getPontosCurvas() { return curvasPontos; }
	void setTime(float);
	void Translacao::getGlobalCatmullRomPoint(float, float *, vector<Ponto>);
	void execCurvas();
	bool vazio();
	virtual ~Translacao();
};

