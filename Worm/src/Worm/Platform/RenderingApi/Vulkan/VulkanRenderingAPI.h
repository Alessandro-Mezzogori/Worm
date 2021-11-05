#pragma once

#include "Worm/Rendering/RenderingAPI.h"

#include <vulkan/vulkan.h>

namespace Worm{
	class VulkanRenderingAPI : public RenderingAPI {
	public:
		~VulkanRenderingAPI();

		virtual void Init() override;
		virtual void RenderIndexed(const VertexArray& vertexArray) const override;
		virtual void ClearColor(const glm::vec4& color) const override;
		virtual void ClearFrame() const override;
		virtual void SetViewportAndScissors(float x, float y, float width, float height) const override;
		virtual void EnableScissors(bool value) const override;
	private:
		VkInstance m_Instance;
	};
}