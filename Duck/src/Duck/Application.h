#pragma once
#include "Core.h"
#include <iostream>
//#include <GLFW/glfw3.h>
#include "Duck/Audio/Audio.h"

#include "Duck/Platform/Windows/WindowsInput.h"
#include "KeyCodes.h"

#include "Duck/De-serialize/GameObject.h"

#include "Duck/ECS/Entity.h"

#include "Duck/Events/KeyEvent.h"
#include "Duck/Events/Event.h"

#include "Duck/ImGui/ImGuiLayer.h"

#include "Duck/Events/ApplicationEvent.h"

#include "Duck/Graphics/Shader.h"
#include "Duck/Graphics/Buffer.h"
#include "Duck/Graphics/Vertex.h"
#include "Duck/Graphics/Renderer.h"
#include "Duck/Graphics/Graphics.h"

#include "Duck/Map/map.h"
#include "Duck/Ghost/AI.h"
#include "Duck/Time.h"

#include "Logging/Logging.h"
#include "Window.h"
#include "Duck/LayerStack.h"




namespace Duck {
	class Graphics;
	class SoundInfo;
	class GameObject;

	class DUCK_API Application {
	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void ReadMapData(std::string filename);

		LayerStack GetLayerStack() const { return m_LayerStack; }
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

		void SetRunning(bool running) { m_Running = running; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		std::shared_ptr<SoundInfo> m_SoundInfo;
		//std::shared_ptr<Audio> m_Audio;
		std::shared_ptr<MapDataHandler> m_map;
		
		std::unique_ptr<Graphics> m_Graphics;
		float CamZoom;

		uint32_t m_CharacterTexture;
		uint32_t m_BackgroundTexture, m_BackgroundTexture2, m_InventorySlot, m_AnimatedTexture;


	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


//GLFWwindow* window;
