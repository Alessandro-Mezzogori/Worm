#include "wormpch.h"
#include "OpenGLUniformBuffer.h"

#include <glad/glad.h>

namespace Worm{
	OpenGLUniformBuffer::OpenGLUniformBuffer()
	{
		glCreateBuffers(1, &m_ID);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void OpenGLUniformBuffer::Bind() const
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_ID);
	}

	void OpenGLUniformBuffer::Unbind() const
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLUniformBuffer::SetData(void* data, size_t size)
	{
		glBufferData(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
	}

	void OpenGLUniformBuffer::SetBindingPoint(uint32_t binding)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_ID);
	}

	void OpenGLUniformBuffer::SetBindingPointRange(uint32_t binding, size_t start, size_t end)
	{
		glBindBufferRange(GL_UNIFORM_BUFFER, binding, m_ID, start, end);
	}

}