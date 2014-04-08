#include "Primitiva.h"

Primitiva::Primitiva(string name){
	nome = name;
	pontos.begin();
}

void Primitiva::adicionaPonto(Ponto p) {
	pontos.push_back(p);
}

Primitiva::~Primitiva(void)
{
}
