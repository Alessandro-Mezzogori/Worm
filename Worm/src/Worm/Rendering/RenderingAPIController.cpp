#include "wormpch.h"
#include "RenderingAPIController.h"

#include "Worm/Platform/RenderingApi/OpenGL/OpenGLRenderingAPI.h"
#include "Worm/Platform/RenderingApi/Vulkan/VulkanRenderingAPI.h"

namespace Worm {
    // ##### STATIC INITIALIZATION/DECLARATION #####

    std::unordered_map<RenderingAPI::API, Unique<RenderingAPI>> RenderingAPIController::s_LoadedApi;

    // ##### PUBLIC METHODS #####

    /*
    * Returns a pointer to the requested RenderingAPI
    */
    const RenderingAPI* RenderingAPIController::GetAPI(RenderingAPI::API api)
    {
        if (!s_LoadedApi.contains(api)) 
            LoadAPI(api);
        
        return s_LoadedApi[api].get();
    }

    void RenderingAPIController::LoadAPI(RenderingAPI::API api) {
        
        // Create the RenderingAPI handler for the requested api
        switch (api)
        {
        case Worm::RenderingAPI::API::OPENGL: s_LoadedApi[api] = CreateUniqueResource<OpenGLRenderingAPI>(); WORM_LOG_CORE_TRACE("Loading OpenGL RenderingAPI"); break;
        case Worm::RenderingAPI::API::VULKAN: s_LoadedApi[api] = CreateUniqueResource<VulkanRenderingAPI>(); WORM_LOG_CORE_TRACE("Loading Vulkan RenderingAPI"); break;
        default: s_LoadedApi[api] = CreateUniqueResource<OpenGLRenderingAPI>(); WORM_LOG_CORE_TRACE("Loading Default RenderingAPI ( Vulkan )"); break;
        }

        // Initiliaze the requested api
        s_LoadedApi[api]->Init();
    }

    void RenderingAPIController::INIT() {
        s_LoadedApi = std::unordered_map <RenderingAPI::API, Unique<RenderingAPI>>();
    }
}
