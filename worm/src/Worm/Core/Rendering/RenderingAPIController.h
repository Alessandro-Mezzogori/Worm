#pragma once

#include <unordered_map>

#include "RenderingAPI.h"

namespace Worm{

	class RenderingAPIController
	{
	public:
		enum class API {
			OPENGL,
			DEFAULT,
		};
	public:
		static Shared<RenderingAPI> LoadAPI(API api);
		static void INIT();
	private:
		static std::unordered_map <RenderingAPIController::API, Shared<RenderingAPI>> s_LoadedApi;
	};

}

