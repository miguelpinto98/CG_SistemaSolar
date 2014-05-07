#include "Transformacao.h"

Transformacao::Transformacao() {
	translacao = Translacao::Translacao();
	rotacao = Tipo::Tipo();
	escala = Tipo::Tipo();
}

Transformacao::Transformacao(Translacao t, Tipo r, Tipo e) {
	translacao = t;
	rotacao = r;
	escala = e;
}

bool Transformacao::trasnformacaoVazia() {
	bool res = false;	
	if(translacao.vazio() && rotacao.tipoVazio() && escala.tipoVazio())
		res = true;

	return res;
}

Transformacao::~Transformacao(void)
{
}
