#pragma once
#include "Core.h"
#include <iostream>
//#include <GLFW/glfw3.h>
#include "De-serialize/GameObject.h"
#include "Logging/Logging.h"
#include "Events/Event.h"
#include "Window.h"
#include "Duck/LayerStack.h"
#include "Duck/Events/ApplicationEvent.h"
#include "Duck/ImGui/ImGuiLayer.h"

namespace Duck {
	class DUCK_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		
		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

 //GLFWwindow* window;