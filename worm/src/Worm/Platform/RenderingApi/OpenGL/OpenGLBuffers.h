#pragma once

#include "Worm/Rendering/Buffers.h"

namespace Worm{
	class OpenGLVertexBuffer : public VertexBuffer{
	public:
		OpenGLVertexBuffer();
		~OpenGLVertexBuffer();

		virtual void Allocate(size_t size, DrawHint hint = DrawHint::STATIC) override;
		virtual void SetData(const void* data, const size_t size, const size_t offset = 0) override;
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void Clear() override;

		virtual void SetLayout(const BufferLayout& layout) override;
		virtual const BufferLayout& GetLayout() const override;
	private:
		unsigned int m_ID;
		BufferLayout m_BufferLayout;
		bool m_Allocated;
		size_t m_AllocatedSize;
	};

	class OpenGLIndexBuffer : public IndexBuffer{
	public:
		OpenGLIndexBuffer();
		~OpenGLIndexBuffer();

		virtual void Allocate(const size_t count, DrawHint hint = DrawHint::STATIC) override;
		virtual void SetData(const uint32_t* indices, const size_t count, const size_t offsetCount = 0) override; 
		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		virtual void Clear() override;

		virtual const size_t GetIndicesCount() const override;
	private:
		unsigned int m_ID;
		size_t m_IndicesCount;
		bool m_Allocated;
	};
}