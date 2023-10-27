//---------------------------------------------------------
// file:	Physics.h
// authors:	muhammad zikry bin zakaria
// email:	muhammadzikry.b\@digipen.edu
//
// brief:	Contains the declaration of the PhysicsObject class for implementing basic physics properties.
//
//
// Copyright � 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once

namespace Duck {
    // This class represents an individual physics object with basic properties such as position, velocity, and acceleration.
    class PhysicsObject {
    public:
        // Constructor: Initializes the physics object with a starting position.
        PhysicsObject(float x, float y);

        // Update the physics object based on the given time delta.
        void Update(double deltaTime);

        // x position.
        float GetX() const;

        // y position.
        float GetY() const;

    private:
        float x, y;                             // The current position of the object
        float xVelocity, yVelocity;             // The current velocity of the object
        float xAcceleration, yAcceleration;     // The current acceleration of the object
    };
}