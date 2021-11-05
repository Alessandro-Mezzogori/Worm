#pragma once

#include <glm/glm.hpp>

namespace Worm {
	class Shader {
	public:
		virtual ~Shader() = default;
		
		virtual void Activate() const = 0;
		
		//virtual void LoadUniform(int value);
		//virtual void LoadUniform(float value);
		//virtual void LoadUniform(glm::vec3 value);
		//virtual void LoadUniform(glm::mat3 value);
		//virtual void LoadUniform(glm::mat4 value);
	protected:

	};
}