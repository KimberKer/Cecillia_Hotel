#pragma once

#include "Core.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <imgui.h>
//#include <imgui_impl_glfw.h>
//#include <imgui_impl_opengl3.h>

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