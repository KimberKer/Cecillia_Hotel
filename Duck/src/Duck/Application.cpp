
// Headers for memory leak detection
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>

#include <fstream>
#include <exception>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "Application.h"
#include "Physics.h"
#include "Debug.h"

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

        // Initialize debugging utilities
        InitializeDebug(window);
    }

    Application::~Application() {
        CleanupDebug(); // Cleanup debugging utilities
    }

    void Application::Run() {
        // Enable memory leak detection
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

        double lastFrameTime = glfwGetTime();

        // Surround the game loop with try-catch for crash logging
        try {
            // Loop until the user closes the window
            while (!glfwWindowShouldClose(window)) {
                // Calculate delta time
                double currentFrameTime = glfwGetTime();
                double deltaTime = currentFrameTime - lastFrameTime;
                lastFrameTime = currentFrameTime;

                BeginProfile("Physics");
                // Call the physics simulation
                PhysicsSystemSimulation();
                EndProfile("Physics");

                // Update debugging utilities
                UpdateDebug(deltaTime);

                // Render here (you can put your OpenGL drawing code here)

                // Swap front and back buffers
                glfwSwapBuffers(window);

                // Poll for and process events
                glfwPollEvents();
            }
        }
        catch (const std::exception& e) 
        {
            // Create a folder for crash logs if it doesn't exist
            std::string crashLogsDir = "CrashLogs";

            // Generate the filename based on current timestamp
            auto timeNow = std::time(nullptr);
            std::ostringstream oss;
            oss << std::put_time(std::localtime(&timeNow), "/CrashLog %d-%m-%y.txt");
            std::string crashLogFileName = crashLogsDir + oss.str();

            // Write the exception message to crash log
            std::ofstream crashLog(crashLogFileName, std::ios::out);
            crashLog << "Crash with message: " << e.what() << std::endl;
            crashLog.close();

            // Re-throw the exception to allow for external handling or just terminate the program
            throw;
        }

        // Terminate GLFW
        glfwTerminate();
        return;
    }
}

