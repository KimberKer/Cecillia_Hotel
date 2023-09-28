#pragma once

#include <chrono>


namespace Duck {

	class Time {
	public:
		//constructor
		Time(): FPS(60) {
			frame_time = 1.0 / 60.0;
		}

		Time(double fps) : FPS(fps) {
			frame_time = 1.0 / fps;
		}

		void start_frame() {
			frame_start = std::chrono::high_resolution_clock::now();
		}

		void end_frame() {
			frame_end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> frame_duration = frame_end - frame_start;

			//calc elapsed time
			elapsed_time += frame_duration.count();

			//calc delta time
			delta_time = frame_duration.count();
			last_frame_time = elapsed_time;
		}

		double get_elapsed_time() {
			return elapsed_time;
		}

		double get_delta_time() {
			return delta_time;
		}

	private:
		double FPS;
		double frame_time;
		std::chrono::high_resolution_clock::time_point frame_start;
		std::chrono::high_resolution_clock::time_point frame_end;
		double elapsed_time = 0.0;
		double delta_time = 0.0;
		double last_frame_time = 0.0;

	}; //end of class FrameTime

} //end of namespace Duck