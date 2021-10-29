#include "Worm.h"

#include "TestingModule.h"

#include <unordered_map>

//
// Test List with corresponding objects
//


std::vector<Testing::Test> tests = {
	{}
};

class TestingStarter : public Worm::Application
{
public:
	TestingStarter()
	{

	}

	~TestingStarter()
	{

	}
private:

};

Worm::Application* Worm::CreateApplication() { return new TestingStarter(); }