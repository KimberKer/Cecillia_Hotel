
#include "Debug.h"
#include "Physics.h"  // Include the physics header to access PhysicsSystemSimulation
#include <windows.h>  // For Win32 console
#include <iostream>   // For console output
#include <string>

// Global variable for FPS calculation
int frameCount = 0;
double accumulatedTime = 0.0;

// Function to handle mouse movement
void mouse_position_callback(GLFWwindow* window, double xpos, double ypos) {
    std::cout << "Mouse X: " << xpos << ", Mouse Y: " << ypos << std::endl;
}

void InitializeDebug(GLFWwindow* window) {
    // Initialize Win32 console
    AllocConsole();

    // Set the mouse position callback
    glfwSetCursorPosCallback(window, mouse_position_callback);
}

void UpdateDebug(double deltaTime) {
    // Calculate the FPS
    frameCount++;
    accumulatedTime += deltaTime;

    // This is to test the exception handling 
    //throw std::runtime_error(std::string("Error in file ") + __FILE__ + " on line " + std::to_string(__LINE__));
    
    // Simulate the physics system
    double physicsStartTime = glfwGetTime();
    PhysicsSystemSimulation();  // Call the physics simulation
    double physicsEndTime = glfwGetTime();
    double physicsDuration = physicsEndTime - physicsStartTime;

    // Calculate the percentage of frame time by the physics system
    double physicsPercentage = (physicsDuration / deltaTime) * 100;

    //Debug info
    if (accumulatedTime >= 1.0) {
        std::cout << "FPS: " << frameCount << std::endl;
        std::cout << "Physics system used " << physicsPercentage << "% of total game loop time" << std::endl;
        frameCount = 0;
        accumulatedTime = 0.0;
    }
}

void CleanupDebug() {
    FreeConsole(); // Release the Win32 console
}
