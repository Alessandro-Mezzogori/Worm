#pragma once

#include <functional>
#include <type_traits>

#include "Worm/Core/Core.h"

namespace Worm {
	enum class EventType {
		// Default event type
		None = 0, 
		// Keyboard Events
		KeyPressed, KeyReleased, KeyTyped,

		// Mouse Events
		MousePressed, MouseReleased, MouseScrolled, 
		// Cursor 
		CursorMoved, CursorEnter, CursorExit,

		// Window Events
		WindowResized, WindowClosed, WindowFocused, WindowUnfocused, WindowMoved, WindowRefreshed,
		WindowMinimized, WindowUnminimized, WindowMaximized, WindowUnmaximized,

		// Application Events
		AppTick, AppUpdated, AppRendered,

		// Other Events
		PathDropped,
	};
	
	enum class EventCategory {
		None = 0,
		Input = BIT(0),
		Mouse = BIT(1),
		Keyboard = BIT(2),
		Window = BIT(3),
		Application = BIT(4),
		Cursor = BIT(5),
	};

	// EventCategory Operators
	EventCategory operator|(const EventCategory& rhs, const EventCategory& lhs);
	EventCategory operator&(const EventCategory& rhs, const EventCategory& lhs);
	bool operator==(const EventCategory& rhs, const EventCategory& lhs);

	static constexpr EventCategory InferEventCategory(EventType type)
	{
		switch (type)
		{
		case EventType::KeyPressed:
		case EventType::KeyReleased:
		case EventType::KeyTyped:
			return EventCategory::Input | EventCategory::Keyboard;

		case Worm::EventType::MousePressed:
		case Worm::EventType::MouseReleased:
		case Worm::EventType::MouseScrolled:
			return EventCategory::Input | EventCategory::Mouse;

		case Worm::EventType::CursorMoved:
			return EventCategory::Input | EventCategory::Cursor;

		case Worm::EventType::CursorEnter:
		case Worm::EventType::CursorExit:
			return EventCategory::Cursor;

		case Worm::EventType::WindowResized:
		case Worm::EventType::WindowClosed:
		case Worm::EventType::WindowFocused:
		case Worm::EventType::WindowUnfocused:
		case Worm::EventType::WindowRefreshed:
		case Worm::EventType::WindowMinimized:
		case Worm::EventType::WindowUnminimized:
		case Worm::EventType::WindowMoved:
		case Worm::EventType::WindowMaximized:
		case Worm::EventType::WindowUnmaximized:
			return EventCategory::Window;

		case Worm::EventType::AppTick:
		case Worm::EventType::AppUpdated:
		case Worm::EventType::AppRendered:
			return EventCategory::Application;

		case Worm::EventType::PathDropped:
			return EventCategory::Input;

		case Worm::EventType::None:
			return EventCategory::None;
		}

		return EventCategory::None;
	}

	// Base Event Interface
	class BaseEvent {
	public:
		virtual EventType GetType() const = 0;
		virtual EventCategory GetCategory() const = 0;
		virtual bool InCategory(EventCategory category) const = 0;
		virtual const std::string ToString() const = 0;

		bool Handled = false;
	};

	// Specialized Event for each EventType
	template<EventType T = EventType::None>
	class Event : public BaseEvent{
	public:
		static EventType GetStaticType() { return T; }
		virtual EventType GetType() const override { return GetStaticType() ; }
		virtual EventCategory GetCategory() const override { return InferEventCategory(T); }
		virtual bool InCategory(EventCategory category) const override { return (GetCategory() & category) != EventCategory::None; };
	};

	class EventDispatcher {
	public:
		EventDispatcher(Shared<BaseEvent> e) : m_Event(e) {}

		template<
			typename T, 
			typename = std::enable_if_t<!std::is_same_v<BaseEvent, T>>,
			typename = std::enable_if_t<std::is_base_of_v<BaseEvent, T>>
		>
		void Dispatch(std::function<bool(T&)> handler)
		{
			if (m_Event->Handled) return;

			static const type_info& class_type_info = typeid(T);

			if (typeid(*m_Event) == class_type_info) {
				m_Event->Handled |= handler(static_cast<T&>(*m_Event));
			}
		}

	private:
		Shared<BaseEvent> m_Event;
	};

}