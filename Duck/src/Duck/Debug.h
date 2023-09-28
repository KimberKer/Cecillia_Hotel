//---------------------------------------------------------
// file:	Debug.h
// authors:	muhammad zikry bin zakaria
// email:	muhammadzikry.b\@digipen.edu
//
// brief:	Contains the declaration of the Debug class for handling debugging and profiling in console.
//
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <map>

namespace Duck {
	class Debug
	{
	public:
		// Singleton pattern: Get the instance of the Debug class
		static Debug* GetInstance();

		// Singleton pattern: Destroy the instance of the Debug class
		static void DestroyInstance();

		// Handle user input to toggle different debug states
		static void HandleDebugInput(GLFWwindow* window, int key, int scancode, int action, int mods);

		// Update function to display debug information based on active debug states
		void Update(double deltaTime, GLFWwindow* window);

		// Start profiling a system's performance
		void BeginSystemProfile(const std::string& systemName);

		// End profiling a system's performance and store the duration
		double EndSystemProfile(const std::string& systemName);

		// Get the duration of the system's profiling
		double GetSystemDuration(const std::string& systemName);

		// Variable watching
		template <typename T>
		void WatchVariable(const std::string& name, const T& variable);

	private:
		int frameCount;
		double accumulateTime;

		// Variables for system profiling
		std::map<std::string, double> systemProfileStartTime;
		std::map<std::string, double> systemProfileDuration;

		// Variable watching
		std::map<std::string, std::string> watchedVariables;

		int debugState = DEBUG_NONE;

		// Debug flags
		enum DebugState
		{
			DEBUG_NONE = 0,
			DEBUG_FPS_ACTIVE = 1 << 0,
			DEBUG_SYS_ACTIVE = 1 << 1,
			DEBUG_MOUSE_ACTIVE = 1 << 2,
			DEBUG_PHYSICS_ACTIVE = 1 << 3,
			DEBUG_KEY_ACTIVE = 1 << 4,
			DEBUG_VARIABLE_ACTIVE = 1 << 5
		};

		// Toggle the FPS debug state on/off
		void ToggleFPSDebug();

		// Toggle the system information debug state on/off
		void ToggleSystemInfoDebug();

		// Toggle the mouse position debug state on/off
		void ToggleMousePosDebug(GLFWwindow* window);

		// Toggle the physics test debug state on/off
		void TogglePhysicsDebug();

		// Toggle key state debug info on/off
		void ToggleKeyStateDebug();

		// Toggle variable debug info on/off
		void ToggleVariableDebug();

		// Static instance to access the non-static members from the static function
		static Debug* debugInstance;

		Debug();
		~Debug();
	};
}

