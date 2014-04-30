#pragma once
#include <vector>
#include <iostream>

using namespace std;

class LinhaIndice {

public:
	vector<int> indice;
	vector<int> getLinha() { return indice; }
	void adicionaIndice(int i);
	virtual ~LinhaIndice(void);
};