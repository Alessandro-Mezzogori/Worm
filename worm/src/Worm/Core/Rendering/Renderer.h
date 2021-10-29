#pragma once

#include<vector>

#include "Worm/Core/Core.h"
#include "Worm/Core/Window.h"

#include "Worm/Core/Rendering/RenderingAPIController.h"
#include "Worm/Core/Rendering/Utilities.h"

namespace Worm {
	struct RenderingFrame {
		Utils::RenderingViewport renderingViewport;
		Shared<RenderingAPI> renderingApi;	

		RenderingFrame(RenderingAPIController::API api, Utils::RenderingViewport viewport = Utils::RenderingViewport()) :
			renderingApi(RenderingAPIController::LoadAPI(api)), renderingViewport(viewport)
		{
		}

		RenderingFrame()
		{
			renderingApi = nullptr;
			renderingViewport = Utils::RenderingViewport();
		}
	};


	class Renderer {
	public:
		static void RenderVertexArray(const VertexArray& vertexArray);

		static void ClearColor(const glm::vec4& color);
		static void ClearFrame();

		static void UseRenderingFrame(RenderingFrame frame);
		static void INIT();
	private:
		static RenderingFrame s_ActiveFrame;
	};
}