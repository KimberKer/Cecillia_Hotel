#include "PhysicsManager.h"

PhysicsManager* PhysicsManager::instance = nullptr;

PhysicsManager* PhysicsManager::GetInstance() {
    if (!instance) {
        instance = new PhysicsManager();
    }
    return instance;
}

void PhysicsManager::AddObject(float x, float y) {
    objects.emplace_back(x, y);
}

void PhysicsManager::Update(double deltaTime) {
    for (auto& obj : objects) {
        obj.Update(deltaTime);
    }
}

std::vector<PhysicsObject>& PhysicsManager::GetObjects() {
    return objects;
}

void PhysicsManager::InitializeTestObjects() {
    AddObject(10, 10);
  
}
