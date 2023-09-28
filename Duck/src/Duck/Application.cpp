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
//#include "Audio/Audio.h"
#include "Debug.h"
#include "CoreManager.h"

//Flags
const unsigned int	FLAG_ACTIVE = 0x00000001;
const unsigned int	FLAG_VISIBLE = 0x00000002;
const unsigned int	FLAG_NON_COLLIDABLE = 0x00000004;

//Collision flags
const unsigned int	COLLISION_LEFT = 0x00000001;	//0001
const unsigned int	COLLISION_RIGHT = 0x00000002;	//0010
const unsigned int	COLLISION_TOP = 0x00000004;	//0100
const unsigned int	COLLISION_BOTTOM = 0x00000008;	//1000

//window
float const         WINDOW_COL = 10;
float const         WINDOW_ROW = 10;

const float         PLAYER_VELOCITY = 5.f;

bool                loadFiles = false;
bool                showImGuiWindow = false;


// Function to handle errors
void error_callback(int error, const char* description) {
	std::cerr << "Error: " << description << std::endl;
}

namespace Duck {
	Application* Application::s_Instance = nullptr;
	CoreManager* coreManager = CoreManager::GetInstance();
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
	Application::Application() {

		DUCK_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;


		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));


		m_Graphics = std::unique_ptr<Graphics>(new Graphics);

		m_Graphics->SetGridSize(10);
		//m_obj = std::unique_ptr<GameObject>(new GameObject());

		m_CharacterTexture = Shader::LoadTexture("../images/Character1.png");
		m_BackgroundTexture = Shader::LoadTexture("../images/FloorTile1.png");


		//TESTING AUDIO
		m_Audio = std::shared_ptr<Audio>(new Audio);
		std::cout << "Create SoundInfo\n";
		m_SoundInfo = std::shared_ptr<SoundInfo>(new SoundInfo("test", "../Duck/src/Duck/Audio/Sfx/SCI-FI.wav"));
		m_Audio->init();
		std::cout << "Load sound\n";
		m_Audio->loadSound(m_SoundInfo);

		coreManager->Init(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}






	Application::~Application() {
		coreManager->DestroyInstance();
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		//DUCK_CORE_INFO("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled) {
				break;
			}
		}

		if (e.GetEventType() == EventType::KeyPressed) {
			KeyPressedEvent& keyEvent = dynamic_cast<KeyPressedEvent&>(e);
			if (keyEvent.GetKeyCode() == Key::A) {
				showImGuiWindow = !showImGuiWindow; // Toggle the window's visibility
			}

			//Gameobject changing state
			switch (keyEvent.GetKeyCode()) {
				//GameObj go LEFT
			case Key::A:
				m_obj.SetState(STATE_GOING_LEFT);
				break;
			case Key::D:
				m_obj.SetState(STATE_GOING_RIGHT);
				break;
			case Key::W:
				m_obj.SetState(STATE_GOING_UP);
				break;
			case Key::S:
				m_obj.SetState(STATE_GOING_DOWN);
				break;
			default:
				m_obj.SetState(STATE_NONE);
				break;
			
			}
		}
		else if (e.GetEventType() == EventType::KeyReleased) {
			KeyReleasedEvent& keyEvent = dynamic_cast<KeyReleasedEvent&>(e);
			// Reset the velocity when the 'D' key is released
			switch (keyEvent.GetKeyCode()) {
				//GameObj go LEFT
			case Key::A:
				m_obj.SetState(STATE_NONE);
				break;
			case Key::D:
				m_obj.SetState(STATE_NONE);
				break;
			case Key::W:
				m_obj.SetState(STATE_NONE);
				break;
			case Key::S:
				m_obj.SetState(STATE_NONE);
				break;

			}
		}
	}
	void Application::Run() {
		// Enable memory leak detection
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		Time runtime;

		try {
			while (m_Running) {
				/* glClearColor(1, 0, 1, 1);
				 glClear(GL_COLOR_BUFFER_BIT)*/
				runtime.update();
				m_Audio->update();


				//object
				switch (m_obj.getState()) {
				case STATE_GOING_LEFT:
					m_obj.SetVelocityX(-PLAYER_VELOCITY);
					break;
				case STATE_GOING_RIGHT:
					m_obj.SetVelocityX(PLAYER_VELOCITY);
					break;
				case STATE_GOING_DOWN:
					m_obj.SetVelocityY(PLAYER_VELOCITY);
					break;
				case STATE_GOING_UP:
					m_obj.SetVelocityY(-PLAYER_VELOCITY);
					break;
				case STATE_NONE:
					m_obj.SetVelocityX(0);
					m_obj.SetVelocityY(0);
					break;
				}


				runtime.update(); // Call this at the beginning of each frame

				float dt = runtime.getDeltaTime(); // Get delta time in seconds

				m_obj.SetPositionX(m_obj.getVelocityX() * dt + m_obj.getX());
				m_obj.SetPositionY(m_obj.getVelocityY() * dt + m_obj.getY());                                                                                                     /////

				RenderCommand::SetClearColor({ 0.2, 0.2, 0.2, 1 });
				RenderCommand::Clear();

				// Would be used for cameras
				Renderer::BeginScene();

				Debug::GetInstance()->BeginSystemProfile("Graphics");
				// Would be used for cameras
				Renderer::BeginScene();


				MathLib::Vector2D obj2(5.0, 5.0);
				AABB windowAABB = aabb.ConvertToAABB(0, 0, 10 * 1, 10 * 1);
				AABB playerAABB = aabb.ConvertToAABB(m_obj.getX(), m_obj.getY(), 0.9f, 0.9f);
				AABB player2AABB = aabb.ConvertToAABB(obj2.x, obj2.y, 1.f, 1.f);

				if (m_phy.CollisionIntersection_RectRect(playerAABB, { m_obj.getVelocityX(), m_obj.getVelocityY() }, player2AABB, { 0,0 })) {
					m_obj.SetPositionX(m_map.SnapToCellX(1.f, m_obj.getX()));
					m_obj.SetPositionY(m_map.SnapToCellY(1.f, m_obj.getY()));
					m_obj.SetVelocityX(0);
				}

				if (m_phy.IsOutOfBounds(windowAABB, playerAABB))
				{
					m_obj.SetPositionX(m_map.SnapToCellX(1.f, m_obj.getX())); // Adjust as needed
					m_obj.SetPositionY(m_map.SnapToCellY(1.f, m_obj.getY()));
					m_obj.SetVelocityX(0);
					m_obj.SetVelocityY(0);

				}

				m_Graphics->DrawBackground(m_BackgroundTexture);
				m_Graphics->ShowGrid();

				m_Graphics->DrawSquareObject((m_map.SnapToCellX(1.f, m_obj.getY())), (m_map.SnapToCellY(1.f, m_obj.getY())) , 2.0f, 45.0f, m_CharacterTexture, true);
				m_Graphics->DrawSquareObject(5.0f, 5.0f, 1.0f, 180.0f, m_CharacterTexture, true);
				m_Graphics->DrawSquareObject(8.0f, 8.0f, 0.5f, 0.0f, m_CharacterTexture, true);

	


				Debug::GetInstance()->EndSystemProfile("Graphics");

				for (Layer* layer : m_LayerStack) {
					layer->OnUpdate();
				}

				m_ImGuiLayer->Begin();
				if (showImGuiWindow) {
				for (Layer* layer : m_LayerStack) {
					layer->OnImGuiRender();
				}
				}


				m_ImGuiLayer->End();


				// Testing of variable watch
				std::string deltatime = std::to_string(runtime.getDeltaTime());
				Debug::GetInstance()->WatchVariable("DT", deltatime);
				

				m_Window->OnUpdate();


				Debug::GetInstance()->BeginSystemProfile("Audio");
				//KRISTY - testing audio manager
				m_Audio->playSound(m_SoundInfo);
				Debug::GetInstance()->EndSystemProfile("Audio");

				coreManager->Update(runtime.getDeltaTime(), static_cast<GLFWwindow*>(m_Window->GetNativeWindow()));

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
