#pragma once
#include "Tipo.h"

class Transformacao {
	Tipo translacao;
	Tipo rotacao;
	Tipo escala;
public:
	Transformacao();
	Transformacao(Tipo, Tipo, Tipo);
	Tipo getTranslacao() { return translacao; }
	Tipo getRotacao() { return rotacao; }
	Tipo getEscala() { return escala; }
	void setTranslacao(Tipo t) { translacao = t; }
	void setRotacao(Tipo t) { rotacao = t; }
	void setEscala(Tipo t) { escala = t; }
	bool trasnformacaoVazia();
	~Transformacao(void);
};