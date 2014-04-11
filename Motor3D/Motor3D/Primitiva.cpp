#include "Primitiva.h"

Primitiva::Primitiva(string n) {
	nome = n;
}

void Primitiva::adicionaPonto(Ponto p) {
	pontos.push_back(p);
}

Primitiva::~Primitiva(void)
{
}
