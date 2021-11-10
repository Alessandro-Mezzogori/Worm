#pragma once

#include<glm/glm.hpp>

#include "VertexArray.h"

namespace Worm {
	struct RenderingAPIInformation {
		int32_t MaxFragmentTextureSlots;
	};
	/*
	 * Interface for the implementation of rendering api's like Vulkan, Opengl, Metal, DirectX
	 */
	class RenderingAPI {
	public:
		enum class API {
			NONE,
			DEFAULT,
			OPENGL,
			VULKAN,
		};
	public:
		virtual void Init() = 0;
		virtual void RenderIndexed(const VertexArray& vertexArray) const= 0;
		
		virtual void ClearColor(const glm::vec4& color) const = 0;
		virtual void ClearFrame() const = 0;

		virtual void SetViewportAndScissors(float x, float y, float width, float height) = 0;
		virtual void EnableScissors(bool value) = 0;
		virtual void EnableDepthTest(bool value) = 0;

		virtual const RenderingAPIInformation& GetInformation() const = 0;
	};
}