#pragma once

#include "Worm/Core/Core.h"

namespace Worm{
	class RenderingContext {
	public:
		virtual ~RenderingContext() = default;

		virtual void INIT() = 0;
		virtual void SwapBuffers() const = 0;
	public:
		static Unique<RenderingContext> Create(void* window);
	};
}