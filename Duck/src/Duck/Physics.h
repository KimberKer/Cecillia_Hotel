#pragma once

class PhysicsObject {
private:
    float x, y;                             // Position
    float xVelocity, yVelocity;             // Velocity
    float xAcceleration, yAcceleration;     // Acceleration

public:
    PhysicsObject(float x, float y);

    void Update(double deltaTime);
    float GetX() const;
    float GetY() const;
};
