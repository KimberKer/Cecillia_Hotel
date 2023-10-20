#pragma once
#include "Core.h"
#include <iostream>
//#include <GLFW/glfw3.h>
#include "Audio/Audio.h"
#include "Duck/De-serialize/GameObject.h"
#include "Logging/Logging.h"
#include "Duck/Events/KeyEvent.h"
#include "Events/Event.h"
#include "ImGui/ImGuiLayer.h"
#include "Window.h"
#include "Duck/LayerStack.h"
#include "Duck/Events/ApplicationEvent.h"
#include "Duck/Graphics/Shader.h"
#include "Duck/Graphics/Buffer.h"
#include "Duck/Graphics/Vertex.h"
#include "Duck/Graphics/Renderer.h"
#include "Duck/Graphics/Graphics.h"
#include "Duck/De-serialize/GameObject.h"
#include "Duck/Map/map.h"
#include "Duck/Ghost/AI.h"
#include "Duck/Time.h"



namespace Duck {
	class DUCK_API Application {
	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline Window& GetWindow() { return *m_Window; }
		
		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


 //GLFWwindow* window;
 