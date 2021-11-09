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

		RenderingBatchElement(void* data, uint32_t* indices, size_t size, size_t indicesCount, BufferLayout layout) :
			Data(data), Indices(indices), Size(size), IndicesCount(indicesCount), Layout(layout)
		{
		}

		RenderingBatchElement() {
			Data = nullptr;
			Indices = nullptr;
			Size = 0;
			IndicesCount = 0;
			Layout = BufferLayout();
		}
	};

	class RenderingBatch {
	public:
		RenderingBatch();
		~RenderingBatch() = default;

		void INIT();
		void Clear();

		void Begin();
		void End();

		void AddData(RenderingBatchElement element);
		bool HasSpace(RenderingBatchElement element) const;

		void SetBufferLayout(const BufferLayout& layout);
		const VertexArray& GetVertexArray() const;

		inline size_t GetMaximumSize() const;
		inline size_t GetUsedSize() const;
		inline size_t GetIndicesUsed() const;
	private:
		// Batcher attributes
		static constexpr size_t s_DefaultMaxBatchSize = 3145728; // 3MB -> average vertex is approx 50 -> 60k vertices per pass
		static constexpr size_t s_DefaultMaxIndicesCount =  524288 ; // 2MB of indices -> 5MB of data transfered per batch if filled

		size_t m_MaxBatchSize;
		size_t m_MaxIndicesCount;
		size_t m_MaxTextureSlots; // queried from driver on init

		size_t m_VertexSize;

		// Saved data pointers
		char* m_DataPtr;
		uint32_t* m_IndicesPtr;
		std::vector<char> m_Data;
		std::vector<uint32_t> m_Indices;

		// Control attributes
		bool m_HasBufferLayout;

		// Rendering Buffers
		Shared<VertexBuffer> m_VertexBuffer;
		Shared<IndexBuffer> m_IndexBuffer;
		Shared<VertexArray> m_VertexArray;
	};
}