#include "Shader.h"

Shader::Shader() {
	ShaderId = 0;
	uniformModel = 0;
	uniformProjection = 0;
}

Shader::~Shader() {
	if (!ShaderId == 0) {
		glDeleteProgram(ShaderId);
	}
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmetCode) {
	Compile(vertexCode, fragmetCode);
}

void Shader::Compile(const char* vertexCode, const char* fragmetCode) {
	ShaderId = glCreateProgram(); //Cria um programa
	GLuint _vShader = glCreateShader(GL_VERTEX_SHADER); //Cria um shader
	GLuint _fShader = glCreateShader(GL_FRAGMENT_SHADER); //Cria um shader

	//Gambiarra para converter Char em GLChar
	const GLchar* vCode[1];
	const GLchar* fCode[1];
	vCode[0] = vertexCode; //Código do vShader
	fCode[0] = fragmetCode; //Código do fShader

	glShaderSource(_vShader, 1, vCode, NULL); //associa o shader ao código
	glCompileShader(_vShader); //Compila o shader
	glAttachShader(ShaderId, _vShader); //Adiciona o shader ao programa


	glShaderSource(_fShader, 1, fCode, NULL); //associa o shader ao código
	glCompileShader(_fShader); //Compila o shader
	glAttachShader(ShaderId, _fShader); //Adiciona o shader ao programa

	glLinkProgram(ShaderId); //Adiciona o programa

	uniformModel = glGetUniformLocation(ShaderId, "model");
	uniformProjection = glGetUniformLocation(ShaderId, "projection");
}

void Shader::UseProgram() {
	glUseProgram(ShaderId);
}

void Shader::CreateFromFile(const char* vertexLocation, const char* fragmentLocation) {
	std::string vertexCode = ReadFile(vertexLocation);
	std::string fragmentCode = ReadFile(fragmentLocation);

	Compile(vertexCode.c_str(), fragmentCode.c_str());
}

std::string Shader::ReadFile(const char* fileLocation) {
	std::string content = "";
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		printf("O arquivo não foi encontrado (%s)", fileLocation);
	}

	std::string line;
	while (!fileStream.eof()){
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();

	return content;
}