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

		virtual void LoadUniform(std::string_view name, int value) const = 0;
		virtual void LoadUniform(std::string_view name, float value) const = 0;
		virtual void LoadUniform(std::string_view name, glm::vec3 value) const = 0;
		virtual void LoadUniform(std::string_view name, glm::vec4 value) const = 0;
		virtual void LoadUniform(std::string_view name, glm::mat3 value, bool transpose) const = 0;
		virtual void LoadUniform(std::string_view name, glm::mat4 value, bool transpose) const = 0;
	};
}