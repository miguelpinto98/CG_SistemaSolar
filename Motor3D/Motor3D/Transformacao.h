#pragma once
#include "Tipo.h"

class Transformacao {
	Tipo translacao;
	Tipo rotacao;
	Tipo escala;
public:
	Transformacao();
	Transformacao(Tipo, Tipo, Tipo);
	bool trasnformacaoVazia();
	~Transformacao(void);
};