#pragma once

#define VK_USE_PLATFORM_WIN32_KHR

#include <iostream>
#include <vector>
#include <Windows.h>
#include <vulkan/vulkan.h>

#ifdef NDEBUG
const bool DEBUG_MODE = true;
#else
const bool DEBUG_MODE = false;
#endif // NDEBUG

using namespace std;

class VulkanRenderer
{
private:
	VkInstance instance_;

	vector<const char*> instanceExtensionsRequired_;
	vector<VkExtensionProperties> instanceExtensionsAvailable_;

	vector<const char*> deviceExtensionsRequired_;
	vector<VkExtensionProperties> deviceExtensionsAvailable_;

	vector<const char*> validationLayersRequired_;
	vector<VkLayerProperties> validationLayersAvailable_;
	VkDebugReportCallbackEXT validationReportCallback_;
	bool validationEnabled_;

public:
	void configureExtensionsAndLayers(
		vector<const char*> instanceExtensions,
		vector<const char*> deviceExtensions,
		vector<const char*> validationLayers);
	VulkanRenderer();
	~VulkanRenderer();
};

