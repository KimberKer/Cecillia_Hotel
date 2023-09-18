#include "Input.h"
#include <GLFW/glfw3.h>

namespace Duck {
	GLFWwindow* Input::window = nullptr;

	void Input::inputInit(GLFWwindow *_window) {
		window = _window;
	}

	bool Input::isKeyPressed(int key) {
		if (window) {
			return glfwGetKey(window, key) == GLFW_PRESS;
		}

		return false;
	}

	bool Input::isKeyLongPressed(int key, double minDuration) {
		static bool pressed = false;
		static double startTime = 0.0;

		if (window) {
			if (glfwGetKey(window, key) == GLFW_PRESS) {
				if (!pressed) {
					pressed = true;
					startTime = glfwGetTime();
				}

				else {
					double currTime = glfwGetTime();
					double duration = currTime - startTime;

					if (duration >= minDuration) {
						return true;
					}
				}
			}

			else {
				pressed = false;
			}
		}

		return false;
	}

	bool Input::isMouseButtonPressed(int button) {
		if (window) {
			return glfwGetMouseButton(window, button) == GLFW_PRESS;
		}

		return false;
	}

	bool Input::isMouseButtonLongPressed(int button, double minDuration) {
		static bool pressed = false;
		static double startTime = 0.0;

		if (window) {
			if (glfwGetMouseButton(window, button) == GLFW_PRESS) {
				if (!pressed) {
					pressed = true;
					startTime = glfwGetTime();
				}

				else {
					double currTime = glfwGetTime();
					double duration = currTime - startTime;

					if (duration >= minDuration) {
						return true;
					}
				}
			}

			else {
				pressed = false;
			}
		}

		return false;
	}

	void Input::getMousePosition(double& xPos, double& yPos) {
		if (window) {
			glfwGetCursorPos(window, &xPos, &yPos);
		}
	}

}