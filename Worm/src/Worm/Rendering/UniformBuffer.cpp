#include "wormpch.h"
#include "UniformBuffer.h"

#include "Worm/Core/Application.h"
#include "Worm/Core/Log.h"

#include "Worm/Platform/RenderingApi/OpenGL/OpenGLUniformBuffer.h"

namespace Worm {
	Shared<UniformBuffer> UniformBuffer::Create()
	{
		switch (Application::GetAPI())
		{
		case RenderingAPI::API::OPENGL: return CreateSharedResource<OpenGLUniformBuffer>();
		case RenderingAPI::API::DEFAULT: return CreateSharedResource<OpenGLUniformBuffer>();
		case RenderingAPI::API::NONE:
		default:
			WORM_CORE_ASSERT(false, "None RenderingAPI is not supported");
		}
		return nullptr;
	}
}