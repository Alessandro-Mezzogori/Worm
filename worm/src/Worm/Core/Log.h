#pragma once

#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)

#include "Worm/Core/Core.h"

namespace Worm
{
	
	class Log
	{
	public:
		// needs To be called before using any of the logging functions
		static void INIT();

		inline static const std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static const std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// -- Logging Macros ------------------------------------------- 

#ifdef WORM_ENABLE_LOGGING
	#define WORM_LOG_CORE_TRACE(...)	::Worm::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define WORM_LOG_CORE_DEBUG(...)	::Worm::Log::GetCoreLogger()->debug(__VA_ARGS__)
	#define WORM_LOG_CORE_INFO(...)		::Worm::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define WORM_LOG_CORE_WARN(...)		::Worm::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define WORM_LOG_CORE_ERROR(...)	::Worm::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define WORM_LOG_CORE_CRITICAL(...) ::Worm::Log::GetCoreLogger()->critical(__VA_ARGS__)

	#define WORM_LOG_TRACE(...)		::Worm::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define WORM_LOG_DEBUG(...)		::Worm::Log::GetClientLogger()->debug(__VA_ARGS__)
	#define WORM_LOG_INFO(...)		::Worm::Log::GetClientLogger()->info(__VA_ARGS__)
	#define WORM_LOG_WARN(...)		::Worm::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define WORM_LOG_ERROR(...)		::Worm::Log::GetClientLogger()->error(__VA_ARGS__)
	#define WORM_LOG_CRITICAL(...)	::Worm::Log::GetClientLogger()->critical(__VA_ARGS__)
#else
	#define WORM_LOG_CORE_TRACE(...)	
	#define WORM_LOG_CORE_DEBUG(...)	
	#define WORM_LOG_CORE_INFO(...)		
	#define WORM_LOG_CORE_WARN(...)		
	#define WORM_LOG_CORE_ERROR(...)	
	#define WORM_LOG_CORE_CRITICAL(...) 

	#define WORM_LOG_TRACE(...)		
	#define WORM_LOG_DEBUG(...)		
	#define WORM_LOG_INFO(...)		
	#define WORM_LOG_WARN(...)		
	#define WORM_LOG_ERROR(...)		
	#define WORM_LOG_CRITICAL(...)	
#endif								
