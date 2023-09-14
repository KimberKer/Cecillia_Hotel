#include "Debug.h"
#include <windows.h>  // For Win32 console
#include <iostream>   // For console output
#include <chrono>     // For FPS calculation

// Global variables for FPS calculation
auto lastTime = std::chrono::high_resolution_clock::now();
int frameCount = 0;

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

void UpdateDebug() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    frameCount++;

    if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastTime).count() >= 1.0) {
        std::cout << "FPS: " << frameCount << std::endl;
        frameCount = 0;
        lastTime = currentTime;
    }
}

void CleanupDebug() {
    FreeConsole(); // Release the Win32 console
}
