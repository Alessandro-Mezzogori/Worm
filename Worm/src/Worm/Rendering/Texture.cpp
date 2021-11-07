#include "wormpch.h"
#include "Texture.h"

#include "Worm/Core/Application.h"
#include "Worm/Platform/RenderingApi/OpenGL/OpenGLTexture.h"

namespace Worm {
	Shared<Texture> Texture::Create(std::filesystem::path path) {
		switch (Application::GetAPI()) {
			case RenderingAPI::API::OPENGL: return CreateSharedResource<OpenGLTexture>(path); 
			case RenderingAPI::API::DEFAULT: return CreateSharedResource<OpenGLTexture>(path); 
			case RenderingAPI::API::NONE:
			default:
				WORM_CORE_ASSERT(false, "None Rendering API isn't supported");
		}
		return nullptr;
	}
}