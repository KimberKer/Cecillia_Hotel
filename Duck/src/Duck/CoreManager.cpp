//---------------------------------------------------------
// File:    CoreManager.cpp
// authors:	muhammad zikry bin zakaria
// email:	muhammadzikry.b\@digipen.edu
//
// Brief:     Contains the implementation of the CoreManager class for managing core game systems
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "duckpch.h"
#include "CoreManager.h"

namespace Duck {
    CoreManager* CoreManager::instance = nullptr;

    CoreManager::CoreManager() {
        debugger = Debug::GetInstance();
    }

    CoreManager::~CoreManager() {
        Debug::DestroyInstance();
    }

    CoreManager* CoreManager::GetInstance() {
        if (!instance) {
            instance = new CoreManager();
            if (!instance)
            {
                // Error handling if memory allocation fails.
                throw std::runtime_error(std::string("Error in file ") + __FILE__ + " on line " + std::to_string(__LINE__));
            }
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
    }

    void CoreManager::Update(double deltaTime, GLFWwindow* window) {
        debugger->BeginSystemProfile("Debug");
        debugger->Update(deltaTime, window);
        debugger->EndSystemProfile("Debug");



    }
}
