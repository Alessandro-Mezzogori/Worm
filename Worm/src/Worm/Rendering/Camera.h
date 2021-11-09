#pragma once

#include <glm/glm.hpp>

namespace Worm {
	class Camera {
	public:
		virtual void Move(const glm::vec3& direction) = 0;
		virtual void Rotate(float horizontalDegrees, float verticalDegrees) = 0;
		virtual void SetSpeed(float speed) = 0;
		virtual void SetFOV(float fovDegrees = 45.0f, float nearPlane= 0.1f, float farPlane = 100.0f) = 0;
		virtual void SetScreenSize(uint32_t width, uint32_t height) = 0;

		virtual inline glm::vec3 GetPosition() const = 0;
		virtual inline glm::vec3 GetLookingDirection() const = 0;
		virtual inline const glm::mat4& GetCamMatrix() const = 0;
	};
}