#pragma once

#ifdef WORM_PLATFORM_WINDOWS

extern Worm::Application* Worm::CreateApplication();

int main(int argc, char** argv)
{
	Worm::Log::INIT();

	WORM_LOG_CORE_TRACE("Creating Application");
	auto app = Worm::CreateApplication();
	app->Run();
	delete app;
	WORM_LOG_CORE_TRACE("Deleting Application");

	return 0;
}

#else 
#error Worm only supports Windows 64x
#endif 
