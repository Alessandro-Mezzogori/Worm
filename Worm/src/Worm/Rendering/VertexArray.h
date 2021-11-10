#pragma once

#include <vector>

#include "Buffers.h"
#include "Worm/Core/Core.h"

namespace Worm {
	struct BufferLayoutElement {
		ShaderType type;
		std::string name;
		uint32_t offset;
		uint32_t size;
		bool normalized;

		BufferLayoutElement(ShaderType type, std::string name, bool normalized = false) {
			// This will be computed inside the BufferLayout class because they're dependant on the other values inside the buffer layout
			offset = 0;

			this->type = type;
			this->name = name;
			this->normalized = normalized;

			size = ShaderTypeSizeOf(type);
		}

		unsigned int GetComponentNumber() const {
			switch (type)
			{
			case Worm::ShaderType::FLOAT:	return 1;
			case Worm::ShaderType::FLOAT2:	return 2;
			case Worm::ShaderType::FLOAT3:	return 3;
			case Worm::ShaderType::FLOAT4:	return 4;
			case Worm::ShaderType::INT:		return 1;
			case Worm::ShaderType::INT2:	return 2;
			case Worm::ShaderType::INT3:	return 3;
			case Worm::ShaderType::INT4:	return 4;
			case Worm::ShaderType::MAT3:	return 3 * 3;
			case Worm::ShaderType::MAT4:	return 4 * 4;
			case Worm::ShaderType::BOOL:	return 1;
			default:
				WORM_CORE_ASSERT(false, "Unknown ShaderType");
			}
		}
	};

	class BufferLayout {
	public:
		BufferLayout() : m_Stride(0) {}

		BufferLayout(const std::initializer_list<BufferLayoutElement>& elements) : m_Elements(elements), m_Stride(0) {
			ComputeStrideAndOffset();
		}

		uint32_t GetStride() const { return m_Stride; }
		const std::vector<BufferLayoutElement>& GetElements() const { return m_Elements; }

		std::vector<BufferLayoutElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferLayoutElement>::iterator end() { return m_Elements.end(); }

		std::vector<BufferLayoutElement>::const_iterator begin() const { return m_Elements.cbegin(); }
		std::vector<BufferLayoutElement>::const_iterator end() const { return m_Elements.cend(); }

	private:
		void ComputeStrideAndOffset() {
			m_Stride = 0;
			unsigned int offset = 0;

			for (auto& element : m_Elements) {
				element.offset = offset;

				m_Stride += element.size;
				offset += element.size;
			}
		}

	private:
		std::vector<BufferLayoutElement> m_Elements;
		uint32_t m_Stride;
	};

	class VertexArray {
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(Shared<VertexBuffer> buffer) = 0;
		virtual void SetIndexBuffer(Shared<IndexBuffer> buffer) = 0;
	
		// Sets the buffer layout that describes how all the attached vertex buffers should have their data structured
		virtual void SetBufferLayout(BufferLayout layout) = 0;

		// Detaches every vertex buffer from the vertex array
		virtual void DetachVertexBuffers() = 0;

		virtual const Shared<IndexBuffer>& GetIndexBuffer() const = 0;
	public:
		static Shared<VertexArray> Create();
	};

}