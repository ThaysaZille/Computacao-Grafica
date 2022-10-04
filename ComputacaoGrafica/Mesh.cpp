#include "Mesh.h"

Mesh::Mesh() {
	VAO = 0;
	VBO = 0;
	VBI = 0;
}

Mesh::~Mesh() {
	if (VBO != 0) glDeleteBuffers(1, &VBO);
	if (VBI != 0) glDeleteBuffers(1, &VBI);
	if (VAO != 0) glDeleteBuffers(1, &VAO);
}

void Mesh::CreateMesh(GLfloat *vertice, unsigned int numOfVertice, GLuint *indice, unsigned int numOfIndice) {
	Mesh::numOfIndice = numOfIndice;

	glGenVertexArrays(1, &VAO); //Cria o VAO
	glBindVertexArray(VAO); //Coloca o VAO em contexto

		glGenBuffers(1, &VBI); //Cria o VBI
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBI);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfIndice, indice, GL_STATIC_DRAW);

			glGenBuffers(1, &VBO); //Cria o VBO
			glBindBuffer(GL_ARRAY_BUFFER, VBO); //Coloca o VBO em contexto

				glBufferData(GL_ARRAY_BUFFER, numOfVertice, vertice, GL_STATIC_DRAW); //Explica o valor do Array
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //Explica os valores de x e y
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0); //remover do contexto o VBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //remover do contexto o VBI
	glBindVertexArray(0); //remover do contexto o VAO
}

void Mesh::RenderMesh() {
	glBindVertexArray(VAO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBI);
			glDrawElements(GL_TRIANGLES, numOfIndice, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}