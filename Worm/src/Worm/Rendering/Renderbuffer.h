#pragma once

namespace Worm {
	class Renderbuffer {
	public:
		virtual ~Renderbuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};
}