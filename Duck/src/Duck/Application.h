#pragma once

#include "Core.h"
#include "Time.h"
#include "Input.h"
#include "../Map/Map.h"
#include "../Math/Vector2D.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "../Physics/collision.h"

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