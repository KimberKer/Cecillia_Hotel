#include "duckpch.h"
#include "Duck/Platform/Windows/WindowsWindows.h"
//#include "Duck/Logging/Logging.h"
#include "Duck/Events/ApplicationEvent.h"
#include "Duck/Events/MouseEvent.h"
#include "Duck/Events/KeyEvent.h"
#include "Duck/Log.h"

namespace Duck {
	static bool s_GLFWInitialized = false;

	// Callback function for GLFW errors
	static void GLFWErrorCallback(int error, const char* description) {
		DUCK_CORE_ERROR("GLFW eRROR ({0}): {1}", error, description);
	}
	
	// Create a window instance based on platform
	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	// Constructor for WindowsWindow class
	WindowsWindow::WindowsWindow(const WindowProps& props){
		Init(props);
	}

	// Destructor for WindowsWindow class
	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	// Initialize the window
	void WindowsWindow::Init(const WindowProps& props) {
		// Initialize window data
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		//// Create log sinks
		//ConsoleSink consoleSink;    // For logging to the console
		//FileSink fileSink;          // For logging to a file
		//FileSink::FileSink();

		//// Create loggers and configure log levels and sinks
		//Logging consoleLogger(LogLevel::INFO);  // Set log level to INFO
		//consoleLogger.AddSink(&consoleSink);    // Add console sink for real-time output

		//Logging fileLogger(LogLevel::DEBUG);    // Set log level to DEBUG
		//fileLogger.AddSink(&fileSink);          // Add file sink for log file

		// INSERT CONSOLE MESSAGE
		//consoleLogger.Log(LogLevel::INFO, "Creating Window: ", props.Title);
		//consoleLogger.Log(LogLevel::INFO, "Creating Window: ", props.Title);

		DUCK_CORE_INFO("Creating Window: {0} ({1}, {2})", props.Title, props.Width, props.Height);

		// Initialize GLFW if it hasn't been initialized yet
		if (!s_GLFWInitialized) {
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			DUCK_CORE_ASSERT(success, "Could not initialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		// Create the GLFW window
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks for various events
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
			});

		// Window close callback
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);

		});

		// Key press/release/repeat callback
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		// Mouse button press/release callback
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		// Mouse scroll callback
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		// Mouse cursor position callback
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
			});
	}

	// Shutdown and destroy the GLFW window
	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	// Poll for events and swap buffers
	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	// Set vertical sync
	void WindowsWindow::SetVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		m_Data.VSync = enabled;
	}

	// Check if vertical sync is enabled
	bool WindowsWindow::IsVSync() const {
		return m_Data.VSync;
	}
}