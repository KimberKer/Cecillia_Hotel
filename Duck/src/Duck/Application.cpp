#include "duckpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Map/Map.h"
#include "Duck/Log.h"
#include "Time.h"
#include "Physics/collision.h"
#include "Physics/PhysicsManager.h"
#include "Duck/Graphics/Graphics.h"
#include "Duck/stb_image.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "Input.h"
#include <Windows.h>
#include "Debug.h"
#include "CoreManager.h"

// Headers for memory leak detection
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>

namespace Duck {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	//ecs
	Coordinator ecs;
	Time runtime;

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
	}

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
		m_map = std::shared_ptr<MapDataHandler>(new MapDataHandler);

		/*--------------------------------------
			ecs stuff - kristy
		--------------------------------------*/
		//init ecs
		ecs.Init();

		



		//getting information from the file.
		if (!m_map->GetMapData("map.txt")) { //--------------------need to be fix
			m_Running = false;
		}
		m_ImGuiLayer = new ImGuiLayer(m_map);
		PushOverlay(m_ImGuiLayer);

		m_Graphics = std::unique_ptr<Graphics>(new Graphics);
		m_CharacterTexture = Shader::LoadTexture("../images/Character1.png");
		m_BackgroundTexture = Shader::LoadTexture("../images/FloorTile1.png");
		m_BackgroundTexture2 = Shader::LoadTexture("../images/FloorTile2.png");

		//setting number of squares
		m_Graphics->SetGridSize(static_cast<int>(m_map->GetHeight()));


		//create a list of game objects
		numOfObjects = 0;
		//m_gameobjList = new GameObject[MAX_NUMBER_OF_OBJ];
		//m_map->printMapData();
		//creating the objects based on the map 

		for (int i{}; i < m_map->GetWidth(); i++) {
			for (int j{}; j < m_map->GetHeight(); j++) {
				if (numOfObjects < MAX_NUMBER_OF_OBJ) {
					int cellValue = m_map->GetCellValue(i, j);
					switch (cellValue) {
					case 0:
						break;
						//player
					case 1:
						objectlist.push_back(m_gameobjList->CreateObj(i, j, STATE_NONE, OBJ_PLAYER));
						numOfObjects++;
						break;
					case 2:
						objectlist.push_back(m_gameobjList->CreateObj(i, j, STATE_NONE, OBJ_OBJ));
						numOfObjects++;
						break;
					default:
						break;
					}

				}

			}
		}


		for (int i{}; i < objectlist.size(); i++) {
			if (objectlist[i]->getObj() == OBJ_PLAYER) {
				p_player = objectlist[i];
			}
		}

	}

	Application::~Application() {
		coreManager->DestroyInstance();
		m_map->FreeMapData();

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
	}

	void Application::Run() {
		// Enable memory leak detection
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		
		/*--------------------------------------
			ecs stuff - kristy
		--------------------------------------*/
		//register components
		ecs.RegisterComponent<Duck::AudioComponent>();


		//register systems -> init system
		auto audioSystem = ecs.RegisterSystem<AudioSystem>();
		{
			Signature signature;
			signature.set(ecs.GetComponentType<AudioComponent>());
			ecs.SetSystemSignature<AudioSystem>(signature);
		}
		audioSystem->init();


		//create entities
		Entity audio1 = ecs.CreateEntity();

		ecs.AddComponent<AudioComponent>(
			audio1,
			{ "oof", "../Duck/src/Duck/Audio/assets/oof.wav" }
		);

		try {
			while (m_Running) {
				/* glClearColor(1, 0, 1, 1);
				 glClear(GL_COLOR_BUFFER_BIT)*/
				runtime.update();
				
				/*--------------------------------------
					ecs stuff - kristy
				--------------------------------------*/
				//updating systems
				audioSystem->update();

				//object
				for (int i{}; i < objectlist.size(); i++) {
					switch (objectlist[i]->getState()) {
					case STATE_GOING_LEFT:
						objectlist[i]->SetVelocityX(-PLAYER_VELOCITY);
						break;
					case STATE_GOING_RIGHT:
						objectlist[i]->SetVelocityX(PLAYER_VELOCITY);
						break;
					case STATE_GOING_DOWN:
						objectlist[i]->SetVelocityY(PLAYER_VELOCITY);
						break;
					case STATE_GOING_UP:
						objectlist[i]->SetVelocityY(-PLAYER_VELOCITY);
						break;
					case STATE_NONE:
						objectlist[i]->SetVelocityX(0);
						objectlist[i]->SetVelocityY(0);
						break;
					}
				}


				runtime.update(); // Call this at the beginning of each frame

				float dt = static_cast<float>(runtime.getDeltaTime()); // Get delta time in seconds

				float newX = p_player->getVelocityX();
				newX += p_player->getVelocityX() * dt + p_player->getX();

				float newY = p_player->getVelocityY();
				newY += p_player->getVelocityY() * dt + p_player->getY();

				p_player->SetPositionX(newX);
				p_player->SetPositionY(newY);

				RenderCommand::SetClearColor({ 0.2, 0.2, 0.2, 1 });
				RenderCommand::Clear();

				// Would be used for cameras
				Renderer::BeginScene();

				Debug::GetInstance()->BeginSystemProfile("Graphics");
				// Would be used for cameras
				Renderer::BeginScene();




				//AABB example3AABB = aabb.ConvertToAABB(m_example3.getX(), m_example3.getY(), 1.f, 1.f);
				//AABB exampleAABB = aabb.ConvertToAABB(m_example.getX(), m_example.getY(), 1.f, 1.f);
				//AABB example2AABB = aabb.ConvertToAABB(m_example2.getX(), m_example2.getY(), 1.f, 1.f);

				//if (m_phy.CollisionIntersection_RectRect(playerAABB, { p_player->getVelocityX(), p_player->getVelocityY() }, example3AABB, { 0,0 }) ||
				//	(m_phy.CollisionIntersection_RectRect(playerAABB, {m_example.getVelocityX(), m_example.getVelocityY() }, exampleAABB, {0,0})) ||
				//	(m_phy.CollisionIntersection_RectRect(playerAABB, { m_example2.getVelocityX(), m_example2.getVelocityY() }, example2AABB, { 0,0 }))
				//	)
				//	 {
				//	p_player->SetPositionX(static_cast<float>(m_map.SnapToCellX(1, p_player->getX())));
				//	p_player->SetPositionY(static_cast<float>(m_map.SnapToCellY(1, p_player->getY())));
				//	p_player->SetVelocityX(0);
				//}

				AABB windowAABB = aabb.ConvertToAABB(0, 0, m_map->GetHeight(), m_map->GetWidth());
				AABB playerAABB = aabb.ConvertToAABB(p_player->getX(), p_player->getY(), CELL_SIZE, CELL_SIZE);


				if (m_phy.IsOutOfBounds(windowAABB, playerAABB))
				{
					p_player->SetPositionX(static_cast<float>(m_map->SnapToCellX(CELL_SIZE, p_player->getX()))); // Adjust as needed
					p_player->SetPositionY(static_cast<float>(m_map->SnapToCellY(CELL_SIZE, p_player->getY())));
					p_player->SetVelocityX(0);
					p_player->SetVelocityY(0);

				}

				//draw objects
				m_Graphics->DrawBackground(m_BackgroundTexture);
				if (showGrid) {
					m_Graphics->ShowGrid();
				}

				for (int i{}; i < objectlist.size(); i++) {
			
					if (objectlist[i]->getObj() == OBJ_OBJ) {
						AABB objectAABB = aabb.ConvertToAABB(objectlist[i]->getX(), objectlist[i]->getY(), CELL_SIZE, CELL_SIZE);

						if (m_phy.CollisionIntersection_RectRect(playerAABB, { p_player->getVelocityX(), p_player->getVelocityY() }, objectAABB, { objectlist[i]->getVelocityX(), objectlist[i]->getVelocityY() })) {
							p_player->SetPositionX(static_cast<float>(m_map->SnapToCellX(1, p_player->getX())));
							p_player->SetPositionY(static_cast<float>(m_map->SnapToCellY(1, p_player->getY())));
							p_player->SetVelocityX(0);
							p_player->SetVelocityY(0);
						}
						m_Graphics->DrawSquareObject(objectlist[i]->getX(), objectlist[i]->getY(), CELL_SIZE, (float)PlayerOrientation, m_BackgroundTexture2, showBB);

					}
				
				}
					
					
					//m_Graphics->DrawSquareObject(m_example.getX(), m_example.getY(), 1.0f, (float)PlayerOrientation, m_BackgroundTexture2, showBB);
					//m_Graphics->DrawSquareObject(p_object->getX(), p_object->getY(), CELL_SIZE, (float)PlayerOrientation, m_BackgroundTexture2, showBB);

				m_Graphics->DrawSquareObject(static_cast<float>((m_map->SnapToCellX(1, p_player->getX()))), static_cast<float>((m_map->SnapToCellY(1.f, p_player->getY()))), CELL_SIZE, (float)PlayerOrientation, m_CharacterTexture, showBB);
				m_Graphics->DrawSquareObject(5.0f, 5.0f, 1.0f, 0.0f, m_BackgroundTexture2, showBB);

				Debug::GetInstance()->EndSystemProfile("Graphics");

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
				
				//coreManager->Update(runtime.getDeltaTime(), static_cast<GLFWwindow*>(m_Window->GetNativeWindow()));
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
