#include "PhysicsManager.h"
#include <iostream>   // For console output
#include <string>

// Singleton instance initialization.
PhysicsManager* PhysicsManager::instance = nullptr;

// Retrieve or create the singleton instance of PhysicsManager.
PhysicsManager* PhysicsManager::GetInstance() {
    if (!instance) {
        instance = new PhysicsManager();
        if (!instance) {
            // Error handling if memory allocation fails.
            throw std::runtime_error(std::string("Error in file ") + __FILE__ + " on line " + std::to_string(__LINE__));
        }
    }
    return instance;
}

// Clean up the singleton instance.
void PhysicsManager::DestroyInstance()
{
    delete instance;
    instance = nullptr;
}

// Add a physics object to the collection.
void PhysicsManager::AddObject(float x, float y) {
    objects.emplace_back(x, y);
}

// Iterate over all physics objects and update them.
void PhysicsManager::UpdateALL(double deltaTime) {
    for (auto& obj : objects) {
        obj.Update(deltaTime);
    }
}

// Provide access to the collection of physics objects.
std::vector<PhysicsObject>& PhysicsManager::GetObjects() {
    return objects;
}

// Create test objects for debugging and testing purposes.
void PhysicsManager::InitializeTestObjects() {
    AddObject(10, 12);
}
