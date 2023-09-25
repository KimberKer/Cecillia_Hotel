#include "Debug.h"
#include "PhysicsManager.h"  
#include <iostream>   // For console output
#include <iomanip>
#include <string>
#include <map>
//#include "duckpch.h"

namespace Duck {
    // This flag is to check whether the user has been informed about the debug commands
    bool isPromptDisplayed = false;

    // Static instance initialization
    Debug* Debug::debugInstance = nullptr;

    // Constructor initializing default values
    Debug::Debug() : frameCount(0), accumulateTime(0.0) {}

    // Destructor
    Debug::~Debug() {}

    // Singleton pattern's method to get or create the instance
    Debug* Debug::GetInstance()
    {
        // Create a new instance if one doesn't already exist
        if (!debugInstance)
        {
            debugInstance = new Debug();
            if (!debugInstance) {
                // Error handling if memory allocation fails
                throw std::runtime_error(std::string("Error in file ") + __FILE__ + " on line " + std::to_string(__LINE__));
            }
        }
        return debugInstance;
    }

    // Singleton pattern's method to destroy the instance
    void Debug::DestroyInstance()
    {
        delete debugInstance;
        debugInstance = nullptr;
    }

    // Begin profiling a system
    void Debug::BeginSystemProfile(const std::string& systemName)
    {
        // Store the start time for the given system
        systemProfileStartTime[systemName] = glfwGetTime();
    }

    // End profiling a system and store its duration
    double Debug::EndSystemProfile(const std::string& systemName)
    {
        double endTime = glfwGetTime();
        double duration = endTime - systemProfileStartTime[systemName];
        systemProfileDuration[systemName] = duration;
        return duration;
    }

    // Get the duration of the profiling for a system
    double Debug::GetSystemDuration(const std::string& systemName)
    {
        if (systemProfileDuration.find(systemName) != systemProfileDuration.end())
        {
            return systemProfileDuration[systemName];
        }
        else
        {
            // Handle errors if system duration data is not found
            throw std::runtime_error(std::string("Error in file ") + __FILE__ + " on line " + std::to_string(__LINE__));
            return -1;
        }
    }

    // Toggle FPS debug state
    void Debug::ToggleFPSDebug()
    {
        if (!(debugState & DEBUG_FPS_ACTIVE))
        {
            debugState |= DEBUG_FPS_ACTIVE;
        }
        else
        {
            debugState &= ~DEBUG_FPS_ACTIVE;
        }
    }

    // Toggle system info debug state
    void Debug::ToggleSystemInfoDebug()
    {
        if (!(debugState & DEBUG_SYS_ACTIVE))
        {
            debugState |= DEBUG_SYS_ACTIVE;
        }
        else
        {
            debugState &= ~DEBUG_SYS_ACTIVE;
        }
    }

    // Toggle mouse position debug state
    void Debug::ToggleMousePosDebug(GLFWwindow* window)
    {
        if (!(debugState & DEBUG_MOUSE_ACTIVE))
        {
            debugState |= DEBUG_MOUSE_ACTIVE;
        }
        else
        {
            debugState &= ~DEBUG_MOUSE_ACTIVE;
        }
    }

    // Toggle physics debug state
    void Debug::TogglePhysicsDebug()
    {
        if (!(debugState & DEBUG_PHYSICS_ACTIVE))
        {
            debugState |= DEBUG_PHYSICS_ACTIVE;
        }
        else
        {
            debugState &= ~DEBUG_PHYSICS_ACTIVE;
        }
    }

    // Handle debug input based on key presses
    void Debug::HandleDebugInput(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
        {
            // Check for the backtick key, this key clears out the console
            if (key == GLFW_KEY_GRAVE_ACCENT)
            {
                system("cls");  // Clear command for Windows
                isPromptDisplayed = false;
            }

            // Toggle specific debug states based on key presses
            if (key == GLFW_KEY_F1)     // F1 key for FPS debug
            {
                debugInstance->ToggleFPSDebug();
                std::cout << "FPS Debug: " << (debugInstance->debugState & DEBUG_FPS_ACTIVE ? "On" : "Off") << std::endl;
            }
            else if (key == GLFW_KEY_F2)    // F2 key for system info debug
            {
                debugInstance->ToggleSystemInfoDebug();
                std::cout << "System Info Debug: " << (debugInstance->debugState & DEBUG_SYS_ACTIVE ? "On" : "Off") << std::endl;
            }
            else if (key == GLFW_KEY_F3)	// F3 key for mouse position debug
            {
                debugInstance->ToggleMousePosDebug(window);
                std::cout << "Mouse Position Debug: " << (debugInstance->debugState & DEBUG_MOUSE_ACTIVE ? "On" : "Off") << std::endl;
            }
            else if (key == GLFW_KEY_F4)   // F4 key for physics debug
            {
                debugInstance->TogglePhysicsDebug();
                std::cout << "Physics Debug: " << (debugInstance->debugState & DEBUG_PHYSICS_ACTIVE ? "On" : "Off") << std::endl;
            }
        }
    }

    // Update function that shows debug information based on the state
    void Debug::Update(double deltaTime, GLFWwindow* window)
    {
        frameCount++;
        accumulateTime += deltaTime;

        // Limit the frame count to 60
        if (frameCount > 60)
        {
            frameCount = 60;
        }

        // Test for crash logging
        //throw std::runtime_error(std::string("Error in file ") + __FILE__ + " on line " + std::to_string(__LINE__));

        // Check if the user has been informed about the debug commands
        if (!isPromptDisplayed)
        {
            std::cout << "Press F1 to debug FPS" << std::endl;
            std::cout << "Press F2 to debug system" << std::endl;
            std::cout << "Press F3 to debug Mouse position" << std::endl;
            std::cout << "Press F4 to debug Physics" << std::endl;
            std::cout << "Press ` clear console" << std::endl << std::endl;
            isPromptDisplayed = true;
        }

        // Check if enough time has passed to show debug information
        if (accumulateTime >= 1.0f)
        {
            // FPS debug info
            if (debugState & DEBUG_FPS_ACTIVE)
            {
                std::cout << "FPS: " << std::fixed << std::setprecision(2) << frameCount << std::endl;
            }

            // Mouse position debug info
            if (debugState & DEBUG_MOUSE_ACTIVE)
            {
                double mouseX, mouseY;
                glfwGetCursorPos(window, &mouseX, &mouseY);
                std::cout << "Mouse X: " << mouseX << ", Mouse Y: " << mouseY << std::endl;
            }

            // System info debug info
            if (debugState & DEBUG_SYS_ACTIVE)
            {
                for (const auto& pair : systemProfileDuration)
                {
                    // Calculate the percentage of time spent on each system
                    double systemPercentage = (pair.second / deltaTime) * 100;
                    std::cout << pair.first << " system used " << systemPercentage << "% of total game loop time" << std::endl;
                }
            }

            // Physics debug info
            if (debugState & DEBUG_PHYSICS_ACTIVE)
            {
                PhysicsManager* physicsManager = PhysicsManager::GetInstance();
                for (const auto& obj : physicsManager->GetObjects())
                {
                    std::cout << "Object Position: X=" << obj.GetX() << ", Y=" << obj.GetY() << std::endl;
                }
            }

            // Flush the output buffer to ensure all debug messages are shown
            std::cout << std::flush;

            // Reset counters
            frameCount = 0;
            accumulateTime = 0.0;
        }
    }
}