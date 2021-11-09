#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Worm {
	class Shader {
	public:
		virtual ~Shader() = default;
		
		virtual void Activate() const = 0;
		
		// ##### Shader Information #####

		virtual int32_t GetUniformBlockBinding(std::string_view name) const = 0;

		// ##### Shader Uniforms #####

		virtual void LoadInt(std::string_view name, int value) const = 0;
		virtual void LoadFloat(std::string_view name, float value) const = 0;
		virtual void LoadFloat3(std::string_view name, glm::vec3 value) const = 0;
		virtual void LoadFloat4(std::string_view name, glm::vec4 value) const = 0;
		virtual void LoadMat3(std::string_view name, glm::mat3 value, bool transpose = false) const = 0;
		virtual void LoadMat4(std::string_view name, glm::mat4 value, bool transpose = false) const = 0;
	public:
		// temporary while waiting shader library / controller
		static Shared<Shader> Create(const char* vertexShaderSource, const char* fragmentShaderSource);
	};
}