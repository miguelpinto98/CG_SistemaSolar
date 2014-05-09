#include "Rotacao.h"


Rotacao::Rotacao() {
	time = rx = ry = rz = 0;
}

Rotacao::Rotacao(float t, float x, float y, float z) {
	time = t;
	rx = x;
	ry = y;
	rz = z;
}

bool Rotacao::vazio() {
	return (time == 0 && rx == 0 && ry == 0 && rz == 0) ? true : false;
}

Rotacao::~Rotacao()
{
}
