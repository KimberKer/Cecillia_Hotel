//---------------------------------------------------------
// file:	Physics.cpp
// authors:	muhammad zikry bin zakaria
// email:	muhammadzikry.b\@digipen.edu
//
// brief:	Contains functions for implementing in-game physics for game levels.
//
//
// Copyright � 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "duckpch.h"
#include "Physics.h"

namespace Duck {
    // Initializes the object's position, and sets initial velocities and accelerations.
    PhysicsObject::PhysicsObject(float x, float y) : x(x), y(y), xVelocity(0.0f), yVelocity(0.0f), xAcceleration(0.1f), yAcceleration(0.1f) {}

    // Calculates the new position of the object based on its current velocity and acceleration.
    void PhysicsObject::Update(double deltaTime)
    {
        // Using the kinematic equation: v = u + a * t
        // Update velocity based on acceleration
        xVelocity += xAcceleration * static_cast<float>(deltaTime);
        yVelocity += yAcceleration * static_cast<float>(deltaTime);

        // Using the kinematic equation: s = u * t + 0.5 * a * t * t
        // Update position based on velocity
        x += xVelocity * static_cast<float>(deltaTime);
        y += yVelocity * static_cast<float>(deltaTime);
    }

    // Return the x-coordinate of the object's position.
    float PhysicsObject::GetX() const
    {
        return x;
    }

    // Return the y-coordinate of the object's position.
    float PhysicsObject::GetY() const
    {
        return y;
    }

}