#include "wormpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Worm{
	static GLenum ShaderTypeToOpenGL(ShaderType type) {
		switch (type)
		{
			case Worm::ShaderType::FLOAT:	 return GL_FLOAT;
			case Worm::ShaderType::FLOAT2:	return GL_FLOAT;
			case Worm::ShaderType::FLOAT3:	return GL_FLOAT;
			case Worm::ShaderType::FLOAT4:	 return GL_FLOAT;
			case Worm::ShaderType::INT:		return GL_INT;
			case Worm::ShaderType::INT2:	return GL_INT;
			case Worm::ShaderType::INT3:	return GL_INT;
			case Worm::ShaderType::INT4:	return GL_INT;
			case Worm::ShaderType::MAT3:	return GL_FLOAT;
			case Worm::ShaderType::MAT4:	return GL_FLOAT;
			case Worm::ShaderType::BOOL:	return GL_BOOL;
			default:
				WORM_CORE_ASSERT(false, "Unknown ShaderType");
		}
	}

	OpenGLVertexArray::OpenGLVertexArray() : m_LayoutIndex(0)
	{
		glCreateVertexArrays(1, &m_ID);
	}
	
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_ID);
	}
	
	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_ID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(Shared<VertexBuffer> buffer)
	{
		m_VertexBuffers.push_back(buffer);

		const auto& layout = buffer->GetLayout();
		for (const auto& element : layout) {
			switch (element.type)
			{
				case Worm::ShaderType::FLOAT:	
				case Worm::ShaderType::FLOAT2:	
				case Worm::ShaderType::FLOAT3:	
				case Worm::ShaderType::FLOAT4:
				case Worm::ShaderType::MAT3:
				case Worm::ShaderType::MAT4:
				{
					glEnableVertexAttribArray(m_LayoutIndex);
					glVertexAttribPointer(
						m_LayoutIndex,
						element.GetComponentNumber(),
						ShaderTypeToOpenGL(element.type),
						element.normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(element.offset)
					);
					m_LayoutIndex++;
					break;
				}
				case Worm::ShaderType::INT:		
				case Worm::ShaderType::INT2:	
				case Worm::ShaderType::INT3:	
				case Worm::ShaderType::INT4:	
				case Worm::ShaderType::BOOL:
				{
					glEnableVertexAttribArray(m_LayoutIndex);
					glVertexAttribIPointer(
						m_LayoutIndex,
						element.GetComponentNumber(),
						ShaderTypeToOpenGL(element.type),
						layout.GetStride(),
						(const void*)(element.offset)
					);
					m_LayoutIndex++;
					break;
				}
				default:
					WORM_CORE_ASSERT(false, "Unknown ShaderType");
			}
		}
	}

	void OpenGLVertexArray::SetIndexBuffer(Shared<IndexBuffer> buffer)
	{
		m_IndexBuffer = buffer;
	}
	const Shared<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}
}
