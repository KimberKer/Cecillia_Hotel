#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <map>


	class Debug
	{
	private:
		int frameCount;
		double accumulateTime;

		std::map<std::string, double> systemProfileStartTime;
		std::map<std::string, double> systemProfileDuration;
		
		int debugState = DEBUG_NONE;

		// Debug flags
		enum DebugState
		{
			DEBUG_NONE = 0,
			DEBUG_FPS_ACTIVE = 1 << 0,
			DEBUG_SYS_ACTIVE = 1 << 1,
			DEBUG_MOUSE_ACTIVE = 1 << 2,
			DEBUG_PHYSICS_ACTIVE = 1 << 3,
		};
		
		void ToggleFPSDebug();
		void ToggleSystemInfoDebug();
		void ToggleMousePosDebug(GLFWwindow* window);
		void TogglePhysicsDebug();

		Debug();
		~Debug();

		// Static instance to access the non-static members from the static function
		static Debug* debugInstance;

		// Preventing copying and assignment
		Debug(const Debug& other) = delete; // copy constructor
		Debug& operator=(const Debug& other) = delete; // copy assignment

		
	public:
		void BeginSystemProfile(const std::string& SystemName);
		double EndSystemProfile(const std::string& SystemName);

		void Update(double deltaTime, GLFWwindow* window);

		double GetSystemDuration(const std::string& systemName);

		// Function to handle Input for debug
		static void HandleDebugInput(GLFWwindow* window, int key, int scancode, int action, int mods);
		
		// Static method to get the instance of the Debug class
		static Debug* GetInstance();

		// Optional: Method to delete the instance (useful for cleanup)
		static void DestroyInstance();
	};


