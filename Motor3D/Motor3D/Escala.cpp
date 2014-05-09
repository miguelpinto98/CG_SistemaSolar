#include "Escala.h"

Escala::Escala() {
	ex = 0;
	ey = 0;
	ez = 0;
}

Escala::Escala(float xx, float yy, float zz) {
	ex = xx;
	ey = yy;
	ez = zz;
}

bool Escala::vazio() {
	return (ex == 0 && ey == 0 && ez == 0) ? true : false;
}

Escala::~Escala(void)
{
}
