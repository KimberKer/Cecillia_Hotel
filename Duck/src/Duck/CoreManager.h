//---------------------------------------------------------
// File:      CoreManager.cpp
// authors:	muhammad zikry bin zakaria
// email:	muhammadzikry.b\@digipen.edu
//
// Brief:     Contains the declaration of the CoreManager class for managing core game systems
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

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

