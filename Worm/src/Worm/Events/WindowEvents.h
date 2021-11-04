#pragma once

#include <sstream>

#include "Event.h"
#include "Worm/Core/Window.h"

namespace Worm {
	class WindowResizedEvent : public Event<EventType::WindowResized>
	{
	public:
		WindowResizedEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height)
		{
		}

		inline virtual std::pair<unsigned int, unsigned int> GetSize() { return { m_Width, m_Height }; }
		inline virtual unsigned int GetWidth() { return GetSize().first; }
		inline virtual unsigned int GetHeight() { return GetSize().second; }

		virtual const std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Window Resizing Width: " << m_Width << " Height: " << m_Height;
			return ss.str();
		}
	private:
		unsigned int m_Width, m_Height;
	};

	class WindowClosedEvent : public Event<EventType::WindowClosed>
	{
	public:
		WindowClosedEvent() = default;

		virtual const std::string ToString() const override
		{
			return "Window Closing";
		}
	};

	class WindowFocusedEvent : public Event<EventType::WindowFocused>
	{
	public:
		WindowFocusedEvent() = default;

		virtual const std::string ToString() const override
		{
			return "Window is Focused";
		}
	};

	class WindowUnfocusedEvent : public Event<EventType::WindowUnfocused>
	{
	public:
		WindowUnfocusedEvent() = default;

		virtual const std::string ToString() const override
		{
			return "Window lost focus";
		}
	};

	class WindowMovedEvent : public Event<EventType::WindowMoved>
	{
	public:
		WindowMovedEvent(int xPos, int yPos) : m_xPos(xPos), m_yPos(yPos) {}

		virtual const std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Window Moved to X: " << m_xPos << " Y: " << m_yPos;
			return ss.str();
		}

		inline std::pair<int, int> GetPosition() const { return { m_xPos, m_yPos }; }
		inline int GetX() const { return m_xPos; }
		inline int GetY() const { return m_yPos; }
	private:
		int m_xPos, m_yPos;
	};

	class WindowRefreshedEvent : public Event<EventType::WindowRefreshed>
	{
	public:
		WindowRefreshedEvent() = default;

		virtual const std::string ToString() const override
		{
			return "Window Refreshing";
		}
	};

	class WindowMinimizedEvent : public Event<EventType::WindowMinimized>
	{
	public:
		WindowMinimizedEvent() = default;

		virtual const std::string ToString() const override
		{
			return "Window Minimized";
		}
	};

	class WindowUnminimizedEvent : public Event<EventType::WindowUnminimized>
	{
	public:
		WindowUnminimizedEvent() = default;

		virtual const std::string ToString() const override
		{
			return "Window Unminimized";
		}
	};

	class WindowMaximizedEvent : public Event<EventType::WindowMaximized>
	{
	public:
		WindowMaximizedEvent() = default;

		virtual const std::string ToString() const override
		{
			return "Window Maximized";
		}
	};

	class WindowUnmaximizedEvent : public Event<EventType::WindowUnmaximized>
	{
	public:
		WindowUnmaximizedEvent() = default;

		virtual const std::string ToString() const override
		{
			return "Window Unmaximized";
		}
	};
}