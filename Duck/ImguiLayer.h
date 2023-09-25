#pragma once

#include
#include "Duck/Layer.h"
#include "Duck/Events/KeyEvent.h"
#include "Duck/Events/MouseEvent.h"

namespace Duck {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();

		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnMouseButtonPressedEvent(GetMouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(GetMouseButtonReleasedEvent& e);
		bool OnMouseEvent(MouseMovedEvent& e);
		bool OnMouseScrollEvent(MouseScrolledEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		//bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizedEvent(OnWindowResizedEvent& e);

	private:
		float m_time = 0.0f;
	};
}