#pragma once

#include "Worm/Core/Rendering/Buffers.h"

namespace Worm{
	class OpenGLVertexBuffer : public VertexBuffer{
	public:
		OpenGLVertexBuffer();
		~OpenGLVertexBuffer();

		virtual void SetData(const float* vertices, const size_t size) override;
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override;
		virtual const BufferLayout& GetLayout() const override;
	private:
		unsigned int m_ID;
		BufferLayout m_BufferLayout;
	};

	class OpenGLIndexBuffer : public IndexBuffer{
	public:
		OpenGLIndexBuffer();
		~OpenGLIndexBuffer();

		virtual void SetData(const uint32_t* indices, const size_t count) override; 
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual const size_t GetIndicesCount() const override;
	private:
		unsigned int m_ID;
		size_t m_IndicesCount;
	};
}