#pragma once

class Tipo {
	float x;
	float y;
	float z;
	float ang;
public:
	Tipo();
	Tipo(float, float, float);
	Tipo(float, float, float, float);
	float getTX() { return x; }
	float getTY() { return y; }
	float getTZ() { return z; }
	float getTAng() { return ang; }
	bool tipoVazio();
	~Tipo(void);
};

