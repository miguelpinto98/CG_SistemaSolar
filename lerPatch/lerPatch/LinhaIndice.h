#pragma once
#include <vector>
#include <iostream>

using namespace std;

class LinhaIndice {
	int i;
public:
	LinhaIndice(int);
	vector<int> indices;
	int getI() { return i; }
	void adicionaIndice(int i);
	virtual ~LinhaIndice(void);
};