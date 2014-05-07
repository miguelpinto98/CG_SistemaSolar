#pragma once
#include "Translacao.h"
#include "Rotacao.h"
#include "Escala.h"

class Transformacao {
	Translacao translacao;
	Rotacao rotacao;
	Escala escala;
public:
	Transformacao();
	Transformacao(Translacao, Rotacao, Escala);
	Translacao getTranslacao() { return translacao; }
	Rotacao getRotacao() { return rotacao; }
	Escala getEscala() { return escala; }
	void setTranslacao(Translacao t) { translacao = t; }
	void setRotacao(Rotacao t) { rotacao = t; }
	void setEscala(Escala t) { escala = t; }
	bool trasnformacaoVazia();
	~Transformacao(void);
};