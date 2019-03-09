#pragma once

#define GLFW_INCLUDE_VULKAN // GLFW will automatically include vulkan.h
#include <GLFW/glfw3.h>

#include <vector>
#include <optional>

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;

	bool isComplete()
	{
		return graphicsFamily.has_value();
	}
};

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
	VkDebugUtilsMessengerEXT debugMessenger;
	
	void setupDebugMessenger();

	bool checkValidationLayerSupport();
	const std::vector<const char*> validationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};
	
	std::vector<const char*> getRequiredExtensions();

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData
	);
#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

	void pickPhysicalDevice();
	bool isDeviceSuitable(VkPhysicalDevice device);
	VkPhysicalDevice physicalDevice;

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	void createLogicalDevice();
	VkDevice logicalDevice;

	VkQueue graphicsQueue;
};
