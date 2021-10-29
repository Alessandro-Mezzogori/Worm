#include "wormpch.h"
#include "OpenGLRenderingAPI.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Worm/Core/Application.h"

namespace Worm{
	void OpenGLRenderingAPI::Init() {
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			WORM_LOG_CORE_CRITICAL("Failed to initialize GLAD");
			return;
		}
	}

	void OpenGLRenderingAPI::RenderVertexArray(const VertexArray& vertexArray) const
	{
		vertexArray.Bind();
		glDrawElements(GL_TRIANGLES, (GLsizei) vertexArray.GetIndexBuffer()->GetIndicesCount(), GL_UNSIGNED_INT, (void*)0);
	}

	void OpenGLRenderingAPI::ClearColor(const glm::vec4& color) const
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderingAPI::ClearFrame() const
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderingAPI::SetViewport(float x, float y, float width, float height) const
	{
		const Unique<Window>& window = Application::GetWindow();
		glViewport(
			static_cast<GLint>(x * window->GetWidth()),
			static_cast<GLint>(y * window->GetHeight()),
			static_cast<GLsizei>(width * window->GetWidth()),
			static_cast<GLsizei>(height * window->GetHeight())
		);
	}
}


