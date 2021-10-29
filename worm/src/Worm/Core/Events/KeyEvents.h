#pragma once

#include "Event.h"
#include "Codes.h"

namespace Worm {
	
	class KeyEvent
	{
	public:
		inline KeyCode GetKeyCode() const { return m_Key; }
	protected:
		KeyEvent(KeyCode key) : m_Key(key) {}

		KeyCode m_Key;
	};

	class KeyPressedEvent : public KeyEvent, public Event<EventType::KeyPressed>
	{
	public:
		KeyPressedEvent(KeyCode key, ModifierKey mods, bool repeated = false) : KeyEvent(key), m_Mods(mods), m_Repeated(repeated) {}

		virtual const std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_Key << (m_Repeated ? "Repeater" : "");
			return ss.str();
		}
		
		inline ModifierKey GetModifiers() const { return m_Mods; }
		inline bool IsRepeated() const { return m_Repeated; }
	private:
		ModifierKey m_Mods;
		bool m_Repeated;
	};

	class KeyReleasedEvent : public KeyEvent, public Event<EventType::KeyReleased>
	{
	public:
		KeyReleasedEvent(KeyCode key, ModifierKey mods) : KeyEvent(key), m_Mods(mods) {}

		virtual const std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleased: " << m_Key;
			return ss.str();
		}

		inline ModifierKey GetModifiers() const { return m_Mods; }
	private:
		ModifierKey m_Mods;
	};

	class KeyTypedEvent :public Event<EventType::KeyTyped>
	{
	public:
		KeyTypedEvent(unsigned int unicodeChar, ModifierKey mods) : m_UnicodeChar(unicodeChar), m_Mods(mods) {}

		virtual const std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTyped: " << (char) m_UnicodeChar;
			return ss.str();
		}

		inline unsigned int GetUnicodeChar() const { return m_UnicodeChar; }
		inline ModifierKey GetModifiers() const { return m_Mods; }
	private:
		unsigned int m_UnicodeChar;
		ModifierKey m_Mods;
	};
}