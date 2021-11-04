#pragma once

#include <sstream>

#include "Event.h"
#include "Codes.h"

namespace Worm {
	class MouseEvent
	{
	public:
		inline MouseCode GetButton() { return m_Button; }
	protected:
		MouseEvent(MouseCode button) : m_Button(button) {}
		MouseCode m_Button;
	};

	class MousePressedEvent : public MouseEvent, public Event<EventType::MousePressed>
	{
	public:
		MousePressedEvent(MouseCode button, ModifierKey mods): MouseEvent(button), m_Mods(mods) {}

		virtual const std::string ToString() const override 
		{
			std::stringstream ss;
			ss << "Mouse Pressed: " << m_Button;
			return ss.str();
		}

		inline ModifierKey GetModifiers() const { return m_Mods; }
	private:
		ModifierKey m_Mods;
	};

	class MouseReleasedEvent : public MouseEvent, public Event<EventType::MouseReleased>
	{
	public:
		MouseReleasedEvent(MouseCode button, ModifierKey mods) : MouseEvent(button), m_Mods(mods) {}

		virtual const std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Released: " << m_Button;
			return ss.str();
		}

		inline ModifierKey GetModifiers() const { return m_Mods; }
	private:
		ModifierKey m_Mods;
	};

	class MouseScrolledEvent : public Event<EventType::MouseScrolled>
	{
	public:
		MouseScrolledEvent(double xOffset, double yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {}

		virtual const std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Cursor Moved: X offset: " << m_xOffset << " Y offset: " << m_yOffset;
			return ss.str();
		}

		inline std::pair<double, double> GetOffsets() const { return { m_xOffset, m_yOffset }; }
		inline double GetXOffset() const { return m_xOffset; }
		inline double GetYOffset() const { return m_yOffset; }
	private:
		double m_xOffset, m_yOffset;
	};

	class CursorMovedEvent : public Event<EventType::CursorMoved>
	{
	public:
		CursorMovedEvent(double xPos, double yPos) : m_xPos(xPos), m_yPos(yPos) {}

		virtual const std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Cursor Moved: X: " << m_xPos << " Y: " << m_yPos;
			return ss.str();
		}

		inline std::pair<double, double> GetPosition() const { return { m_xPos, m_yPos }; }
		inline double GetX() const { return m_xPos; }
		inline double GetY() const { return m_yPos; }
	private:
		double m_xPos, m_yPos;
	};

	class CursorEnterEvent : public Event<EventType::CursorEnter>
	{
	public:
		CursorEnterEvent() = default;

		virtual const std::string ToString() const override
		{
			return "Moused entered";
		}
	};

	class CursorExitEvent : public Event<EventType::CursorExit>
	{
	public:
		CursorExitEvent() = default;

		virtual const std::string ToString() const override
		{
			return "Moused exit";
		}
	};
}