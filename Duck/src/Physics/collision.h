#ifndef PHYSICSLIB_HPP
#define PHYSICSLIB_HPP

#include <chrono>
#include "../Math/Vector2D.h"
#include <GLFW/glfw3.h>
#include "../Duck/Input.h"
#include <iostream>

class AABB {
public:
    MathLib::Vector2D min;
    MathLib::Vector2D max;
};

class PhysicsLib {
public:
    PhysicsLib();


    float GetDeltaTime();

bool CollisionIntersection_RectRect(const AABB& aabb1, const MathLib::Vector2D& vel1,
	const AABB& aabb2, const MathLib::Vector2D& vel2);

    void PlayerMovement(bool keyPressed,int longPressedKey, MathLib::Vector2D player_current_position, MathLib::Vector2D player_current_Velocity);
        void testCollison(int longKeyPressed,GLFWwindow* _window, MathLib::Vector2D* player_pos);

private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point currentTime;

    std::chrono::duration<float> deltaTime;
};

#endif // PHYSICSLIB_HPP
