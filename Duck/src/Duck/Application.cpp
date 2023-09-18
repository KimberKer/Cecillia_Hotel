#include "Application.h"



// Function to handle errors
void error_callback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}



namespace Duck {

    //TESTING - time.h
    void testTime() {
        Time time;

        time.startFrame();
        time.endFrame();

        double elapsed = time.getElapsedTime();
        double delta = time.getDeltaTime();

        std::cout << "Elapsed time: " << elapsed << std::endl;
        std::cout << "Delta time: " << delta << std::endl;
    }

    //TESTING - input.h
    void testInput(GLFWwindow *_window) {
        Input::inputInit(_window);
        
        //test keyboard
        if (Input::isKeyPressed(GLFW_KEY_A)) {
            std::cout << "Key A is pressed!\n";
        }

        if (Input::isKeyLongPressed(GLFW_KEY_A, 1.0)) {
            std::cout << "Key A is long pressed (1.0s)\n";
        }

        if (Input::isKeyLongPressed(GLFW_KEY_A, 3.0)) {
            std::cout << "Key At is long pressed (3.0s)\n";
        }

        //test mouse
        if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
            std::cout << "Mouse left is pressed!\n";
        }

        if (Input::isMouseButtonLongPressed(GLFW_MOUSE_BUTTON_LEFT, 1.0)) {
            std::cout << "Mouse left is long pressed (1.0s)\n";
        }
        
        if (Input::isMouseButtonLongPressed(GLFW_MOUSE_BUTTON_LEFT, 3.0)) {
            std::cout << "Mouse left is long pressed (3.0s)\n";
        }
    }

	Application::Application() {

        // Initialize GLFW
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return;
        }

        // Set the GLFW error callback
        glfwSetErrorCallback(error_callback);

        // Create a GLFW window and OpenGL context
        window = glfwCreateWindow(800, 800, "Cecillia's Hotel", NULL, NULL);
        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }

        // Make the window's context current
        glfwMakeContextCurrent(window);

	}

	Application::~Application() {

	}

	void Application::Run() {



        // Loop until the user closes the window
        while (!glfwWindowShouldClose(window)) {
            // Render here (you can put your OpenGL drawing code here)
            testTime();
            //testInput(window);

            // Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();
        }

        // Terminate GLFW
        glfwTerminate();
        return;


	}
}