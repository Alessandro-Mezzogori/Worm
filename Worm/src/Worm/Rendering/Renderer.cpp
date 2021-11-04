#include "wormpch.h"
#include "Renderer.h"

namespace Worm {
	RenderingFrame Renderer::s_ActiveFrame = RenderingFrame();

	void Renderer::RenderVertexArray(const VertexArray& vertexArray) {
		s_ActiveFrame.renderingApi->RenderVertexArray(vertexArray);
	}

	void Renderer::ClearColor(const glm::vec4& color) {
		s_ActiveFrame.renderingApi->ClearColor(color);
	}

	void Renderer::ClearFrame() {
		s_ActiveFrame.renderingApi->ClearFrame();
	}

	void Renderer::UseRenderingFrame(RenderingFrame frame) {
		s_ActiveFrame = frame;

		RenderingViewport vp = s_ActiveFrame.renderingViewport;
		s_ActiveFrame.renderingApi->SetViewport(vp.x, vp.y, vp.width, vp.height);
	}

	void Renderer::INIT() {
		RenderingAPIController::INIT();

		s_ActiveFrame = RenderingFrame(RenderingAPIController::API::DEFAULT);
	}
}