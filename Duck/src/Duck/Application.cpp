#include "Application.h"



// Function to handle errors
void error_callback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}



namespace Duck {



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

        // Setup ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        // Setup Platform/Renderer bindings
        //ImGui_ImplGlfw_InitForOpenGL(window, true); 
        //ImGui_ImplOpenGL3_Init("#version 330");

	}

	Application::~Application() {

	}

	void Application::Run() {



        // Loop until the user closes the window
        while (!glfwWindowShouldClose(window)) {
            // Render here (you can put your OpenGL drawing code here)
            // Start new ImGui frame
            //ImGui_ImplOpenGL3_NewFrame();
            //ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

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