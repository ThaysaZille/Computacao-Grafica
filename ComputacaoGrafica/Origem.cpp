#include <iostream>
#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Mesh.h"
#include "Shader.h"


std::vector<Mesh*> listMesh;
std::vector<Shader*> listShader;


//Vertex Shader
static const char* VertexLocation = "VertexShader.glsl";

static const char* FragmentLocation = "FragmentShader.glsl";


void CriaTriangulos() {
	GLfloat vertices[] = {
		//x , y	, z	
		0.0f, 1.0f, 0.0f,   //Vertice 0 (Verde)
		-1.0f, -1.0f, 0.0f, //Vertice 1 (Preto)
		1.0f, -1.0f, 0.0f,  //Vertice 2 (Vermelho)
		0.0f, -1.0f, 1.0f    //Vertice 3 (Azul)
	};

	GLfloat vertices2[] = {
		//x , y	, z	
		0.0f, 1.0f, 0.0f,   //Vertice 0 (Verde)
		-1.0f, -1.0f, 0.0f, //Vertice 1 (Preto)
		1.0f, -1.0f, 0.0f,  //Vertice 2 (Vermelho)
		0.0f, -1.0f, -1.0f    //Vertice 3 (Azul)
	};

	GLuint indice[] = {
		0, 1, 3,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	//CreateMesh
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, sizeof(vertices), indice, sizeof(indice));
	listMesh.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices2, sizeof(vertices2), indice, sizeof(indice));
	listMesh.push_back(obj2);
}

void CriaShader() {
	Shader* shader = new Shader();
	shader->CreateFromFile(VertexLocation, FragmentLocation);
	listShader.push_back(shader);
}

int main() {
	if (!glfwInit()) {
		printf("GLFW: Não pode ser iniciado");
		return 1;
	}

	GLFWwindow* mainWindow = glfwCreateWindow(800, 600, "Ola Mundo!", NULL, NULL);
	if (!mainWindow) {
		printf("GLFW: Não foi possível criar a janela");
		glfwTerminate();
		return 1;
	}

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(mainWindow);

	if (glewInit() != GLEW_OK) {
		printf("Glew: Não pode ser iniciado!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, bufferWidth, bufferHeight);

	CriaTriangulos();
	CriaShader();

	float triangleOffsetX = 0.0f, maxOffsetX = 0.7f, minOffsetX = -0.7f, incOffsetX = 0.05f;
	bool directionX = true;
		
	float triangleOffsetX1 = 0.0f, maxOffsetX1 = 0.5f, minOffsetX1 = -0.7f, incOffsetX1 = 0.01f;
	bool directionX1 = true;

	float triangleOffsetY = 0.0f, maxOffsetY = 0.7f, minOffsetY = -0.7f, incOffsetY = 0.05f;
	bool directionY = true;

	float triangleOffsetY1 = 0.0f, maxOffsetY1 = 0.3f, minOffsetY1 = -0.7f, incOffsetY1 = 0.001f;
	bool directionY1 = true;

	float rotationOffset = 0.0f, maxRotation = 360.0f, minRotation = -0.1f, incRotation = 0.5f;
	bool rotation = true;

	float scaleOffset = 0.4f, maxScale = 0.4f, minScale = 0.0f, incScale = 0.005f;
	bool scale = true;

	while (!glfwWindowShouldClose(mainWindow)) {

		//Habilitar os eventos de usuario
		glfwPollEvents();

		glClearColor(1.0f, 0.75f, 0.79f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Desenha o triangulo
		Shader* shader = listShader[0];
		shader->UseProgram();

		triangleOffsetX += directionX ? incOffsetX : incOffsetX * -1;
		if (triangleOffsetX >= maxOffsetX || triangleOffsetX <= minOffsetX)
			directionX = !directionX;

		triangleOffsetX1 += directionX1 ? incOffsetX1 : incOffsetX1 * -1;
		if (triangleOffsetX1 >= maxOffsetX1 || triangleOffsetX1 <= minOffsetX1)
			directionX1 = !directionX1;

		triangleOffsetY += directionY ? incOffsetY : incOffsetY * -1;
		if (triangleOffsetY >= maxOffsetY || triangleOffsetY <= minOffsetY)
			directionY = !directionY;

		triangleOffsetY1 += directionY1 ? incOffsetY1 : incOffsetY1 * -1;
		if (triangleOffsetY1 >= maxOffsetY1 || triangleOffsetY1 <= minOffsetY1)
			directionY1 = !directionY1;

		rotationOffset += rotation ? incRotation : incRotation * -1;
		if (rotationOffset >= maxRotation || rotationOffset <= minRotation)
			rotation = !rotation;

		scaleOffset += scale ? incScale : incScale * -1;
		if (scaleOffset >= maxScale || scaleOffset <= minScale)
			scale = !scale;

		
		/*
		* Triangulo 1
		*/
		listMesh[0]->RenderMesh();
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -2.0f));
		model = glm::rotate(model, glm::radians(rotationOffset), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4, 0.4, 0.4));

		
		glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model));

		/*
		* Triangulo 2
		*/
		listMesh[1]->RenderMesh();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
		model = glm::rotate(model, glm::radians(rotationOffset), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4, 0.4, 0.4));

		
		glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model));

		//Projeção perspectiva 3D
		
		glm::mat4 projection = glm::perspective(1.0f, (GLfloat)bufferWidth / (GLfloat)bufferHeight, 0.1f, 100.0f);
		glUniformMatrix4fv(shader->GetUniformProjection(), 1, GL_FALSE, glm::value_ptr(projection));

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}

	glfwDestroyWindow(mainWindow);
	glfwTerminate();
	return 0;
}