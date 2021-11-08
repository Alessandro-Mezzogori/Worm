#pragma once

#include <vector>

#include "Buffers.h"
#include "Worm/Core/Core.h"

namespace Worm {
	class VertexArray {
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(Shared<VertexBuffer> buffer) = 0;
		virtual void SetIndexBuffer(Shared<IndexBuffer> buffer) = 0;
	
		// Detaches every vertex buffer from the vertex array
		virtual void DetachVertexBuffers() = 0;

		virtual const Shared<IndexBuffer>& GetIndexBuffer() const = 0;
	public:
		static Shared<VertexArray> Create();
	};

}