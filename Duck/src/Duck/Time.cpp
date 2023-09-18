#include "Time.h"

namespace Duck {

	Time::Time() : FPS() {
		frameTime = 1.0 / 60.0;
	}

	Time::Time(double fps) : FPS(fps) {
		frameTime = 1.0 / fps;
	}

	void Time::startFrame() {
		frameStart = std::chrono::high_resolution_clock::now();
	}

	void Time::endFrame() {
		frameEnd = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> frame_duration = frameEnd - frameStart;

		//calc elapsed time
		elapsedTime += frame_duration.count();

		//calc delta time
		deltaTime = frame_duration.count();
		lastFrameTime = elapsedTime;
	}

	double Time::getElapsedTime() {
		return elapsedTime;
	}

	double Time::getDeltaTime() {
		return deltaTime;
	}

}