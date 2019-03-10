#pragma once

#define GLFW_INCLUDE_VULKAN // GLFW will automatically include vulkan.h
#include <GLFW/glfw3.h>

#include <vector>
#include <optional>

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete()
	{
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
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

	void createSurface();
	VkSurfaceKHR surface;

	void createVulkanInstance();
	VkInstance_T* vulkanInstance;
	VkDebugUtilsMessengerEXT debugMessenger;
	
	void setupDebugMessenger();

	bool checkValidationLayerSupport();
	const std::vector<const char*> validationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};
	
	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
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
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	void createSwapChain();

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	VkPhysicalDevice physicalDevice;

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	void createLogicalDevice();
	VkDevice logicalDevice;

	VkQueue graphicsQueue;
	VkQueue presentQueue;
};
