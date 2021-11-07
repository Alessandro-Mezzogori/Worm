#pragma once


namespace Worm {


	class Framebuffer {
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};
}