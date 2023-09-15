#pragma once
#include <GLFW/glfw3.h>
#include <string>

// Initialize the debugging utilities
void InitializeDebug(GLFWwindow* window);

// Beginning wrapper for functions
void BeginProfile(const std::string& regionName);

// Ending wrapper for functions
void EndProfile(const std::string& regionName);

// Update the debugging utilities
void UpdateDebug(double);

// Cleanup the debugging utilities
void CleanupDebug();

