#include "wormpch.h"
#include "VulkanRenderingAPI.h"

#include <vulkan/vulkan.h>

namespace Worm{

	void VulkanRenderingAPI::Init()
	{
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS) {
			WORM_LOG_CORE_CRITICAL("Failed to create Vulkan Instance");
		}
	}

	VulkanRenderingAPI::~VulkanRenderingAPI() {
		WORM_LOG_CORE_TRACE("Destroying Vulkan instance");
		vkDestroyInstance(m_Instance, nullptr);
	}

	void VulkanRenderingAPI::RenderIndexed(const VertexArray& vertexArray) const
	{
	}

	void VulkanRenderingAPI::ClearColor(const glm::vec4& color) const
	{
	}

	void VulkanRenderingAPI::ClearFrame() const
	{
	}

	void VulkanRenderingAPI::SetViewportAndScissors(float x, float y, float width, float height)
	{
	}

	void VulkanRenderingAPI::EnableScissors(bool value)
	{
	}

	void VulkanRenderingAPI::EnableDepthTest(bool value)
	{
	}

	const RenderingAPIInformation& VulkanRenderingAPI::GetInformation()
	{
		return RenderingAPIInformation();
	}

}