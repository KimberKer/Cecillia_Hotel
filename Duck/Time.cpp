#include "Time.h"
#include <GLFW/glfw3.h>


namespace Duck
{


		Time(double fps)
		{
			limitFPS = fps;

			frameTime = 1 / limitFPS;
			lastFrameTime = glfwGetTime();

			elapsedTime = 0.0;
			deltaTime = 0.0;
		}

		void update()
		{
			double currFrameTime = glfwGetTime();

			deltaTime = currFrameTime - lastFrameTime;
			lastFrameTime = currFrameTime;

			elapsedTime += deltaTime;
		}

		double getElapsedTime() const
		{
			return elapsedTime;
		}

		double getDeltaTime() const
		{
			return deltaTime;
		}

		double getFPS() const
		{
			return limitFPS;
		}

		double Time::getFrameTime() const
		{
			return frameTime;
		}

}