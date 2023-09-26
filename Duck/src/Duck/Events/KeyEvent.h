#pragma once
#include "Event.h"
#include "../KeyCodes.h"
#include <sstream>

namespace Duck {
	// Base class for keyboard-related events
	class KeyEvent : public Event {
	public:
		// Getter function for the key code
		inline KeyCode GetKeyCode() const { return m_KeyCode; }

		// Define event categories for keyboard and input
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		// Constructor to initialize with a key code
		KeyEvent(int keycode) : m_KeyCode(keycode) {}

		KeyCode m_KeyCode;
	};

	// Event for a key press
	class KeyPressedEvent : public KeyEvent {
	public:
		// Constructor to initialize with a key code and repeat count
		KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		// Getter function for the repeat count
		inline int GetRepeatCount() const { return m_RepeatCount; }

		// String representation of the event
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_RepeatCount << ")";
			return ss.str();
		}

		// Define the event type
		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};

	// Event for a key release
	class KeyReleasedEvent : public KeyEvent {
	public:
		// Constructor to initialize with a key code
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

		// String representation of the event
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		// Define the event type
		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}
