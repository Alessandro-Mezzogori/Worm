#include "wormpch.h"
#include "Event.h"

namespace Worm {
	//
	//	Used to group EventCategories flags together
	//
	EventCategory operator|(const EventCategory& rhs, const EventCategory& lhs)
	{
		return static_cast<EventCategory>(static_cast<uint32_t>(rhs) | static_cast<uint32_t>(lhs));
	}

	//
	//	Used to retrieve the shared categories flags between a and b
	//
	EventCategory operator&(const EventCategory& rhs, const EventCategory& lhs)
	{
		return static_cast<EventCategory>(static_cast<uint32_t>(rhs) & static_cast<uint32_t>(lhs));
	}

	//
	//	Comparing if a categories has all the flags of the other
	//
	bool operator==(const EventCategory& rhs, const EventCategory& lhs)
	{
		return static_cast<uint32_t>(rhs & lhs) == static_cast<uint32_t>(rhs);
	}

	
}