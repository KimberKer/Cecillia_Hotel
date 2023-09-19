// Include necessary headers and precompiled header
#pragma once
#include "duckpch.h"
#include "Duck/Core.h"
#include "Duck/Events/Event.h"

namespace Duck {
    // Struct to hold window properties
    struct WindowProps {
        std::string Title;     // Window title
        uint32_t Width;        // Window width
        uint32_t Height;       // Window height

        // Constructor to initialize window properties
        WindowProps(const std::string& title = "Cecillia Hotel",
            uint32_t width = 800,
            uint32_t height = 800)
            : Title(title), Width(width), Height(height)
        {
        }
    };

    // Interface representing a desktop system based Window
    class DUCK_API Window {
    public:
        // Define a callback function for handling events
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() {}; // Virtual destructor for Window class

        // Pure virtual function to be implemented by derived classes
        virtual void OnUpdate() = 0; // Update the window

        // Get the width and height of the window
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        // Set the event callback function for handling window events
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

        // Enable or disable vertical synchronization (VSync)
        virtual void SetVSync(bool enabled) = 0;

        // Check if VSync is enabled
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        // Create a window with the specified properties
        static Window* Create(const WindowProps& props = WindowProps());
    };
}
