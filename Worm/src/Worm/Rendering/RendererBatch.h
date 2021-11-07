#pragma once

namespace Worm {
	class RendererBatch {
	public:
		virtual void INIT() = 0;
		virtual void Allocate(size_t size) = 0;
		virtual void Clear() = 0;
		virtual void Flush() const = 0;

		virtual void AddData(const void* data, size_t size) = 0;
		virtual bool HasSpace(size_t size) const = 0;
		virtual size_t GetMaximumSize() const = 0;
		virtual size_t GetUsedSize() const = 0;
	};
}