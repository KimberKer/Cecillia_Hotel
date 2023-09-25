#pragma once
#include <vector>
#include "Physics.h"

// This class manages multiple physics objects and provides a single point of control
// for interacting with these objects.
class PhysicsManager {
public:
    // Retrieve or create the singleton instance of PhysicsManager.
    static PhysicsManager* GetInstance();

    // Destroys the singleton instance of PhysicsManager.
    static void DestroyInstance();

    // Add a physics object with specified initial position.
    void AddObject(float x, float y);

    // Update all physics objects with the given time delta.
    void UpdateALL(double deltaTime);

    // Get a reference to all physics objects.
    std::vector<PhysicsObject>& GetObjects();

    // Initialize test objects (for debugging purposes).
    void InitializeTestObjects();

    ~PhysicsManager() {}

private:
    // Singleton instance
    static PhysicsManager* instance;

    // Collection to store all physics objects
    std::vector<PhysicsObject> objects;

    // Private constructor to ensure only one instance of the manager is created.
    PhysicsManager() {}
};
