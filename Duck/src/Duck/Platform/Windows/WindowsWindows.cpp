#include "duckpch.h"
#include "Duck/Platform/Windows/WindowsWindows.h"
#include "Duck/Logging/Logging.h"

namespace Duck {
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props){
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		// Create log sinks
		ConsoleSink consoleSink;    // For logging to the console
		FileSink fileSink;          // For logging to a file
		FileSink::FileSink();

		// Create loggers and configure log levels and sinks
		Logging consoleLogger(LogLevel::INFO);  // Set log level to INFO
		consoleLogger.AddSink(&consoleSink);    // Add console sink for real-time output

		Logging fileLogger(LogLevel::DEBUG);    // Set log level to DEBUG
		fileLogger.AddSink(&fileSink);          // Add file sink for log file

		// INSERT CONSOLE MESSAGE
		//consoleLogger.Log(LogLevel::INFO, "Creating Window: ", props.Title);
		//consoleLogger.Log(LogLevel::INFO, "Creating Window: ", props.Title);


		if (!s_GLFWInitialized) {
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			// INSERT CONSOLE MESSAGE

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return m_Data.VSync;
	}
}