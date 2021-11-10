#pragma once

#include "Worm/Core/Core.h"

#include "VertexArray.h"

namespace Worm {
	struct BatchSpecification {
		int32_t MaxFragmentTextureSlots;
	};

	struct BatchInformation {
		BufferLayout VerticesLayout;	// Batch Vertex Layout information
	};

	struct RenderingBatchElement {
		void* Data;				// Contains the data to be copied inside the temporary vertex batching buffer
		uint32_t* Indices;		// Contains the indices to be copied inside the temporary index batching buffer
		size_t Size;			// Size of Data
		size_t IndicesCount;	// Number of indices inside Indices
	};

	class RenderingBatch {
	public:
		RenderingBatch();
		~RenderingBatch() = default;

		void INIT(BatchSpecification specification);
		void Clear();

		void Begin(BatchInformation info);
		void End();

		void AddData(RenderingBatchElement element);
		bool HasSpace(RenderingBatchElement element) const;

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
		size_t m_MaxTextureSlots; 

		size_t m_VertexSize;

		// Saved data pointers
		char* m_DataPtr;
		uint32_t* m_IndicesPtr;
		std::vector<char> m_Data;
		std::vector<uint32_t> m_Indices;

		std::vector<uint32_t> m_Textures;

		// Rendering Buffers
		Shared<VertexBuffer> m_VertexBuffer;
		Shared<IndexBuffer> m_IndexBuffer;
		Shared<VertexArray> m_VertexArray;
	};
}