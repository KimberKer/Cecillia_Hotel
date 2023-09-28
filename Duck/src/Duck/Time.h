#pragma once
#include <chrono>
using namespace std::chrono;

namespace Duck {

    class DeltaTime
    {
    public:

        DeltaTime(){
            lastTime = std::chrono::high_resolution_clock::now();
            fps = 0.0f;
        }

        // Call this function at the beginning of each frame
        void Update()
        {
            auto currentTime = std::chrono::high_resolution_clock::now();
            deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
            lastTime = currentTime;
        }

        // Get the delta time in seconds
        float GetDeltaTime() const
        {
            return deltaTime;
        }
    private:
        std::chrono::high_resolution_clock::time_point lastTime;
        float deltaTime;
        float fps;
    };

} //end of namespace Duck