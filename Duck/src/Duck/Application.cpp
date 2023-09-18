#include "duckpch.h"
#include "Application.h"
#include "Time.h"
#include "Events/ApplicationEvent.h"

GameObject player;
bool loadFiles = false;

// Function to handle errors
void error_callback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}

namespace Duck {
	Application::Application() {
        // Initialize GLFW
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return;
        }

        // Set the GLFW error callback
        glfwSetErrorCallback(error_callback);

        // Create a GLFW window and OpenGL context
        window = glfwCreateWindow(800, 800, "Cecillia's Hotel", NULL, NULL);
        if (!window) { 
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }

        // Make the window's context current
        glfwMakeContextCurrent(window);
	}

	Application::~Application() {

	}

	void Application::Run() {
        // Create log sinks
        ConsoleSink consoleSink;    // For logging to the console
        FileSink fileSink;          // For logging to a file
        FileSink::FileSink();

        // Create loggers and configure log levels and sinks
        Logging consoleLogger(LogLevel::INFO);  // Set log level to INFO
        consoleLogger.AddSink(&consoleSink);    // Add console sink for real-time output

        Logging fileLogger(LogLevel::DEBUG);    // Set log level to DEBUG
        fileLogger.AddSink(&fileSink);          // Add file sink for log file

        /*WindowResizeEvent e(1280, 720);
        if (e.IsInCategory(EventCategoryApplication)) {
            consoleLogger.Log(e.ToString(), LogLevel::INFO);

        }
        if (e.IsInCategory(EventCategoryInput)) {
            consoleLogger.Log(e.ToString(), LogLevel::INFO);
        }

        while (true);*/

        // Loop until the user closes the window
        while (!glfwWindowShouldClose(window)) {
            // Render here (you can put your OpenGL drawing code here)
            Time run_time;
            double delta_time = run_time.get_elapsed_time();
            //std::cout << "Elapsed Time: " << delta_time << std::endl;

            // Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();

            // Load Game Objects
            if (!loadFiles) {
                // Load player data
                player.loadPlayerData();
                loadFiles = true; // Set the flag to true to indicate data has been loaded

                consoleLogger.Log("All Game Object Loaded!", LogLevel::INFO);
                fileLogger.Log("All Game Object Loaded!", LogLevel::DEBUG);
            }
        }

        // Terminate GLFW
        glfwTerminate();

	}
}