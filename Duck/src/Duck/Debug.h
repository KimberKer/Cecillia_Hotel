#pragma once
#include <GLFW/glfw3.h>

// Initialize the debugging utilities
void InitializeDebug(GLFWwindow* window);

// Update the debugging utilities (to be called in the main loop)
void UpdateDebug();

// Cleanup the debugging utilities (to be called on application termination)
void CleanupDebug();

