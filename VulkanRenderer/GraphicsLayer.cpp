#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GraphicsLayer.h"
#include <filesystem>

using namespace glm;


GraphicsLayer::GraphicsLayer()
{
	init();
}

bool GraphicsLayer::init()
{
	glewExperimental = true;

	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW!" << std::endl;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1920, 1080, "Tutorial 01", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
	defaultShader = new Shader();
	defaultShader->load("shaders/gl/simpleVertex.vert", "shaders/gl/simpleFrag.frag");

	Mesh* m = new Mesh();
	m->load("tree.fbx");
	meshList.push_back(m);

	for (int i = 0; i < 100; i++)
	{
		float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 5000.0f - 2500.0f;
		float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 5000.0f - 2500.0f;
		float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 5000.0f - 2500.0f;

		SceneObj obj;
		obj.mesh = m;
		obj.model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
		sceneList.push_back(obj);
	}

	
	

}

bool GraphicsLayer::render()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1920.0f / (float)1080.0f, 0.1f, 10000.0f);

	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	glm::vec3 camPos = glm::vec3(0, 0, 4000);
	// Camera matrix
	glm::mat4 view = glm::lookAt(
		camPos,
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 model = glm::mat4(1.0f);


	defaultShader->use();
	
	defaultShader->setMat4("view", view);
	defaultShader->setMat4("projection", projection);
	
	float time = glfwGetTime();
	defaultShader->setVec3("lightPos", glm::vec3(sin(time) * 1500.0f, cos(time) * 1500.0f, sin(time) * 1500.0f));
	defaultShader->setVec3("lightColor", glm::vec3(0.5f, 0.5f, 0.9f));
	defaultShader->setVec3("camPos", camPos);
	defaultShader->setFloat("ambientStrength", 0.00f);

	for (auto& obj : sceneList)
	{
		defaultShader->setMat4("model", obj.model);
		obj.mesh->draw();
	}
		

	// Swap buffers
	glfwSwapBuffers(window);

	return true;
}



GLFWwindow* GraphicsLayer::getWindow()
{
	return window;
}