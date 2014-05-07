#pragma once
class Translacao
{
public:
	int time;
	Translacao();
	Translacao(int);
	int getTime() { return time; }
	void setTime(int);
	bool vazio();
	virtual ~Translacao();
};

