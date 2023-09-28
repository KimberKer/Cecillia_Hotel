#include "duckpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Duck//Log.h"
#include "Time.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Duck/stb_image.h"

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


GameObject player;
bool loadFiles = false;


namespace Duck {
    Application* Application::s_Instance = nullptr;
    CoreManager* coreManager = CoreManager::GetInstance();
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    

    Application::Application() {
        DUCK_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

        
        m_Graphics = std::unique_ptr<Graphics>(new Graphics);

        m_Graphics->SetGridSize(10);


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
	}

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* layer) {
        m_LayerStack.PushOverlay(layer);
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
    }

    void Application::Run() {
        // Enable memory leak detection
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

        Time runtime;

        try {
            while (m_Running) {
                runtime.update();
                m_Audio->update();
              
                ////////////////////////////////////////////////// MAHDI /////////////////////////////////////////////////////////////////
                /////                                                                                                                /////
                Debug::GetInstance()->BeginSystemProfile("Graphics");
                // Would be used for cameras
                Renderer::BeginScene();

                m_Graphics->DrawBackground(m_BackgroundTexture);
                m_Graphics->ShowGrid();

                m_Graphics->DrawSquareObject(1.0f, 1.0f, 2.0f, 45.0f, m_CharacterTexture, true);
                m_Graphics->DrawSquareObject(5.0f, 5.0f, 1.0f, 180.0f, m_CharacterTexture, true);
                m_Graphics->DrawSquareObject(8.0f, 8.0f, 0.5f, 0.0f, m_CharacterTexture, true);


                Renderer::EndScene();                
           
           
                Debug::GetInstance()->EndSystemProfile("Graphics");
                /////                                                                                                                /////
                ////////////////////////////////////////////////// MAHDI /////////////////////////////////////////////////////////////////

                for (Layer* layer : m_LayerStack) {
                    layer->OnUpdate();
                }

                m_Window->OnUpdate();
                //// Log Mouse Position to Console
                //auto [x, y] = Input::GetMousePosition();
                //DUCK_CORE_TRACE("{0}, {1}", x, y);

                ////////////////////////////////////////////////// ZIKRY /////////////////////////////////////////////////////////////////
                
                // Testing of variable watch
                std::string deltatime = std::to_string(runtime.getDeltaTime());              
                Debug::GetInstance()->WatchVariable("DT", deltatime);

                Debug::GetInstance()->BeginSystemProfile("Audio");
                //KRISTY - testing audio manager
                m_Audio->playSound(m_SoundInfo);
                Debug::GetInstance()->EndSystemProfile("Audio");

                coreManager->Update(runtime.getDeltaTime(), static_cast<GLFWwindow*>(m_Window->GetNativeWindow()));

                ////////////////////////////////////////////////// ZIKRY /////////////////////////////////////////////////////////////////

            }
        }
        catch (const std::exception& e)
        {
            ////////////////////////////////////////////////// ZIKRY /////////////////////////////////////////////////////////////////
            
            // Define the directory for crash logs
            const char* crashLogsDir = "CrashLogs/";

            // Check if the directory exists, if not, create it
            if (GetFileAttributesA(crashLogsDir) == INVALID_FILE_ATTRIBUTES)
            {
                CreateDirectoryA(crashLogsDir, NULL);
            }

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