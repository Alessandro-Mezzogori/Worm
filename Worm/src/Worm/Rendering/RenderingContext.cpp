#include "wormpch.h"
#include "RenderingContext.h"

#include "Worm/Core/Application.h"

#include "Worm/Platform/RenderingApi/OpenGL/OpenGLRenderingContext.h"

namespace Worm {
    Unique<RenderingContext> RenderingContext::Create(void* window)
    {
        switch (Application::GetAPI()) {
            case RenderingAPI::API::DEFAULT:
            case RenderingAPI::API::OPENGL: return CreateUniqueResource<OpenGLRenderingContext>(static_cast<GLFWwindow*>(window)); break;
            case RenderingAPI::API::VULKAN: 
                WORM_CORE_ASSERT(false, "RenderingAPI Vulkan is not supported!") break;
            case RenderingAPI::API::NONE:
                WORM_CORE_ASSERT(false, "RenderingAPI None is not supported!");
        }
    }
}

