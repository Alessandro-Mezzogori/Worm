#pragma once

#include<stack>

#include "Worm/Core/Core.h"
#include "Worm/Core/Window.h"

#include "Worm/Rendering/RenderingPrimitives.h"

#include "Worm/Rendering/VertexArray.h"

namespace Worm {
	struct RenderingFrame {
		RenderingViewport renderingViewport;
		
		RenderingFrame(RenderingViewport viewport = RenderingViewport()) :
			renderingViewport(viewport)
		{
		}
	};

	struct Environment {

	};

	struct Camera {

	};

	class Renderer {
	public:
		static void BeginScene(Environment env, Camera camera); 
		static void EndScene();
		static void FlushScene();

		static void Submit(const VertexArray& vertexArray);

		static void SetActiveRenderingFrame(RenderingFrame frame);
		static RenderingFrame& GetActiveRenderingFrame();
		static void INIT();

	private:
		static RenderingFrame s_ActiveFrame;
	};
}