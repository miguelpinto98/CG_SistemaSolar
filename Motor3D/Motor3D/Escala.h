#pragma once

class Escala {
	float ex;
	float ey;
	float ez;
public:
	Escala();
	Escala(float, float, float);
	float getEx() { return ex; }
	float getEy() { return ey; }
	float getEz() { return ez; }
	bool vazio();
	~Escala(void);
};

