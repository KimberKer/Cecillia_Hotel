#include "duckpch.h"
#include "Time.h"
#include <GLFW/glfw3.h>


namespace Duck
{


		Time::Time(double fps)
		{
			limitFPS = fps;

			frameTime = 1 / limitFPS;
			lastFrameTime = glfwGetTime();

			elapsedTime = 0.0;
			deltaTime = 0.0;
		}

		void Time::update()
		{
			double currFrameTime = glfwGetTime();

			deltaTime = currFrameTime - lastFrameTime;
			lastFrameTime = currFrameTime;

			elapsedTime += deltaTime;
		}

		double Time::getElapsedTime() const
		{
			return elapsedTime;
		}

		double Time::getDeltaTime() const
		{
			return deltaTime;
		}

		double Time::getFPS() const
		{
			return limitFPS;
		}

		double Time::getFrameTime() const
		{
			return frameTime;
		}

}