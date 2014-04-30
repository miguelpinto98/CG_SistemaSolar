#pragma once
#include <vector>
#include <iostream>
#include "LinhaIndice.h"

using namespace std;

class Indices {

public:
	vector<LinhaIndice> indices;
	vector<LinhaIndice> getIndices() { return indices; }
	void adicionaLinhaInd(LinhaIndice i);
	virtual ~Indices(void);
};