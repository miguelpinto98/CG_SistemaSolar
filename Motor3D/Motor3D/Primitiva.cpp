#include "Primitiva.h"

Primitiva::Primitiva(string nome) {
	nome = nome;
	transf = Transformacao::Transformacao();
	}

void Primitiva::adicionaPonto(Ponto p) {
	pontos.push_back(p);
}

Primitiva::~Primitiva(void)
{
}
