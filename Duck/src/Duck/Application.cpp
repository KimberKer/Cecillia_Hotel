#include "duckpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Map/Map.h"
#include "Duck/Log.h"
#include "Time.h"
#include "Physics/collision.h"
#include "Duck/Graphics/Graphics.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Duck/stb_image.h"
#include <GLFW/glfw3.h>

// Headers for memory leak detection
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>

#include "Input.h"
#include <fstream>
#include <exception>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <Windows.h>
#include "Application.h"
#include "Physics/PhysicsManager.h"
#include "Debug.h"
#include "CoreManager.h"



namespace Duck {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	//GameObject* Application::p_object = nullptr;
	//GameObject* Application::p_player = nullptr;
	//GameObject* Application::m_gameobjList = nullptr;
	CoreManager* coreManager = CoreManager::GetInstance();
	MapDataHandler Object;


    Application::Application() {
        DUCK_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		
		//m_ImGuiLayer = new ImGuiLayer();
		//PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() {
		coreManager->DestroyInstance();
		//m_map->FreeMapData();
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled) {
				break;
			}
		}

		////setting events based on inputs
		//if (e.GetEventType() == EventType::KeyPressed) {
		//	KeyPressedEvent& keyEvent = dynamic_cast<KeyPressedEvent&>(e);
		//	if (keyEvent.GetKeyCode() == Key::I) {
		//		showImGuiWindow = !showImGuiWindow; // Toggle the window's visibility
		//	}
		//	else if (keyEvent.GetKeyCode() == Key::G) {
		//		showGrid = !showGrid;
		//	}
		//	else if (keyEvent.GetKeyCode() == Key::B) {
		//		showBB = !showBB;
		//	}
		//	else if (keyEvent.GetKeyCode() == Key::R) {
		//		PlayerOrientation = (PlayerOrientation + 90) % 360;
		//	}
		//	else if (keyEvent.GetKeyCode() == Key::Q) {
		//		m_Running = false;
		//	}
		//}

		////Gameobject changing state

		//if (e.GetEventType() == EventType::KeyPressed) {
		//	KeyPressedEvent& keyEvent = dynamic_cast<KeyPressedEvent&>(e);
		//	switch (keyEvent.GetKeyCode()) {
		//		//GameObj go LEFT
		//	case Key::A:
		//		p_player->SetState(STATE_GOING_LEFT);
		//		break;
		//	case Key::D:
		//		p_player->SetState(STATE_GOING_RIGHT);
		//		break;
		//	case Key::W:
		//		p_player->SetState(STATE_GOING_UP);
		//		break;
		//	case Key::S:
		//		p_player->SetState(STATE_GOING_DOWN);
		//		break;
		//	default:
		//		p_player->SetState(STATE_NONE);
		//		break;
		//	}
		//}
		//else if (e.GetEventType() == EventType::KeyReleased) {
		//	KeyReleasedEvent& keyEvent = dynamic_cast<KeyReleasedEvent&>(e);
		//	// Reset the velocity when key is released
		//	switch (keyEvent.GetKeyCode()) {
		//	case Key::A:
		//	case Key::D:
		//	case Key::W:
		//	case Key::S:
		//		p_player->SetState(STATE_NONE);
		//	default:
		//		p_player->SetState(STATE_NONE);
		//		break;
		//	}
		//}
	}
	void Application::Run() {
		// Enable memory leak detection
		//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		try {
			while (m_Running) {

				for (Layer* layer : m_LayerStack) {
					layer->OnUpdate();
				}

				/*m_ImGuiLayer->Begin();
				if (showImGuiWindow) {
					for (Layer* layer : m_LayerStack) {
						layer->OnImGuiRender();
					}
				}
				m_ImGuiLayer->End();*/
				m_Window->OnUpdate();
				

			//	coreManager->Update(runtime.getDeltaTime(), static_cast<GLFWwindow*>(m_Window->GetNativeWindow()));
			}
		}
		catch (const std::exception& e)
		{
			////////////////////////////////////////////////// ZIKRY /////////////////////////////////////////////////////////////////

			// Define the directory for crash logs
			const char* crashLogsDir = "CrashLogs/";

			// Generate the filename based on current timestamp
			struct tm newtime;
			time_t now = time(0);
			localtime_s(&newtime, &now);     // fills in the newtime struct with the date if not error
			std::ostringstream oss;
			oss << std::put_time(&newtime, "/Crashlog [%d-%m-%Y].txt");   // format the date and time for the crashlog filename
			std::string crashLogFileName = std::string(crashLogsDir) + oss.str();

			// Write the exception message to crash log
			std::ofstream crashLog(crashLogFileName, std::ios::out);
			crashLog << "Crash with message: " << e.what() << std::endl;
			crashLog.close();

			// Re-throw the exception to allow for external handling or just terminate the program
			throw;

			////////////////////////////////////////////////// ZIKRY /////////////////////////////////////////////////////////////////
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {

		m_Running = false;
		return true;

	}
}
