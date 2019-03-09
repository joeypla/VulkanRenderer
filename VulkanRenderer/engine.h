#pragma once

class GLFWwindow;

class Engine
{
public:
	static const int WIDTH = 800;
	static const int HEIGHT = 600;

	void run();
private:
	void initWindow();
	void initVulkan();
	void mainLoop();
	void cleanup();
	
	GLFWwindow* window;
};