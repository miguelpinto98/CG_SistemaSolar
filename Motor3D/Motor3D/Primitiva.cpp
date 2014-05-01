#include "Primitiva.h"

Primitiva::Primitiva(string n) {
	nome = n;
	nvertices = 0;
}

void Primitiva::adicionaPonto(Ponto p) {
	pontos.push_back(p);
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
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, nvertices);
}

void Primitiva::preparar() {
	int tpontos = pontos.size(), lados = tpontos/3, j;
	buffer = buffer = (GLuint*)malloc(sizeof(GLuint)*tpontos*3);

	nvertices = tpontos * 3;
	glEnableClientState(GL_VERTEX_ARRAY);

	float *vertexB = (float *)malloc(sizeof(float)* nvertices);

	j = 0;
	for (int i = 0; i<tpontos; i++) {
		Ponto xyz = pontos.at(i);

		vertexB[j + 0] = xyz.getX();
		vertexB[j + 1] = xyz.getY();
		vertexB[j + 2] = xyz.getZ();

		j += 3;
	}
	nvertices = j;

	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, nvertices*sizeof(float), vertexB, GL_STATIC_DRAW);

	free(vertexB);
}

Primitiva::~Primitiva(void)
{
}
