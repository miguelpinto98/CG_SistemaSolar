#pragma once
class Rotacao
{
	float time;
	float rx;
	float ry;
	float rz;
public:
	Rotacao();
	Rotacao(float,float,float,float);
	float getRx() { return rx; }
	float getRy() { return ry; }
	float getRz() { return rz; }
	float getTime() { return time; }
	bool vazio();
	virtual ~Rotacao();
};

