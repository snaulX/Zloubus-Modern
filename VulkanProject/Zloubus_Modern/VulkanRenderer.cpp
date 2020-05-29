#include "VulkanRenderer.h"

void VulkanRenderer::configureExtensionsAndLayers(vector<const char*> instanceExtensions,
	vector<const char*> deviceExtensions, vector<const char*> validationLayers)
{
	this->instanceExtensionsRequired_ = instanceExtensions;
	this->deviceExtensionsRequired_ = deviceExtensions;
	this->validationLayersRequired_ = validationLayers;

	unsigned int instanceExtensionCount;
	vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionCount, nullptr);
	if (instanceExtensionCount > 0)
	{
		this->instanceExtensionsAvailable_.resize(instanceExtensionCount);

		vkEnumerateInstanceExtensionProperties(nullptr,
			&instanceExtensionCount, this->instanceExtensionsAvailable_.data());
	}

	unsigned int layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	if (layerCount > 0)
	{
		this->instanceExtensionsAvailable_.resize(instanceExtensionCount);
		vkEnumerateInstanceLayerProperties(&layerCount, this->validationLayersAvailable_.data());
	}

	bool allInstancesExtensionsAvialable = true;
	if (instanceExtensionsRequired_.size() > 0)
	{
		unsigned int instanceExtAvialableAndRequiredQnt;
		for (const char* extName : instanceExtensionsRequired_)
		{
			for (const VkExtensionProperties &extProps : this->deviceExtensionsAvailable_)
			{
				if (strcmp(extName, extProps.extensionName))
				{
					instanceExtAvialableAndRequiredQnt++;
				}
			}
		}
		allInstancesExtensionsAvialable = (instanceExtAvialableAndRequiredQnt == this->instanceExtensionsRequired_.size());

		bool allValidationLayersAvialable = true;
		if (validationLayersRequired_.size() > 0)
		{
			unsigned int validationLayersAvialableAndRequiredQnt;
			for (const char* layerName : validationLayersRequired_)
			{
				for (const VkLayerProperties& layProps : this->validationLayersAvailable_)
				{
					if (strcmp(layerName, layProps.layerName))
					{
						validationLayersAvialableAndRequiredQnt++;
					}
				}
			}
			allInstancesExtensionsAvialable = (validationLayersAvialableAndRequiredQnt == this->validationLayersRequired_.size());
		}

		bool validationExtensionsIsAvialable = false;
		for (const VkExtensionProperties& ext : this->instanceExtensionsAvailable_)
		{
			if (strcmp(VK_EXT_DEBUG_MARKER_EXTENSION_NAME, ext.extensionName))
			{
				validationExtensionsIsAvialable = true;
				break;
			}
		}

		if (DEBUG_MODE && allValidationLayersAvialable && validationExtensionsIsAvialable && validationLayersRequired_.size() > 0)
		{
			this->instanceExtensionsRequired_.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
			this->validationEnabled_ = true;
			cout << "Vulkan debug layer enabled" << endl;
		}
		else if (!allValidationLayersAvialable)
		{
			cout << "Vulkan debug layer unavialable" << endl;
		}
		else
		{
			cout << "Vulkan debug layer not used" << endl;
		}
	}
}
