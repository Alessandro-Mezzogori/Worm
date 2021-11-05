#pragma once

#include "Worm/Core/Core.h"
#include "Worm/Rendering/Shader.h"

namespace Worm {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const char* vertexShader, const char* fragmentShader);
		~OpenGLShader();

		virtual void Activate() const override;

		virtual int32_t GetUniformBlockBinding(std::string_view name) const override;

		virtual void LoadUniform(std::string_view name, int value) const override;
		virtual void LoadUniform(std::string_view name, float value) const override;
		virtual void LoadUniform(std::string_view name, glm::vec3 value) const override;
		virtual void LoadUniform(std::string_view name, glm::vec4 value) const override;
		virtual void LoadUniform(std::string_view name, glm::mat3 value, bool transpose) const override;
		virtual void LoadUniform(std::string_view name, glm::mat4 value, bool transpose) const override;
	private:
		unsigned int m_ID;
	};
}