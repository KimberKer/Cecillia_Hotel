#pragma once
#include "Core.h"
#include <iostream>
//#include <GLFW/glfw3.h>
#include "De-serialize/GameObject.h"
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
#include "Audio/Audio.h"

namespace Duck {
	class Graphics;
	class SoundInfo;
	class Audio;
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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<SoundInfo> m_SoundInfo;
		std::shared_ptr<Audio> m_Audio;

		std::unique_ptr<Graphics> m_Graphics;

		uint32_t m_CharacterTexture;
		uint32_t m_BackgroundTexture;


	private:
		static Application* s_Instance;
	};






	// To be defined in CLIENT
	Application* CreateApplication();
}


 //GLFWwindow* window;
 