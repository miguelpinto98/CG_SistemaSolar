#include "Translacao.h"

Translacao::Translacao() {
	time = 0;
}

Translacao::Translacao(float t) {
	time = t;
}

Translacao::Translacao(float t, vector<Ponto> vtp, int num) {
	time = t;
	transPontos = vtp;
	tam = num;
}

bool Translacao::vazio() {
	return (time == 0 && transPontos.size() == 0) ? true : false;
}

void Translacao::setTime(float t) {
	time = t;
}

Translacao::~Translacao()
{
}
