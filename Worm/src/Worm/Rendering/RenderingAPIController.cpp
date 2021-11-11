#include "wormpch.h"
#include "RenderingAPIController.h"

#include "Worm/Platform/RenderingApi/OpenGL/OpenGLRenderingAPI.h"
#include "Worm/Platform/RenderingApi/Vulkan/VulkanRenderingAPI.h"

namespace Worm {
    // ##### STATIC INITIALIZATION/DECLARATION #####

    RenderingAPI::API RenderingAPIController::s_LoadedAPItype = RenderingAPI::API::DEFAULT; // TODO 
    Unique<RenderingAPI> RenderingAPIController::s_LoadedAPI = nullptr;
    // ##### PUBLIC METHODS #####

    /*
    * Returns a pointer to the requested RenderingAPI
    */
    RenderingAPI* RenderingAPIController::GetAPIimpl()
    {
        return s_LoadedAPI.get();
    }

    RenderingAPI::API RenderingAPIController::GetAPI() {
        return s_LoadedAPItype;
    }

    void RenderingAPIController::LoadAPI(RenderingAPI::API api) 
    {
        switch (api)
        {
        case Worm::RenderingAPI::API::OPENGL: s_LoadedAPI = CreateUniqueResource<OpenGLRenderingAPI>(); WORM_LOG_CORE_TRACE("Loading OpenGL RenderingAPI"); break;
        case Worm::RenderingAPI::API::VULKAN: s_LoadedAPI = CreateUniqueResource<VulkanRenderingAPI>(); WORM_LOG_CORE_TRACE("Loading Vulkan RenderingAPI"); break;
        case Worm::RenderingAPI::API::DEFAULT: s_LoadedAPI = CreateUniqueResource<OpenGLRenderingAPI>(); WORM_LOG_CORE_TRACE("Loading Default RenderingAPI ( OpenGL )"); break;
        default:
            WORM_CORE_ASSERT(false, "None RenderingAPI is no supported");
        }
        s_LoadedAPItype = api;
        s_LoadedAPI->Init();
    }

    void RenderingAPIController::INIT() {
        LoadAPI(RenderingAPI::API::DEFAULT);
    }
}
