#pragma once
#include "Tipo.h"

class Estado {
	Tipo translacao;
	Tipo rotacao;
	Tipo escala;
public:
	Estado();
	Estado(Tipo, Tipo, Tipo);
	bool estadoVazio();
	~Estado(void);
};

