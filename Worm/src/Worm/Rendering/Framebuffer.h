#pragma once

#include "Renderbuffer.h"
#include "Texture.h"

namespace Worm {
	class Framebuffer {
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddRenderBuffer(Renderbuffer renderbuffer) = 0;
		virtual void AttachTexture(Texture texture) = 0;
	};
}