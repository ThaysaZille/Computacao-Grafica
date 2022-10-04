#include "GL/glew.h"

class Mesh
{
public:
	Mesh();
	~Mesh();
	void CreateMesh(GLfloat *vertice, unsigned int numOfVertice, GLuint *indice, unsigned int numOfIndice);
	void RenderMesh();
private:
	GLuint VAO, VBO, VBI;
	GLuint numOfIndice;
};

