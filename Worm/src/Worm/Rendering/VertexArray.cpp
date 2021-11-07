#include "wormpch.h"
#include "VertexArray.h"

#include "Worm/Core/Application.h"
#include "Worm/Core/Log.h"

#include "Worm/Platform/RenderingApi/OpenGL/OpenGLVertexArray.h"

namespace Worm {
	Shared<VertexArray> VertexArray::Create()
	{
		switch (Application::GetAPI())
		{
		case RenderingAPI::API::OPENGL: return CreateSharedResource<OpenGLVertexArray>();
		case RenderingAPI::API::DEFAULT: return CreateSharedResource<OpenGLVertexArray>();
		case RenderingAPI::API::NONE:
		default:
			WORM_CORE_ASSERT(false, "None RenderingAPI is not supported");
		}
		return nullptr;
	}
}