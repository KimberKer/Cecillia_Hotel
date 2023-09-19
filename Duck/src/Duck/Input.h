#pragma once

#include "Core.h"
#include <GLFW/glfw3.h>

namespace Duck {

	class DUCK_API Input {

	public:
		static void inputInit(GLFWwindow* window);

		//keyboard functions
		static bool isKeyPressed(int key);
		static bool isKeyLongPressed(int key, double minDuration);

		//mouse functions
		static bool isMouseButtonPressed(int button);
		static bool isMouseButtonLongPressed(int button, double minDuration);
		static void getMousePosition(double& xPos, double& yPos);
		static int GetKeys();

	private:
		static GLFWwindow* window;
	};

}