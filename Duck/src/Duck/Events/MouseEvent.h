#pragma once
#include "Event.h"
#include "../MouseCodes.h"

namespace Duck {

	// Event for mouse movement
	class DUCK_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(const float x, const float y)
			: m_MouseX(x), m_MouseY(y) {}

		// Getter functions for mouse coordinates
		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		// String representation of the event
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		// Define the event type and categories
		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY;
	};

	// Event for mouse scrolling
	class DUCK_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		// Getter functions for scroll offsets
		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		// String representation of the event
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		// Define the event type and categories
		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffset, m_YOffset;
	};

	// Base class for mouse button events
	class DUCK_API MouseButtonEvent : public Event {
	public:
		// Getter function for the mouse button code
		MouseCode GetMouseButton() const { return m_Button; }

		// Define event categories for mouse and input
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

	protected:
		MouseButtonEvent(const MouseCode button)
			: m_Button(button) {}

		MouseCode m_Button;
	};

	// Event for mouse button press
	class DUCK_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const MouseCode button)
			: MouseButtonEvent(button) {}

		// String representation of the event
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		// Define the event type
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	// Event for mouse button release
	class DUCK_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		// String representation of the event
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		// Define the event type
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}
