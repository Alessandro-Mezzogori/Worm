#pragma once

#include<glm/glm.hpp>

#include "VertexArray.h"

namespace Worm {
	/*
	 * Interface for the implementation of rendering api's like Vulkan, Opengl, Metal, DirectX
	 */
	class RenderingAPI {
	public:
		enum class API {
			DEFAULT,
			OPENGL,
			VULKAN,
		};
	public:
		virtual void Init() = 0;
		virtual void RenderIndexed(const VertexArray& vertexArray) const= 0;
		
		virtual void ClearColor(const glm::vec4& color) const = 0;
		virtual void ClearFrame() const = 0;

		virtual void SetViewportAndScissors(float x, float y, float width, float height) const = 0;
		virtual void EnableScissors(bool value) const = 0;
	};
}