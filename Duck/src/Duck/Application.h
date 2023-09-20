#pragma once

#include "Core.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "Debug.h"

namespace Duck {

	

	class DUCK_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


 GLFWwindow* window;
 