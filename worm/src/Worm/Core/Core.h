#pragma once

//
//	ASSERTS
//

#ifdef WORM_DEBUG
	#define WORM_ENABLE_LOGGING	
	#define WORM_ENABLE_ASSERTS
#endif

#ifdef WORM_ENABLE_ASSERTS
	#define WORM_ASSERT(x, ...) { if(!(x)) { WORM_LOG_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } } 
	#define WORM_CORE_ASSERT(x, ...) { if(!(x)) { WORM_LOG_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } } 
#else
	#define WORM_ASSERT(x, ...)
	#define WORM_CORE_ASSERT(x, ...)
#endif
	
#include<memory>
#include<functional>

namespace Worm {
	//
	//	
	//
	constexpr int BIT(unsigned char x) { return 1 << x; }

	//
	//	Functions and Methods conversion to std::function<>
	//

	template<typename R, typename P, typename C>
	std::function<R(P)> BIND_METHOD_CALLBACK(C* ptr, R(C::* method)(P)) {
		return [ptr, method](P arg) { return (ptr->*method)(arg);  };
	}

	template<typename R, typename C>
	std::function<R()> BIND_METHOD_CALLBACK(C* ptr, R(C::* method)()) {
		return [ptr, method]() { return (ptr->*method)();  };
	}

	template<typename R, typename P>
	std::function<R(P)> BIND_FUNCTION_CALLBACK(R(*method)(P)) {
		return [method](P arg) { return (*method)(arg);  };
	}

	template<typename R>
	std::function<R()> BIND_FUNCTION_CALLBACK(R(*method)()) {
		return [method]() { return (*method)();  };
	}

	//
	//	Unique and Shared ptr renaming for future redefinition with classes for behavior consinstency trough standard library changes
	//

	template<typename T>
	using Unique = std::unique_ptr<T>;
	template<typename T, typename... Args>
	constexpr Unique<T> CreateUniqueResource(Args &&...args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Shared = std::shared_ptr<T>;
	template<typename T, typename... Args>
	constexpr Shared<T> CreateSharedResource(Args &&...args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}