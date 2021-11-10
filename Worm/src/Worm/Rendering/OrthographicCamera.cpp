#include "wormpch.h"
#include "OrthographicCamera.h"

#include <glm/ext.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace Worm{

    OrtographicCamera::OrtographicCamera(uint32_t screenWidth, uint32_t screenHeight, const glm::vec3& position, const glm::vec3& lookPoint)
    {
        m_Position = position;
        m_LookingDirection = glm::normalize(lookPoint - m_Position);
    
        m_FOV = glm::radians(45.0f);
        m_NearPlane = 0.01f;
        m_FarPlane = 100.0f;

        m_Speed = 1.0f;

        m_ViewMatrix = glm::mat4(1.0f);
        m_ProjectionMatrix = glm::mat4(1.0f);

        SetScreenSize(screenWidth, screenHeight);
        ComputeViewMatrix();
        ComputeProjectionMatrix();
        ComputeCameraMatrix();
    }

    void OrtographicCamera::Move(const glm::vec3& direction)
    {
        m_Position += direction * m_Speed;
        ComputeViewMatrix();
        ComputeCameraMatrix();
    }

    void OrtographicCamera::ComputeViewMatrix()
    {
        WORM_LOG_CORE_DEBUG("Camera Direction: {0} {1} {2}", m_LookingDirection.x, m_LookingDirection.y, m_LookingDirection.z);
        WORM_LOG_CORE_DEBUG("Camera Position: {0} {1} {2}", m_Position.x, m_Position.y, m_Position.z);
        m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_LookingDirection, s_Up);
    }

    void OrtographicCamera::ComputeProjectionMatrix()
    {
        m_ProjectionMatrix = glm::perspective(m_FOV, ((float)(m_ScreenWidth) / m_ScreenHeight), m_NearPlane, m_FarPlane);
    }

    void OrtographicCamera::ComputeCameraMatrix()
    {
        m_CameraMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrtographicCamera::Rotate(float horizontalDegrees, float verticalDegrees)
    {
        float horizontalRadians = glm::radians(horizontalDegrees);
        float verticalRadians = glm::radians(verticalDegrees);

        // Calculates upcoming vertical change in the Orientation
        glm::vec3 newDirection = glm::rotate(m_LookingDirection, glm::radians(-verticalRadians), glm::normalize(glm::cross(m_LookingDirection, s_Up)));

        // Decides whether or not the next vertical Orientation is legal or not
        if (abs(glm::angle(newDirection, s_Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
        {
            m_LookingDirection = newDirection;
        }

        // Rotates the Orientation left and right
        m_LookingDirection = glm::rotate(m_LookingDirection, glm::radians(-horizontalRadians), s_Up);
        ComputeViewMatrix();
        ComputeCameraMatrix();
    }

    void OrtographicCamera::SetSpeed(float speed)
    {
        m_Speed = speed;
    }

    void OrtographicCamera::SetFOV(float fovDegrees, float nearPlane, float farPlane)
    {
        m_FOV = glm::radians(fovDegrees);
        m_NearPlane = nearPlane;
        m_FarPlane = farPlane;
        ComputeProjectionMatrix();
        ComputeCameraMatrix();
    }

    void OrtographicCamera::SetScreenSize(uint32_t width, uint32_t height)
    {
        m_ScreenWidth = width;
        m_ScreenHeight = height;
    }

    glm::vec3 OrtographicCamera::GetPosition() const { return m_Position; };
    glm::vec3 OrtographicCamera::GetLookingDirection() const { return m_LookingDirection; };
    const glm::mat4& OrtographicCamera::GetCamMatrix() const { return m_CameraMatrix; }
}