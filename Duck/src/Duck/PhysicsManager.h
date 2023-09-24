#pragma once
#include <vector>
#include "Physics.h"

class PhysicsManager {
private:
    static PhysicsManager* instance;
    std::vector<PhysicsObject> objects;

    PhysicsManager() {}

public:
    static PhysicsManager* GetInstance();

    void AddObject(float x, float y);
    void Update(double deltaTime);
    std::vector<PhysicsObject>& GetObjects();
    void InitializeTestObjects();

    ~PhysicsManager() {}
};
