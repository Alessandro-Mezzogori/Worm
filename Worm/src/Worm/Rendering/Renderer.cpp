#include "wormpch.h"
#include "Renderer.h"

#include "RenderCommand.h"

namespace Worm {
	// ##### STATIC DECLARATION / INIT #####

	RenderingFrame Renderer::s_ActiveFrame;
	RenderingBatch Renderer::s_Batch;
	Camera* Renderer::s_ActiveCamera = nullptr;
	Shader* Renderer::s_ActiveShader = nullptr;

	// ##### SCENE CONTROLS FUNTIONS #####

	void Renderer::BeginScene(Environment env, Camera* camera, Shader* shader)
	{
		s_Batch.Begin();
		s_ActiveCamera = camera;
		s_ActiveShader = shader;
	}

	void Renderer::EndScene()
	{
		FlushScene();
		s_ActiveShader = nullptr;
		s_ActiveCamera = nullptr;
	}

	void Renderer::FlushScene(bool clearBatch)
	{
		s_ActiveShader->Activate();
		s_ActiveShader->LoadMat4(s_CameraMatrixUniformName, s_ActiveCamera->GetCamMatrix());
		
		s_Batch.End();
		if (s_Batch.GetUsedSize() != 0) {
			RenderCommand::RenderIndexed(s_Batch.GetVertexArray());

			if (clearBatch) s_Batch.Clear();
		}
	}

	// ##### RENDERING OBJECTS FUNCTIONS ######

	void Renderer::Submit(RenderingBatchElement element) {
		if (!s_Batch.HasSpace(element)) {
			FlushScene();
		};
		s_Batch.AddData(element);
	}

	// ##### ENVIRONMENT FUNCTIONS ######

	void Renderer::SetActiveRenderingFrame(RenderingFrame frame, bool clearBatch) {
		// FlushScene(clearBatch);

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

		SetActiveRenderingFrame(RenderingFrame());

		s_Batch = RenderingBatch();
		s_Batch.INIT();
	}
}