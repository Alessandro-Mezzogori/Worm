#include "wormpch.h"
#include "Buffers.h"

#include "Worm/Core/Application.h"

#include "Worm/Platform/RenderingApi/OpenGL/OpenGLBuffers.h"

namespace Worm{

Shared<VertexBuffer> Worm::VertexBuffer::Create()
{
	switch (Application::GetAPI())
	{
	case RenderingAPI::API::OPENGL: return CreateSharedResource<OpenGLVertexBuffer>();
	case RenderingAPI::API::DEFAULT: return CreateSharedResource<OpenGLVertexBuffer>();
	case RenderingAPI::API::NONE:
	default:
		WORM_CORE_ASSERT(false, "None RenderingAPI is not supported");
	}
	return nullptr;
}

Shared<IndexBuffer> Worm::IndexBuffer::Create()
{
	switch (Application::GetAPI())
	{
	case RenderingAPI::API::OPENGL: return CreateSharedResource<OpenGLIndexBuffer>();
	case RenderingAPI::API::DEFAULT: return CreateSharedResource<OpenGLIndexBuffer>();
	case RenderingAPI::API::NONE:
	default:
		WORM_CORE_ASSERT(false, "None RenderingAPI is not supported");
	}
	return nullptr;
}

}
