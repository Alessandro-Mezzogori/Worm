#pragma once

#include "Worm/Rendering/RenderingContext.h"
 
struct GLFWwindow;

namespace Worm {
	class OpenGLRenderingContext : public RenderingContext{
	public:
		OpenGLRenderingContext(GLFWwindow* window);

		virtual void INIT() override;

		virtual void SwapBuffers() const override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}