#pragma once

#include<vector>
#include<inttypes.h>

#include "Worm/Core/Log.h"
#include "Worm/Core/Core.h"
#include "ShaderTypes.h"

namespace Worm{
	enum class DrawHint {
		STATIC, DYNAMIC
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;
	
		/**
		* Allocate the requested memory size on the gpu
		*/
		virtual void Allocate(size_t size, DrawHint hint = DrawHint::STATIC) = 0;

		/**
		* Sets the given data to the allocated buffer, if not allocated it should allocate the space
		*/
		virtual void SetData(const void* vertices, const size_t size, const size_t offset = 0) = 0;

		/**
		* Clears Buffer
		*/
		virtual void Clear() = 0;

		/**
		* Binds/Unbinds the vertex buffer so that it can be used
		*/
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	public:
		/**
		* Factory method for the Vertex Buffer
		*/
		static Shared<VertexBuffer> Create();
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;

		virtual void Allocate(const size_t count, DrawHint hint = DrawHint::STATIC) = 0;
		virtual void SetData(const uint32_t* indices, const size_t count, const size_t offsetCount = 0) = 0;
		virtual void Clear() = 0;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual const size_t GetIndicesCount() const = 0;
	public:
		static Shared<IndexBuffer> Create();
	};
}