#pragma once

#include "Camera.h"

namespace Worm {
	class OrtographicCamera : public Camera{
	public:
		OrtographicCamera(uint32_t screenWidth, uint32_t screenHeight, const glm::vec3& position, const glm::vec3& lookPoint);

		virtual void Move(const glm::vec3& direction) override;
		virtual void Rotate(float horizontalDegrees, float verticalDegrees) override;
		virtual void SetSpeed(float speed) override;
		virtual void SetFOV(float fovDegrees = 45.0f, float nearPlane = 0.1f, float farPlane = 100.0f) override;
		virtual void SetScreenSize(uint32_t width, uint32_t height) override;

		virtual inline glm::vec3 GetPosition() const override ;
		virtual inline glm::vec3 GetLookingDirection() const override;
		virtual inline const glm::mat4& GetCamMatrix() const override;
	private:
		void ComputeViewMatrix();
		void ComputeProjectionMatrix();
		void ComputeCameraMatrix();
	private:
		static constexpr glm::vec3 s_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		
		uint32_t m_ScreenWidth, m_ScreenHeight;

		glm::vec3 m_Position;
		glm::vec3 m_LookingDirection;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_CameraMatrix;
		float m_Speed;

		// Perspective parameters ( FOV is stored in radians )
		float m_FOV, m_NearPlane, m_FarPlane;
	};
}