#include "wormpch.h"
#include "OpenGLRenderingContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Worm{

	OpenGLRenderingContext::OpenGLRenderingContext(GLFWwindow* window)
		: m_WindowHandle(window)
	{
		WORM_CORE_ASSERT(window != nullptr, "Window handle is a null pointer!");
	}
	
	void OpenGLRenderingContext::INIT()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		WORM_CORE_ASSERT(status, "Failed to initialize GLAD");

		WORM_LOG_CORE_INFO("OpenGL Info:");
		WORM_LOG_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		WORM_LOG_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		WORM_LOG_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
		WORM_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Worm requires at least OpenGL version 4.5!");
	}
	
	void OpenGLRenderingContext::SwapBuffers() const
	{
		glfwSwapBuffers(m_WindowHandle);
	}
	
}