#pragma once

namespace Worm {
	class Texture{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};
}