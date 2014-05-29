#include "Primitiva.h"

Primitiva::Primitiva(string n) {
	nome = n;
	nvertices = 0;
	tipo = 'f';
}

void Primitiva::adicionaPonto(Ponto p) {
	pontos.push_back(p);
}

void Primitiva::adicionaNormal(Ponto p) {
	normais.push_back(p);
}

void Primitiva::adicionaFilho(Primitiva p) {
	filhos.push_back(p);
}

int Primitiva::numeroFilhos() {
	return filhos.size();
}

void Primitiva::construir() {
	int numpontos = pontos.size();

	glBegin(GL_TRIANGLES);
	for (int j = 0; j< numpontos; j++) {
		glVertex3f(pontos.at(j).getX(), pontos.at(j).getY(), pontos.at(j).getZ());
	}
	glEnd();
}

void Primitiva::desenhar() {
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glNormalPointer(GL_FLOAT, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, nvertices);
}

void Primitiva::preparar() {
	int tpontos = pontos.size(), lados = tpontos/3, j;
	//buffers = (GLuint*)malloc(sizeof(GLuint)*tpontos*3*2);

	nvertices = tpontos * 3;
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	float *vertexB = (float *)malloc(sizeof(float)* nvertices);
	float *normalB = (float *)malloc(sizeof(float)* nvertices);

	j = 0;
	for (int i = 0; i<tpontos; i++) {
		Ponto xyz = pontos.at(i);
		Ponto pn = normais.at(i);

		vertexB[j + 0] = xyz.getX();	normalB[j + 0] = pn.getX();
		vertexB[j + 1] = xyz.getY();	normalB[j + 1] = pn.getY();
		vertexB[j + 2] = xyz.getZ();	normalB[j + 2] = pn.getZ();

		j += 3;
	}
	nvertices = j;

	glGenBuffers(2, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, nvertices*sizeof(float), vertexB, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, nvertices*sizeof(float), normalB, GL_STATIC_DRAW);

	free(vertexB);
	free(normalB);
}

Primitiva::~Primitiva(void)
{
}
