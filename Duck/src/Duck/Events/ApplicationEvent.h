//---------------------------------------------------------
// File:    ApplicationEvent.h
//authors:	Kimber Ker Soon Kiat
// email:	s.ker\@digipen.edu
// 
//
// Brief:     Contains the declarations related to application events
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once
#include "duckpch.h"
#include "Event.h"

namespace Duck {
	// Event for window resize
	class WindowResizeEvent : public Event {
	public:
		// Constructor to initialize with width and height
		WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

		// Getter functions for width and height
		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		// String representation of the event
		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		// Define event type and category
		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_Width, m_Height;
	};

	// Event for window close
	class WindowCloseEvent : public Event {
	public:
		// Constructor
		WindowCloseEvent() {}

		// Define event type and category
		EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	// Event for application tick
	class AppTickEvent : public Event {
	public:
		// Constructor
		AppTickEvent() = default;

		// Define event type and category
		EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	// Event for application update
	class AppUpdateEvent : public Event {
	public:
		// Constructor
		AppUpdateEvent() = default;

		// Define event type and category
		EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	// Event for application render
	class AppRenderEvent : public Event {
	public:
		// Constructor
		AppRenderEvent() = default;

		// Define event type and category
		EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
