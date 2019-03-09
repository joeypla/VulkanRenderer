#pragma once

#include <vector>

struct GLFWwindow;
struct VkInstance_T;

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

	void createVulkanInstance();
	VkInstance_T* vulkanInstance;

	bool checkValidationLayerSupport();
	const std::vector<const char*> validationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif
};