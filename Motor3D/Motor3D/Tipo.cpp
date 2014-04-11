#include "Tipo.h"


Tipo::Tipo() {
	x = 0;
	y = 0;
	z = 0;
	ang = 0;
}

Tipo::Tipo(float xx, float yy, float zz) {
	x = xx;
	y = yy;
	z = zz;
	ang = 0;
}

Tipo::Tipo(float a, float xx, float yy, float zz) {
	x = xx;
	y = yy;
	z = zz;
	ang = a;
}

bool Tipo::tipoVazio() {
	bool res = false;
	if(x==0 && y==0 && z==0 && ang==0)
		res = true;

	return res;
}

Tipo::~Tipo(void)
{
}
