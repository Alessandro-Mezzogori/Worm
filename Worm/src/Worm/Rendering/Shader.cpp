#include "wormpch.h"
#include "Shader.h"

#include "Worm/Core/Application.h"
#include "Worm/Core/Log.h"

#include "Worm/Platform/RenderingApi/OpenGL/OpenGLShader.h"

namespace Worm {
	Shared<Shader> Shader::Create(const char* vertexShaderSource, const char* fragmentShaderSource)
	{
		switch (Application::GetAPI())
		{
		case RenderingAPI::API::OPENGL: return CreateSharedResource<OpenGLShader>(vertexShaderSource, fragmentShaderSource);
		case RenderingAPI::API::DEFAULT: return CreateSharedResource<OpenGLShader>(vertexShaderSource, fragmentShaderSource);
		case RenderingAPI::API::NONE:
		default:
			WORM_CORE_ASSERT(false, "None RenderingAPI is not supported");
		}
		return nullptr;
	}
}
