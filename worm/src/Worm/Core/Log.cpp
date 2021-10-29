#include "wormpch.h"
#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>


namespace Worm {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::INIT()
	{
		// [%TIME] %LOGGER_NAME: %MESSAGE
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stderr_color_mt<spdlog::synchronous_factory>("WORM");
		s_CoreLogger->set_level(spdlog::level::trace);
		
		s_ClientLogger = spdlog::stderr_color_mt<spdlog::synchronous_factory>("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}	
}