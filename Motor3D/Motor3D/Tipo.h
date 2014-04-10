#pragma once

class Tipo {
	double x;
	double y;
	double z;
	double ang;
public:
	Tipo();
	Tipo(double, double, double);
	Tipo(double, double, double, double);
	bool tipoVazio();
	~Tipo(void);
};

