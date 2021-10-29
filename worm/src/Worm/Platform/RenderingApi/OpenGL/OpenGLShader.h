#pragma once

#include "Worm/Core/Core.h"
#include "Worm/Core/Rendering/Shader.h"

namespace Worm {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const char* vertexShader, const char* fragmentShader);
		~OpenGLShader();

		virtual void Activate() const override;
	private:
		unsigned int m_ID;
	};
}