#include "wormpch.h"
#include "Renderer.h"

#include "RenderCommand.h"

namespace Worm {
	// ##### STATIC DECLARATION / INIT #####

	RenderingFrame Renderer::s_ActiveFrame;
	RenderingBatch Renderer::s_Batch;

	// ##### SCENE CONTROLS FUNTIONS #####

	void Renderer::BeginScene(Environment env, Camera camera)
	{
		s_Batch.Clear();
	}

	void Renderer::EndScene()
	{
		if (s_Batch.GetUsedSize() != 0) RenderCommand::RenderIndexed(s_Batch.GetVertexArray());
	}

	void Renderer::FlushScene()
	{
		
	}

	// ##### RENDERING OBJECTS FUNCTIONS ######

	void Renderer::Submit(RenderingBatchElement element) {
		if (!s_Batch.HasSpace(element)) {
			RenderCommand::RenderIndexed(s_Batch.GetVertexArray());
			s_Batch.Clear();
		};
		s_Batch.AddData(element);
	}

	// ##### ENVIRONMENT FUNCTIONS ######

	void Renderer::SetActiveRenderingFrame(RenderingFrame frame) {
		if (s_Batch.GetUsedSize() != 0) {
			RenderCommand::RenderIndexed(s_Batch.GetVertexArray());
			s_Batch.Clear();
		};

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

		s_Batch = RenderingBatch();
		s_Batch.INIT();
	}
}