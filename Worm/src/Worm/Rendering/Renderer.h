#pragma once

#include<stack>

#include "Worm/Core/Core.h"
#include "Worm/Core/Window.h"

#include "Worm/Rendering/RenderingPrimitives.h"

#include "Worm/Rendering/Camera.h"

#include "Worm/Rendering/VertexArray.h"
#include "Worm/Rendering/RenderingBatch.h"

#include "Worm/Rendering/Shader.h"

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

	class Renderer {
	public:
		static void BeginScene(Environment env, Camera* camera, Shader* shader);
		static void EndScene();
		
		static void Submit(RenderingBatchElement element);

		static void SetActiveRenderingFrame(RenderingFrame frame, bool clearBatch = true);
		static RenderingFrame& GetActiveRenderingFrame();

		static void INIT();
	private:
		static void FlushScene(bool clearBatch = true);
	private:
		static RenderingFrame s_ActiveFrame;
		static RenderingBatch s_Batch;

		static Camera* s_ActiveCamera;
		static Shader* s_ActiveShader;
		
		static constexpr const char* s_CameraMatrixUniformName = "u_CameraMatrix";
	};
}