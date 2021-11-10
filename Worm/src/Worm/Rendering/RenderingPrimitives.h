#pragma once

#include <glm/glm.hpp>
#include <array>

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

	struct Vertex {
		glm::vec3 Position;
		glm::vec2 TextureCoords;
		float TextureID;
	};

	namespace VertexUtils {
		inline std::array<Vertex, 4> CreateQuad(float x, float y, float size, float textureID) {
			return { {
				{{x, y, 0.0f}, {0.0f, 0.0f}, textureID},
				{{x + size, y, 0.0f}, {1.0f, 0.0f}, textureID},
				{{x + size, y + size, 0.0f}, {1.0f, 1.0f}, textureID},
				{{x, y + size, 0.0f}, {0.0f, 1.0f}, textureID}
			}};
		}
	}
}