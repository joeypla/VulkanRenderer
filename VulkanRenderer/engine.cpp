#include "engine.h"

#define GLFW_INCLUDE_VULKAN // GLFW will automatically include vulkan.h
#include <GLFW/glfw3.h>

void Engine::run()
{
	initWindow();
	initVulkan();
	mainLoop();
	cleanup();
}

void Engine::initWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(800, 600, "Vulkan Renderer", nullptr, nullptr);

}

void Engine::initVulkan()
{

}

void Engine::mainLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
}

void Engine::cleanup()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}