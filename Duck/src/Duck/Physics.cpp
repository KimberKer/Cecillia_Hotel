#include "Physics.h"

PhysicsObject::PhysicsObject(float x, float y) : x(x), y(y), xVelocity(0.0f), yVelocity(0.0f), xAcceleration(0.1f), yAcceleration(0.1f) {}


void PhysicsObject::Update(double deltaTime) {
    // v = u + a * t
    // Update velocity based on acceleration
    xVelocity += xAcceleration * deltaTime;
    yVelocity += yAcceleration * deltaTime;

    //s = u * t + 0.5 * a * t * t
    // Update position based on velocity
    x += xVelocity * deltaTime;
    y += yVelocity * deltaTime;
}
float PhysicsObject::GetX() const {
    return x;
}

float PhysicsObject::GetY() const {
    return y;
}
