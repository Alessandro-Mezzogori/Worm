#pragma once

#include <string>

namespace Testing
{
	class TestingModuleInterface
	{
	public:
		virtual void Run() = 0;
	};

	struct Test
	{
		std::string Name;
		TestingModuleInterface* TestObject;
	};
}

