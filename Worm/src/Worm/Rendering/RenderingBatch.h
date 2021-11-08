#pragma once

#include "Worm/Core/Core.h"

#include "VertexArray.h"

namespace Worm {
	struct RenderingBatchElement {
		void* Data;
		uint32_t* Indices;
		size_t Size;
		size_t IndicesCount;

		BufferLayout Layout;
	};

	class RenderingBatch {
	public:
		RenderingBatch();
		virtual ~RenderingBatch() = default;

		virtual void INIT();
		virtual void Allocate();
		virtual void Clear();

		virtual void AddData(RenderingBatchElement element);
		virtual bool HasSpace(RenderingBatchElement element) const;

		virtual void SetBufferLayout(const BufferLayout& layout);
		virtual const VertexArray& GetVertexArray() const;

		virtual size_t GetMaximumSize() const;
		virtual size_t GetUsedSize() const;

		// virtual void SetMaximumSize(size_t size);
		// virtual void SetMaximumIndicesCount(size_t count);
	private:
		// Batcher attributes
		static constexpr size_t s_DefaultMaxBatchSize = 3145728; // 3MB -> average vertex is approx 50 -> 60k vertices per pass
		static constexpr size_t s_DefaultMaxIndicesCount =  524288 ; // 2MB of indices -> 5MB of data transfered per batch if filled
		size_t m_MaxBatchSize;
		size_t m_MaxIndicesCount;

		size_t m_UsedSize;
		size_t m_UsedIndices;

		// Control attributes
		bool m_HasBufferLayout;

		// Rendering Buffers
		Shared<VertexBuffer> m_VertexBuffer;
		Shared<IndexBuffer> m_IndexBuffer;
		Shared<VertexArray> m_VertexArray;
	};
}