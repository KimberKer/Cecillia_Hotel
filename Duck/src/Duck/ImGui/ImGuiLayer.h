#pragma once


#include "Duck/Layer.h"

#include "Duck/Events/ApplicationEvent.h"
#include "Duck/Events/KeyEvent.h"
#include "Duck/Events/MouseEvent.h"

namespace Duck {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

	private:
		bool m_BlockEvents = true;
		float m_time = 0.0f;
	};
}