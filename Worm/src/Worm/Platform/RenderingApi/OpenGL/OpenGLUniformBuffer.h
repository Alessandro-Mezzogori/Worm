#pragma once

#include "Worm/Rendering/UniformBuffer.h"

namespace Worm {
	class OpenGLUniformBuffer : public UniformBuffer {
	public:
		OpenGLUniformBuffer();
		~OpenGLUniformBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void SetData(void* data, size_t size) override;
	
		virtual void SetBindingPoint(uint32_t binding) override;
		virtual void SetBindingPointRange(uint32_t binding, size_t start, size_t end) override;
	private:
		uint32_t m_ID;
	};
}