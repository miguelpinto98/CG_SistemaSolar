#include "Estado.h"

Estado::Estado() {
	translacao = Tipo::Tipo();
	rotacao = Tipo::Tipo();
	escala = Tipo::Tipo();
}

Estado::Estado(Tipo t, Tipo r, Tipo e) {
	translacao = t;
	rotacao = r;
	escala = e;
}

bool Estado::estadoVazio() {
	bool res = false;	
	if(translacao.tipoVazio() && rotacao.tipoVazio() && escala.tipoVazio())
		res = true;

	return res;
}

Estado::~Estado(void)
{
}
