#pragma once


#include "Duck/Layer.h"

#include "Duck/Events/ApplicationEvent.h"
#include "Duck/Events/KeyEvent.h"
#include "Duck/Events/MouseEvent.h"

namespace Duck {
	class DUCK_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnImGuiRender() override;

		void OnEvent(Event& event);

		void Begin();
		void End();

	private:
		float m_time = 0.0f;
	};
}