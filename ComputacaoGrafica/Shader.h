#include "GL/glew.h"
#include "iostream"
#include "fstream"
#include "string"

class Shader
{
public:	
	Shader();
	~Shader();
	void CreateFromString(const char* vertexCode, const char* fragmetCode);
	void CreateFromFile(const char* vertexLocation, const char* fragmentLocation);
	void UseProgram();
	GLuint GetUniformModel() { return uniformModel; };
	GLuint GetUniformProjection() { return uniformProjection; };

private:
	GLuint ShaderId;
	GLuint uniformModel, uniformProjection;
	void Compile(const char* vertexCode, const char* fragmetCode);
	std::string ReadFile(const char* fileLocation);

};