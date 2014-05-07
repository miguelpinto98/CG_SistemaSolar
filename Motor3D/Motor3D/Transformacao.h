#pragma once
#include "Tipo.h"
#include "Translacao.h"

class Transformacao {
	Translacao translacao;
	Tipo rotacao;
	Tipo escala;
public:
	Transformacao();
	Transformacao(Translacao, Tipo, Tipo);
	Translacao getTranslacao() { return translacao; }
	Tipo getRotacao() { return rotacao; }
	Tipo getEscala() { return escala; }
	void setTranslacao(Translacao t) { translacao = t; }
	void setRotacao(Tipo t) { rotacao = t; }
	void setEscala(Tipo t) { escala = t; }
	bool trasnformacaoVazia();
	~Transformacao(void);
};