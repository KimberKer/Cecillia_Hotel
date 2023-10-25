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


#include "Duck/Graphics/Shader.h"
#include "Duck/Graphics/Buffer.h"
#include "Duck/Graphics/Vertex.h"
#include "Duck/Graphics/Renderer.h"



namespace Duck {
	class Graphics;
	class SoundInfo;
	class Audio;
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
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

		void SetRunning(bool running) { m_Running = running; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<SoundInfo> m_SoundInfo;
		std::shared_ptr<Audio> m_Audio;
		std::shared_ptr<MapDataHandler> m_map;


		std::unique_ptr<Graphics> m_Graphics;

		uint32_t m_CharacterTexture;
		uint32_t m_BackgroundTexture, m_BackgroundTexture2;


	private:
		static Application* s_Instance;

		AABB aabb;
		PhysicsLib m_phy;
		std::vector<std::shared_ptr<GameObject>> objectlist;
		std::shared_ptr<GameObject> m_gameobjList;
		std::shared_ptr<GameObject> p_player;
		//static GameObject* p_object;


		unsigned const int CELL_SIZE = 1.f;




		const float         PLAYER_VELOCITY = 0.1f;

		bool                loadFiles = false;
		bool                showImGuiWindow = false;
		bool				showGrid = false;
		bool				showBB = false;

		int					PlayerOrientation = 0;
	};






	// To be defined in CLIENT
	Application* CreateApplication();
}


//GLFWwindow* window;
