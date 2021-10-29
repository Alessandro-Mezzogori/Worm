#include "wormpch.h"
#include "OpenGLBuffers.h"

#include "glad/glad.h"

namespace Worm{
	/* ##### VERTEX BUFFER ##### */
	OpenGLVertexBuffer::OpenGLVertexBuffer()
	{
		glCreateBuffers(1, &m_ID);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void OpenGLVertexBuffer::SetData(const float* vertices, const size_t size)
	{
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); // TODO add option to change type fo draw
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
	{
		m_BufferLayout = layout;
	}

	const BufferLayout& OpenGLVertexBuffer::GetLayout() const
	{
		return m_BufferLayout;
	}

	/* ##### INDEX BUFFER ##### */

	OpenGLIndexBuffer::OpenGLIndexBuffer()
	{
		m_IndicesCount = 0;
		glCreateBuffers(1, &m_ID);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGLIndexBuffer::SetData(const uint32_t* indices, const size_t count)
	{
		m_IndicesCount = count;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW); // TODO add option to change type fo draw
	}

	const size_t OpenGLIndexBuffer::GetIndicesCount() const
	{
		return m_IndicesCount;
	}

}