#pragma once

#include <sstream>

#include "Worm/Core/Events/Event.h"


namespace Worm {
	class PathDroppedEvent : public Event<EventType::PathDropped>
	{
	public:
		PathDroppedEvent(int pathCount, const char* paths[]) : m_Paths(paths, paths + pathCount){}

		virtual const std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Path dropped: \n";
			for (const std::string& path : m_Paths)
				ss << path << "\n";
			return ss.str();
		}

		const std::vector<std::string>& GetPaths() { return m_Paths; }	
	private:
		std::vector<std::string> m_Paths;
	};

	class AppTickEvent : public Event<EventType::AppTick>
	{
	public:
		AppTickEvent() = default;

		virtual const std::string ToString() const override
		{
			return "AppTick Event";
		}
	};

	class AppUpdatedEvent : public Event<EventType::AppUpdated>
	{
	public:
		AppUpdatedEvent() = default;

		virtual const std::string ToString() const override
		{
			return "App Updating Event";
		}
	};

	class AppRenderedEvent : public Event<EventType::AppRendered>
	{
	public:
		AppRenderedEvent() = default;

		virtual const std::string ToString() const override
		{
			return "Application is rendering";
		}
	};
}