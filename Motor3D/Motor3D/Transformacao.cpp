#include "Transformacao.h"

Transformacao::Transformacao() {
	translacao = Tipo::Tipo();
	rotacao = Tipo::Tipo();
	escala = Tipo::Tipo();
}

Transformacao::Transformacao(Tipo t, Tipo r, Tipo e) {
	translacao = t;
	rotacao = r;
	escala = e;
}

bool Transformacao::trasnformacaoVazia() {
	bool res = false;	
	if(translacao.tipoVazio() && rotacao.tipoVazio() && escala.tipoVazio())
		res = true;

	return res;
}

Transformacao::~Transformacao(void)
{
}
