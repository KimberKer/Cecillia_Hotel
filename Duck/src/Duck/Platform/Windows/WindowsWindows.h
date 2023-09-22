#pragma once
#include "Duck/Window.h"
#include <GLFW/glfw3.h>

namespace Duck {
	class WindowsWindow : public Window {
	public:
		// Constructor
		WindowsWindow(const WindowProps& props);

		// Destructor
		virtual ~WindowsWindow();

		// Function to handle window updates
		void OnUpdate() override;

		// Getters for window width and height
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Set the event callback function
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		// Set vertical sync
		void SetVSync(bool enabled) override;

		// Check if vertical sync is enabled
		bool IsVSync() const override;
		
		inline virtual void* GetNativeWindow() const { return m_Window; }

	private:
		// Initialize the window
		virtual void Init(const WindowProps& props);

		// Shutdown and destroy the window
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;

		// Struct to store window data
		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}
