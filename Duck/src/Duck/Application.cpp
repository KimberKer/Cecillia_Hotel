#include "duckpch.h"
#include "Application.h"
#include "Time.h"
#include "Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

GameObject player;
bool loadFiles = false;

// Function to handle errors
void error_callback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}

namespace Duck {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

        //// Initialize GLFW
        //if (!glfwInit()) {
        //    std::cerr << "Failed to initialize GLFW" << std::endl;
        //    return;
        //}

        //// Set the GLFW error callback
        //glfwSetErrorCallback(error_callback);

        //// Create a GLFW window and OpenGL context
        //window = glfwCreateWindow(800, 800, "Cecillia's Hotel", NULL, NULL);
        //if (!window) { 
        //    std::cerr << "Failed to create GLFW window" << std::endl;
        //    glfwTerminate();
        //    return;
        //}

        //// Make the window's context current
        //glfwMakeContextCurrent(window);
	}

	Application::~Application() {

	}

    void Application::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        
        //HZ_CORE_TRACE("{0}", e);
    }

	void Application::Run() {
        while (m_Running) {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }

        // Loop until the user closes the window
        //while (!glfwWindowShouldClose(window)) {
        //    // Render here (you can put your OpenGL drawing code here)
        //    Time run_time;
        //    double delta_time = run_time.get_elapsed_time();
        //    //std::cout << "Elapsed Time: " << delta_time << std::endl;

        //    // Swap front and back buffers
        //    glfwSwapBuffers(window);

        //    // Poll for and process events
        //    glfwPollEvents();

        //    // Load Game Objects
        //    if (!loadFiles) {
        //        // Load player data
        //        player.loadPlayerData();
        //        loadFiles = true; // Set the flag to true to indicate data has been loaded

        //        consoleLogger.Log("All Game Object Loaded!", LogLevel::INFO);
        //        fileLogger.Log("All Game Object Loaded!", LogLevel::DEBUG);
        //    }
        //}

        //// Terminate GLFW
        //glfwTerminate();

	}

    bool Application::OnWindowClose(WindowCloseEvent& e) {
        m_Running = false;
        return true;
    }
}