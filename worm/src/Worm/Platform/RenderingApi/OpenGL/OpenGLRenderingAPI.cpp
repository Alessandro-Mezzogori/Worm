#include "wormpch.h"
#include "OpenGLRenderingAPI.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Worm/Core/Application.h"

namespace Worm{
	void OpenGLRenderingAPI::Init() {
		m_ClearBitField = GL_COLOR_BUFFER_BIT;
	}

	void OpenGLRenderingAPI::RenderIndexed(const VertexArray& vertexArray) const
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
		glClear((GLbitfield) m_ClearBitField);
	}

	void OpenGLRenderingAPI::SetViewportAndScissors(float x, float y, float width, float height)
	{
		const Unique<Window>& window = Application::GetWindow();

		GLint xCoord = static_cast<GLint>(x * window->GetWidth());
		GLint yCoord = static_cast<GLint>(y * window->GetHeight());
		GLsizei vpWidth = static_cast<GLsizei>(width * window->GetWidth());
		GLsizei vpHeight = static_cast<GLsizei>(height * window->GetHeight());

		// Sets the rendering viewport
		//glViewport(xCoord, yCoord, vpWidth, vpHeight);
		glViewport(0, 0, vpWidth, vpHeight);
		// Sets the scissor box so that everything outside is culled 
		// glScissor(xCoord, yCoord, vpWidth, vpHeight);
	}

	void OpenGLRenderingAPI::EnableScissors(bool value)
	{
		if (value) {
			glEnable(GL_SCISSOR_TEST);
		}
		else {
			glDisable(GL_SCISSOR_TEST);
		}
	}

	void OpenGLRenderingAPI::EnableDepthTest(bool value) {
		if (value) {
			glEnable(GL_DEPTH_TEST);
			m_ClearBitField |= GL_DEPTH_BUFFER_BIT; 
		}
		else {
			glDisable(GL_DEPTH_TEST);
			m_ClearBitField &= ~(GL_DEPTH_BUFFER_BIT);
		}
	}

	const RenderingAPIInformation& OpenGLRenderingAPI::GetInformation() 
	{
		if (!m_IsLoadedInformation) {
			// Populate RenderingAPIInformation for the GetInformation() method
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_Information.MaxFragmentTextureSlots);
			m_IsLoadedInformation = true;
		}

		return m_Information;
	}
}


