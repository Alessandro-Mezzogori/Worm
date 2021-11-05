#pragma once

#include "Worm/Core/Core.h"
#include "Worm/Core/Window.h"

#include "Worm/Rendering/RenderingAPIController.h"
#include "Worm/Rendering/Utilities.h"

namespace Worm {
	class RenderCommand {
	public:
		static void RenderIndexed(const VertexArray& vertexArray) { 
			s_RenderingAPI->RenderIndexed(vertexArray);  
		}

		static void ClearColor(const glm::vec4& color) { 
			s_RenderingAPI->ClearColor(color);
		};

		static void ClearFrame() { 
			s_RenderingAPI->ClearFrame();
		};

		static void SetViewport(float x, float y, float width, float height) { 
			s_RenderingAPI->SetViewportAndScissors(x, y, width, height); 
		};

	public:
		static void INIT();
	private:
		static const RenderingAPI* s_RenderingAPI;
	};
}