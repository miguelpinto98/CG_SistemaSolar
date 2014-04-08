#pragma once
class Ponto {
	double x;
	double y;
	double z;
public:
	Ponto(double,double,double);
	double getX() { return x; }
	double getY() { return y; }
	double getZ() { return z; }
	virtual ~Ponto(void);
};

