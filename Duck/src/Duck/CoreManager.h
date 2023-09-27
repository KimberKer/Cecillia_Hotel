#pragma once

#include "Debug.h"
#include "Physics/PhysicsManager.h"

namespace Duck {
    class CoreManager {
    public:
        // Singleton pattern's method to get or create the instance
        static CoreManager* GetInstance();

        // Singleton pattern's method to destroy the instance
        static void DestroyInstance();

        // Initialize all systems
        void Init(GLFWwindow* window);

        // Update all systems
        void Update(double deltaTime, GLFWwindow* window);

    private:
        Debug* debugger;
        PhysicsManager* physicsManager;

        // Singleton mechanics
        static CoreManager* instance;
        CoreManager();
        ~CoreManager();
    };
}

