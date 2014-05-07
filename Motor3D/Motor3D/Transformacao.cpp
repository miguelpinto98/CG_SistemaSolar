#include "Transformacao.h"

Transformacao::Transformacao() {
	translacao = Translacao::Translacao();
	rotacao = Rotacao::Rotacao();
	escala = Escala::Escala();
}

Transformacao::Transformacao(Translacao t, Rotacao r, Escala e) {
	translacao = t;
	rotacao = r;
	escala = e;
}

bool Transformacao::trasnformacaoVazia() {
	return (translacao.vazio() && rotacao.vazio() && escala.vazio()) ? true : false;
}

Transformacao::~Transformacao(void)
{
}
