#include "Application.h"

#include "Time.h"
#include "Input.h"
#include "../Audio/Audio.h"



// Function to handle errors
void error_callback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}



namespace Duck {

    //TESTING - time.h
    void testTime()
    {
        Time test;

        bool done = false;

        while (!done)
        {
            test.update();

            std::cout << "Elapsed time: " << test.getElapsedTime() << std::endl;
            std::cout << "Delta time: " << test.getDeltaTime() << std::endl;

            if (Input::isKeyLongPressed(GLFW_KEY_A, 3.0))
                done = true;
        }

        std::cout << "Time test done!\n";
    }

    //TESTING - audio.h
    void testAudio() 
    {
        using namespace AudioMgr;

        Audio audio;
        audio.init();

        SoundInfo* testSound = new SoundInfo("test", "../Assets/Audio/test.wav");

        audio.loadSound(*testSound);

        audio.playSound(*testSound);

        bool done = false;

        while (!done)
        {
            audio.update();

            if (Duck::Input::isKeyPressed(GLFW_KEY_A))
                audio.stopSound(*testSound);
        }

        audio.deactivate();

        std::cout << "Audio test done!\n";
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
            testAudio();
            testTime();

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