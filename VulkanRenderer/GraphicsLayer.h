#pragma once


#include <string>
#include "Mesh.h"
#include "Graphics.h"
#include "Shader.h"

struct SceneObj
{
	glm::mat4 model;
	Mesh* mesh;
};

class GraphicsLayer
{
public:


	GraphicsLayer();

	bool init();

	bool render();

	/* returns the window created by GLFW. */
	GLFWwindow* getWindow();

	glm::vec3 cameraLocation;
private:
	GLFWwindow* window;

	std::vector<Mesh*> meshList;

	std::vector<SceneObj> sceneList;

	Shader* defaultShader;

	GLuint VertexArrayID;
};