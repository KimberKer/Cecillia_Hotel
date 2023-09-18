#pragma once

#include "Core.h"
#include <iostream>
//#include <GLFW/glfw3.h>
#include "De-serialize/GameObject.h"
#include "Logging/Logging.h"
#include "Events/Event.h"
#include "Window.h"

namespace Duck {
	class DUCK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

 //GLFWwindow* window;