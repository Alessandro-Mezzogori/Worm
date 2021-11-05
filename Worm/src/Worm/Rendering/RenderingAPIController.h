#pragma once

#include <unordered_map>

#include "RenderingAPI.h"

namespace Worm{

	class RenderingAPIController
	{
	public:
		/**
		* Loads and returns a const reference to the requested RenderingAPI
		* ( The ownership of the RenderingAPI object is of the Controller )
		*/
		static const RenderingAPI* GetAPI(RenderingAPI::API api);
		static void INIT();
	private:
		static void LoadAPI(RenderingAPI::API api);
	private:
		// TODO get rid of map if there's won't be any hot swappable rendering api ( turning the controller into a simple factory )
		static std::unordered_map <RenderingAPI::API, Unique<RenderingAPI>> s_LoadedApi;
	};

}

