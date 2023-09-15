
#include "Debug.h"
#include "Physics.h"  
#include <iostream>   // For console output
#include <string>
#include <map>

// Global variable for FPS calculation
int frameCount = 0;
double accumulatedTime = 0.0;

// Map to store the start times of profiled regions
std::map<std::string, double> profileStartTimes;


// Function to handle mouse movement
void mouse_position_callback(GLFWwindow* window, double xpos, double ypos) 
{
    std::cout << "Mouse X: " << xpos << ", Mouse Y: " << ypos << std::endl;
}

void InitializeDebug(GLFWwindow* window) 
{
    // Set the mouse position callback
    glfwSetCursorPosCallback(window, mouse_position_callback);
}

void BeginProfile(const std::string& regionName) 
{
    profileStartTimes[regionName] = glfwGetTime();
}

void EndProfile(const std::string& regionName) 
{
    double endTime = glfwGetTime();
    double duration = endTime - profileStartTimes[regionName];
    profileStartTimes[regionName] = duration;
}

void UpdateDebug(double deltaTime) 
{
    // Calculate the FPS
    frameCount++;
    accumulatedTime += deltaTime;

    // This is to test the exception handling 
    //throw std::runtime_error(std::string("Error in file ") + __FILE__ + " on line " + std::to_string(__LINE__));

    // Calculate the percentage of frame time by the physics system
    double physicsPercentage = (profileStartTimes["Physics"] / deltaTime) * 100;

    //Debug info
    if (accumulatedTime >= 1.0f) 
    {
        std::cout << "FPS: " << frameCount << std::endl;
        std::cout << "Physics system used " << physicsPercentage << "% of total game loop time" << std::endl;
        frameCount = 0;
        accumulatedTime = 0.0;
    }
}

void CleanupDebug() 
{
}
