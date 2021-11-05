#pragma once

namespace Worm {
	struct RenderingViewport{
		float x;
		float y;

		float width; // percentage of screen width
		float height; // percentage of screen height

		RenderingViewport(float x, float y, float width, float height) : x(x), y(y), width(width), height(height)  {}
		RenderingViewport() : RenderingViewport(0.0f, 0.0f, 1.0f, 1.0f)  {}
	};

	namespace ViewportUtils {
		inline RenderingViewport GetHorizontalComplementaryViewport(RenderingViewport vp) {
			return { 1.0f - vp.x - vp.width, vp.y, 1.0f - vp.width, vp.height };
		}
	}
}