#include "wormpch.h"
#include "RenderingAPIController.h"

#include "Worm/Platform/RenderingApi/OpenGL/OpenGLRenderingAPI.h"

namespace Worm {
    // ##### STATIC INITIALIZATION #####

    std::unordered_map<RenderingAPIController::API, Shared<RenderingAPI>> RenderingAPIController::s_LoadedApi;

    // ##### PUBLIC METHODS #####

    Shared<RenderingAPI> RenderingAPIController::LoadAPI(API api)
    {
        if (s_LoadedApi.contains(api)) 
            return s_LoadedApi[api];
    
        switch (api)
        {
        case Worm::RenderingAPIController::API::OPENGL:
            s_LoadedApi[api] = CreateSharedResource<OpenGLRenderingAPI>();
            break;
        default:
            s_LoadedApi[api] = CreateSharedResource<OpenGLRenderingAPI>();
            break;
        }

         s_LoadedApi[api]->Init();

        return s_LoadedApi[api];
    }

    void RenderingAPIController::INIT() {
        s_LoadedApi = std::unordered_map <RenderingAPIController::API, Shared<RenderingAPI>>();
    }
}
