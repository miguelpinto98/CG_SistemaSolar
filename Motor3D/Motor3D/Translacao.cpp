#include "Translacao.h"


Translacao::Translacao() {
	time = 0;
}

Translacao::Translacao(int t) {
	time = t;
}

bool Translacao::vazio() {
	return (time == 0) ? true : false;
}

void Translacao::setTime(int t) {
	time = t;
}

Translacao::~Translacao()
{
}
