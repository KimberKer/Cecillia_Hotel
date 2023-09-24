#include "Debug.h"
#include "Physics.h"  
#include <iostream>   // For console output
#include <iomanip>
#include <string>
#include <map>

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
    // If instance doesn't exist, create one
    if (!debugInstance)
    {
        debugInstance = new Debug();
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
        glfwSetCursorPosCallback(window, NULL);
        debugState &= ~DEBUG_MOUSE_ACTIVE;
    }
}

// Handle debug input based on key presses
void Debug::HandleDebugInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        // Check for the backtick key
        if (key == GLFW_KEY_GRAVE_ACCENT)
        {
            #ifdef _WIN32
            system("cls");
            isPromptDisplayed = false;
            #else
            system("clear");
            isPromptDisplayed = false;
            #endif
        }
        // Toggle specific debug states based on key presses
        if (key == GLFW_KEY_F1)
        {
            debugInstance->ToggleFPSDebug();
            std::cout << "FPS Debug: " << (debugInstance->debugState & DEBUG_FPS_ACTIVE ? "On" : "Off") << std::endl;
        }
        else if (key == GLFW_KEY_F2)
        {
            debugInstance->ToggleSystemInfoDebug();
            std::cout << "System Info Debug: " << (debugInstance->debugState & DEBUG_SYS_ACTIVE ? "On" : "Off") << std::endl;
        }
        else if (key == GLFW_KEY_F3)
        {
            debugInstance->ToggleMousePosDebug(window);
            std::cout << "Mouse Position Debug: " << (debugInstance->debugState & DEBUG_MOUSE_ACTIVE ? "On" : "Off") << std::endl;
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
        std::cout << "Press ` clear console" << std::endl << std::endl;
        isPromptDisplayed = true;
    }

    // Check if enough time has passed to show debug information
    if (accumulateTime >= 1.0f)
    {
        if (debugState & DEBUG_FPS_ACTIVE)
        {
            std::cout << "FPS: " << std::fixed << std::setprecision(2) << frameCount << std::endl;
        }
        if (debugState & DEBUG_MOUSE_ACTIVE)
        {
            double mouseX, mouseY;
            glfwGetCursorPos(window, &mouseX, &mouseY);
            std::cout << "Mouse X: " << mouseX << ", Mouse Y: " << mouseY << std::endl;
        }
        if (debugState & DEBUG_SYS_ACTIVE)
        {
            for (const auto& pair : systemProfileDuration)
            {
                double systemPercentage = (pair.second / deltaTime) * 100;
                std::cout << pair.first << " system used " << systemPercentage << "% of total game loop time" << std::endl;
            }
        }
        std::cout << std::flush;

        frameCount = 0;
        accumulateTime = 0.0;
    }
}

