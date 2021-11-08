#include "wormpch.h"
#include "OpenGLBuffers.h"

#include "glad/glad.h"

namespace Worm{
	/* ##### VERTEX BUFFER ##### */
	OpenGLVertexBuffer::OpenGLVertexBuffer()
	{
		glCreateBuffers(1, &m_ID);
		m_Allocated = false;
		m_AllocatedSize = 0;
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void OpenGLVertexBuffer::Allocate(size_t size, DrawHint hint)
	{
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, hint == DrawHint::STATIC ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
		m_Allocated = true;
		m_AllocatedSize = size;
	}

	void OpenGLVertexBuffer::SetData(const void* data, const size_t size, const size_t offset)
	{
		if (!m_Allocated) Allocate(size);
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::Clear()
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_AllocatedSize, nullptr);
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
		m_Allocated = false;
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

	void OpenGLIndexBuffer::Allocate(const size_t count, DrawHint hint)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), nullptr, hint == DrawHint::STATIC ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
		m_Allocated = true;
	}

	void OpenGLIndexBuffer::SetData(const uint32_t* indices, const size_t count, const size_t offsetCount)
	{
		// If the last utilized index is greater than the current last utilized -> update the count
		if (m_Allocated && m_IndicesCount < offsetCount + count) { m_IndicesCount = offsetCount + count; }
		
		if (!m_Allocated) Allocate(count);

		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offsetCount * sizeof(uint32_t), count * sizeof(uint32_t), indices);
	}

	void OpenGLIndexBuffer::Clear()
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_IndicesCount * sizeof(uint32_t), nullptr);
	}

	const size_t OpenGLIndexBuffer::GetIndicesCount() const
	{
		return m_IndicesCount;
	}

	

}