#pragma once

namespace Worm {
	class UniformBuffer {
	public:
		virtual ~UniformBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(void* data, size_t size) = 0;
		virtual void SetBindingPoint(uint32_t binding) = 0;
		virtual void SetBindingPointRange(uint32_t binding, size_t start, size_t end) = 0;
	
	};
}