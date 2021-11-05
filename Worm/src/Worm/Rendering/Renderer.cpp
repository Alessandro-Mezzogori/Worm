#include "wormpch.h"
#include "Renderer.h"

#include "RenderCommand.h"

namespace Worm {
	RenderingFrame Renderer::s_ActiveFrame = RenderingFrame();

	// ##### SCENE CONTROLS FUNTIONS #####

	void Renderer::BeginScene(Environment env, Camera camera)
	{
		
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::FlushScene()
	{
	}

	// ##### RENDERING OBJECTS FUNCTIONS ######

	void Renderer::Submit(const VertexArray& vertexArray) {
		RenderCommand::RenderIndexed(vertexArray);
	}

	// ##### ENVIRONMENT FUNCTIONS ######

	void Renderer::SetActiveRenderingFrame(RenderingFrame frame) {
		s_ActiveFrame = frame;

		RenderingViewport vp = s_ActiveFrame.renderingViewport;
		RenderCommand::SetViewport(vp.x, vp.y, vp.width, vp.height);
	}

	RenderingFrame& Renderer::GetActiveRenderingFrame() {
		return s_ActiveFrame;
	}

	void Renderer::INIT() {
		RenderingAPIController::INIT();
		RenderCommand::INIT();

		s_ActiveFrame = RenderingFrame();
	}
}