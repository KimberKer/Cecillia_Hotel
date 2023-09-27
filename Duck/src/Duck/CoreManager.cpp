#include "duckpch.h"
#include "CoreManager.h"

namespace Duck {
    CoreManager* CoreManager::instance = nullptr;

    CoreManager::CoreManager() {
        debugger = Debug::GetInstance();
        physicsManager = PhysicsManager::GetInstance();
    }

    CoreManager::~CoreManager() {
        Debug::DestroyInstance();
        PhysicsManager::DestroyInstance();
    }

    CoreManager* CoreManager::GetInstance() {
        if (!instance) {
            instance = new CoreManager();
        }
        return instance;
    }

    void CoreManager::DestroyInstance() {
        delete instance;
        instance = nullptr;
    }

    void CoreManager::Init(GLFWwindow* window) {
        // Initialize systems as needed
        glfwSetKeyCallback(window, Debug::HandleDebugInput);
        physicsManager->InitializeTestObjects();
    }

    void CoreManager::Update(double deltaTime, GLFWwindow* window) {\
        debugger->BeginSystemProfile("Debug");
        debugger->Update(deltaTime, window);
        debugger->EndSystemProfile("Debug");

        // Wraps the physics system to calculate the system time
        debugger->BeginSystemProfile("Physics");
        physicsManager->UpdateALL(deltaTime);
        debugger->EndSystemProfile("Physics");
    }
}
