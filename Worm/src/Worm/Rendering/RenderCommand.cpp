#include "wormpch.h"
#include "RenderCommand.h"

namespace Worm {
	const RenderingAPI* RenderCommand::s_RenderingAPI = nullptr;

	// Global initialization functions
	void RenderCommand::INIT() {
		s_RenderingAPI = RenderingAPIController::GetAPI(RenderingAPI::API::DEFAULT);

		// Setup Global values for the rendering api (ex. enableing scissors )
		s_RenderingAPI->EnableScissors(true);
	}
}