#pragma once

#include "Core.h"
#include <chrono>

namespace Duck {

	class DUCK_API Time {
	public:
		Time();
		Time(double fps);

		void startFrame();
		void endFrame();

		double getElapsedTime();
		double getDeltaTime();

	private:
		double FPS;
		double frameTime;
		std::chrono::high_resolution_clock::time_point frameStart;
		std::chrono::high_resolution_clock::time_point frameEnd;
		double elapsedTime = 0.0;
		double deltaTime = 0.0;
		double lastFrameTime = 0.0;

	}; //end of class FrameTime

} //end of namespace Duck