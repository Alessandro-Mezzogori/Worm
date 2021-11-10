#include "wormpch.h"
#include "RenderCommand.h"

namespace Worm {
	RenderingAPI* RenderCommand::s_RenderingAPI = nullptr;

	// Global initialization functions
	void RenderCommand::INIT() {
		s_RenderingAPI = RenderingAPIController::GetAPIimpl();

		// Setup Global values for the rendering api (ex. enableing scissors )
		s_RenderingAPI->EnableScissors(true);
		s_RenderingAPI->EnableDepthTest(true);
	}
}