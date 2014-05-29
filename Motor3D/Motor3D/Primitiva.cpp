#include "Primitiva.h"

Primitiva::Primitiva(string n) {
	nome = n;
	nvertices = 0;
	tipo = 'f';
	cmdHor = 0;
	cmdVer = 0;
	numsInd = 0;
	
}

void Primitiva::adicionaPonto(Ponto p) {
	pontos.push_back(p);
}

void Primitiva::adicionaNormal(Ponto p) {
	normais.push_back(p);
}

void Primitiva::adicionaTextura(Ponto p) {
	texturas.push_back(p);
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
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);
	
	glDrawElements(GL_TRIANGLES, numsInd, GL_UNSIGNED_INT, indices);
}

void Primitiva::preparar() {
	int j, jj, x;
	int tpontos = pontos.size(), textNum;
	Ponto p = Ponto();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	nvertices = tpontos * 3;
	textNum = normais.size() * 2;

	float *vertexB = (float *)malloc(sizeof(float)* nvertices);
	float *normalB = (float *)malloc(sizeof(float)* nvertices);
	float *textureB = (float *)malloc(sizeof(float)* textNum); 

	numsInd = 6 * cmdHor*cmdVer;
	indices = (int*)malloc(numsInd*sizeof(int));

	/* Coordenadas Normais e Textura */
	j = 0;
	jj = 0;
	for (int i = 0; i<tpontos; i++) {
		p = pontos.at(i);
		vertexB[j + 0] = p.getX();
		vertexB[j + 1] = p.getY();
		vertexB[j + 2] = p.getZ();

		p = normais.at(i);
		normalB[j + 0] = p.getX();
		normalB[j + 1] = p.getY();
		normalB[j + 2] = p.getZ();

		p = texturas.at(i);
		textureB[jj + 0] = p.getX();
		textureB[jj + 1] = p.getY();

		j += 3;
		jj += 2;
	}
	int numVN = j;
	int numT = jj;
	nvertices = numVN;

	x = 0;
	for (int i = 0; i < cmdVer; i++) {
		for (int j = 0; j < cmdHor; j++) {
			int p1, p2, p3, p4;
			p1 = (cmdHor + 1)*(i)+j;
			p2 = (cmdHor + 1)*(i)+j + 1;
			p3 = (cmdHor + 1)*(i + 1) + j;
			p4 = (cmdHor + 1)*(i + 1) + j + 1;

			indices[x+0] = p1;
			indices[x+1] = p3;
			indices[x+2] = p2;

			indices[x+3] = p4;
			indices[x+4] = p2;
			indices[x+5] = p3;

			x += 6;
		}
	}

	glGenBuffers(3, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, numVN*sizeof(float), vertexB, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, numVN*sizeof(float), normalB, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, numT*sizeof(float), textureB, GL_STATIC_DRAW);

	free(vertexB);
	free(normalB);
	free(textureB);
}

void Primitiva::desenhaComImagem() {
	glBindTexture(GL_TEXTURE_2D, texID);
	desenhar();
	cout << texID << endl;
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Primitiva::carregaImagem(string file) {
	string path = "imagens/" + file;

	ilGenImages(1, &ima);
	ilBindImage(ima);
	ilLoadImage((ILstring)path.c_str());
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int height = ilGetInteger(IL_IMAGE_HEIGHT);
	imageData = ilGetData();

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
}

Primitiva::~Primitiva(void)
{
}
