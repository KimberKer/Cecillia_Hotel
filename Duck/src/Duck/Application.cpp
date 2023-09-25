#include "duckpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Duck//Log.h"
#include "Time.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/matrix_transform_2d.hpp>
// Headers for memory leak detection
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>

#include "Input.h"
#include <fstream>
#include <exception>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <Windows.h>
#include "Application.h"
#include "PhysicsManager.h"
#include "Debug.h"


GameObject player;
bool loadFiles = false;

// Function to handle errors
void error_callback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}

namespace Duck {
    Application* Application::s_Instance = nullptr;

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)




	Application::Application() {
        DUCK_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

/////////////////////////////////////////////////// MAHDI ////////////////////////////////////////////////////////////////
/////                                                                                                                /////







        /////////////////////////////// TRIANGLES /////////////////////////////

        m_VertexArray.reset(new VertexArray());

        float vertices[3*7] = {
           //Coordinates         //Colors
           -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,
            0.0f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f
        };
    Application::Application() {

        m_VertexBuffer.reset(new VertexBuffer(vertices , sizeof(vertices)));

        BufferLayout layout = {

            { ShaderDataType::Float3, "aPos"},
            { ShaderDataType::Float4, "aColor"}

        };

        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        unsigned int indices[3] = { 0, 1, 2 };
        m_IndexBuffer.reset(new IndexBuffer(indices, sizeof(indices)));
        m_VertexArray->AddIndexBuffer(m_IndexBuffer);

        m_VertexArray->SetPrimitiveType(GL_TRIANGLES);

        /////////////////////////////// SQUARES /////////////////////////////


        m_SquareVA.reset(new VertexArray);

        float SquareVertices[3 * 4] = {
            //Coordinates         
            -0.5f, -0.5f, 0.0f,   
             0.5f, -0.5f, 0.0f, 
             0.5f,  0.5f, 0.0f, 
            -0.5f,  0.5f, 0.0f
        };


        std::shared_ptr<VertexBuffer> SquareVB;
        SquareVB.reset(new VertexBuffer(SquareVertices, sizeof(SquareVertices)));
            
        BufferLayout SquareLayout = {

            { ShaderDataType::Float3, "aPos"}

        };
        SquareVB->SetLayout(SquareLayout);
        m_SquareVA->AddVertexBuffer(SquareVB);

        unsigned int SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<IndexBuffer> SquareIB;
        SquareIB.reset(new IndexBuffer(SquareIndices, sizeof(SquareIndices)));
        m_SquareVA->AddIndexBuffer(SquareIB);

        m_SquareVA->SetPrimitiveType(GL_TRIANGLES);


        /////////////////////////////// POINTS //////////////////////////////

        m_PointVA.reset(new VertexArray);

        float PointVertices[3 * 1] = {
            //Coordinates         
            0.0f, 0.0f, 0.0f
        };


        std::shared_ptr<VertexBuffer> PointVB;
        PointVB.reset(new VertexBuffer(PointVertices, sizeof(PointVertices)));

        BufferLayout PointLayout = {

            { ShaderDataType::Float3, "aPos"}

        };
        PointVB->SetLayout(PointLayout);
        m_PointVA->AddVertexBuffer(PointVB);

        unsigned int PointIndices[1] = { 0 };
        std::shared_ptr<IndexBuffer> PointIB;
        PointIB.reset(new IndexBuffer(PointIndices, sizeof(PointIndices)));
        m_PointVA->AddIndexBuffer(PointIB);
        glPointSize(5.f);

        m_PointVA->SetPrimitiveType(GL_POINTS);



        /////////////////////////////// LINES //////////////////////////////

        m_LineVA.reset(new VertexArray);

        float LineVertices[3 * 2] = {
            //Coordinates         
             0.5f, 0.0f, 0.0f,
            -0.5f, 0.0f, 0.0f
        };


        std::shared_ptr<VertexBuffer> LineVB;
        LineVB.reset(new VertexBuffer(LineVertices, sizeof(LineVertices)));

        BufferLayout LineLayout = {

            { ShaderDataType::Float3, "aPos"}

        };
        LineVB->SetLayout(LineLayout);
        m_LineVA->AddVertexBuffer(LineVB);

        unsigned int LineIndices[2] = { 0, 1 };
        std::shared_ptr<IndexBuffer> LineIB;
        LineIB.reset(new IndexBuffer(LineIndices, sizeof(LineIndices)));
        m_LineVA->AddIndexBuffer(LineIB);
        glLineWidth(3.f);

        m_LineVA->SetPrimitiveType(GL_LINES);


        /////////////////////////////// SHADERS /////////////////////////////

        // Load vertex and fragment shader source code

        // Triangle Shaders
        std::string vertexShaderSource = Shader::LoadShaderSource("../shaders/vertex_shader.glsl");
        std::string fragmentShaderSource = Shader::LoadShaderSource("../shaders/fragment_shader.glsl");
        m_Shader.reset(new Shader(vertexShaderSource, fragmentShaderSource));

        // Square Shaders
        std::string SquareVertexShaderSrc = Shader::LoadShaderSource("../shaders/Square_Vtx_Shader.glsl");
        std::string SquareFragmentShaderSrc = Shader::LoadShaderSource("../shaders/Square_Frg_Shader.glsl");
        m_SquareShader.reset(new Shader(SquareVertexShaderSrc, SquareFragmentShaderSrc));

        // Point Shaders
        std::string PointVertexShaderSrc = Shader::LoadShaderSource("../shaders/Point_Vtx_Shader.glsl");
        std::string PointFragmentShaderSrc = Shader::LoadShaderSource("../shaders/Point_Frg_Shader.glsl");
        m_PointShader.reset(new Shader(PointVertexShaderSrc, PointFragmentShaderSrc));

        // Line Shaders
        std::string LineVertexShaderSrc = Shader::LoadShaderSource("../shaders/Line_Vtx_Shader.glsl");
        std::string LineFragmentShaderSrc = Shader::LoadShaderSource("../shaders/Line_Frg_Shader.glsl");
        m_LineShader.reset(new Shader(LineVertexShaderSrc, LineFragmentShaderSrc));



/////                                                                                                                /////
////////////////////////////////////////////////////// MAHDI /////////////////////////////////////////////////////////////



        //// Initialize GLFW
        //if (!glfwInit()) {
        //    std::cerr << "Failed to initialize GLFW" << std::endl;
        //    return;
        //}

        //// Set the GLFW error callback
        //glfwSetErrorCallback(error_callback);

        //// Create a GLFW window and OpenGL context
        //window = glfwCreateWindow(800, 800, "Cecillia's Hotel", NULL, NULL);
        //if (!window) { 
        //    std::cerr << "Failed to create GLFW window" << std::endl;
        //    glfwTerminate();
        //    return;
        //}

        //// Make the window's context current
        //glfwMakeContextCurrent(window);
	}

	Application::~Application() {

	}

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
    }

        glfwSetKeyCallback(window, Debug::HandleDebugInput);

    }
    void Application::PushOverlay(Layer* layer) {
        m_LayerStack.PushOverlay(layer);
    }

    Application::~Application() {
    void Application::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

        //DUCK_CORE_INFO("{0}", e);

        Debug::DestroyInstance(); 
        PhysicsManager::DestroyInstance();  
    }
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
            (*--it)->OnEvent(e);
            if (e.Handled) {
                break;
            }
        }
    }

    void Application::Run() {
        // Enable memory leak detection
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	void Application::Run() {
        while (m_Running) {

////////////////////////////////////////////////// MAHDI /////////////////////////////////////////////////////////////////
/////                                                                                                                /////
            
            RenderCommand::SetClearColor({ 0.2, 0.2, 0.2, 1 });
            RenderCommand::Clear();

            // Would be used for cameras
            Renderer::BeginScene();

            glm::vec3 SquarePos{ 0.2f,0.2f,0.0f };
            m_SquareTransform = glm::translate(glm::mat4(1.0), SquarePos);
            Renderer::Submit(m_SquareVA, m_SquareShader, m_SquareTransform);

            glm::vec3 TrianglePos{ 0.2f,0.2f,0.0f };
            m_TriangleTransform = glm::translate(glm::mat4(1.0), TrianglePos);
            Renderer::Submit(m_VertexArray, m_Shader, m_TriangleTransform);
           
            glm::vec3 LinePos{ 0.5f,0.5f,0.0f };
            float LineAngle{ 45.f };
            glm::vec3 LineScale{ 2.0f, 2.0f, 1.0f };
            m_LineTransform = glm::translate(glm::mat4(1.0), LinePos);
            m_LineTransform = glm::rotate(m_LineTransform,glm::radians(LineAngle), glm::vec3(0, 0, 1));
            m_LineTransform = glm::scale(m_LineTransform, LineScale);
            Renderer::Submit(m_LineVA, m_LineShader, m_LineTransform);
            
            glm::vec3 PointPos{ 0.0f,0.0f,0.0f };
            m_PointTransform = glm::translate(glm::mat4(1.0), PointPos);
            Renderer::Submit(m_PointVA, m_PointShader, m_PointTransform);
           
            
            Renderer::EndScene();

/////                                                                                                                /////
////////////////////////////////////////////////// MAHDI /////////////////////////////////////////////////////////////////

            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate();
            }

        double lastFrameTime = glfwGetTime();
            //// Log Mouse Position to Console
            //auto [x, y] = Input::GetMousePosition();
            //DUCK_CORE_TRACE("{0}, {1}", x, y);


        // Surround the game loop with try-catch for crash logging
        try {
            // Loop until the user closes the window
            while (!glfwWindowShouldClose(window)) {
                Debug* debugger = Debug::GetInstance();

                // Initialize the physics manager and its test objects
                PhysicsManager* physicsManager = PhysicsManager::GetInstance();
                physicsManager->InitializeTestObjects();

                // Calculate delta time
                double currentFrameTime = glfwGetTime();
                double deltaTime = currentFrameTime - lastFrameTime;
                lastFrameTime = currentFrameTime;

                // Wraps the physics system to calculate the system time
                debugger->BeginSystemProfile("Physics");
                physicsManager->UpdateALL(deltaTime);
                debugger->EndSystemProfile("Physics");

                // Update debugging utilities
                debugger->Update(deltaTime, window);

         

                // Render here (you can put your OpenGL drawing code here)
            m_Window->OnUpdate();
        }

        // Loop until the user closes the window
        //while (!glfwWindowShouldClose(window)) {
        //    // Render here (you can put your OpenGL drawing code here)
        //    Time run_time;
        //    double delta_time = run_time.get_elapsed_time();
        //    //std::cout << "Elapsed Time: " << delta_time << std::endl;

        //    // Swap front and back buffers
        //    glfwSwapBuffers(window);

        //    // Poll for and process events
        //    glfwPollEvents();

        //    // Load Game Objects
        //    if (!loadFiles) {
        //        // Load player data
        //        player.loadPlayerData();
        //        loadFiles = true; // Set the flag to true to indicate data has been loaded

        //        consoleLogger.Log("All Game Object Loaded!", LogLevel::INFO);
        //        fileLogger.Log("All Game Object Loaded!", LogLevel::DEBUG);
        //    }
        //}

        //// Terminate GLFW
        //glfwTerminate();

                // Swap front and back buffers
                glfwSwapBuffers(window);

                // Poll for and process events
                glfwPollEvents();
            }
        }
        catch (const std::exception& e) 
        {
            // Define the directory for crash logs
            const char* crashLogsDir = "CrashLogs/";

            // Check if the directory exists, if not, create it
            if (GetFileAttributesA(crashLogsDir) == INVALID_FILE_ATTRIBUTES)
            {
                CreateDirectoryA(crashLogsDir, NULL);
            }

            // Generate the filename based on current timestamp
            struct tm newtime;
            time_t now = time(0);
            localtime_s(&newtime, &now);     // fills in the newtime struct with the date if not error
            std::ostringstream oss;
            oss << std::put_time(&newtime, "/CrashLog %d-%m-%Y.txt");   // format the date and time for the crashlog filename
            std::string crashLogFileName = std::string(crashLogsDir) + oss.str();

            // Write the exception message to crash log
            std::ofstream crashLog(crashLogFileName, std::ios::out);
            crashLog << "Crash with message: " << e.what() << std::endl;
            crashLog.close();

            // Re-throw the exception to allow for external handling or just terminate the program
            throw;
        }

        // Terminate GLFW
        glfwTerminate();
        return;
    }
}


	}

    bool Application::OnWindowClose(WindowCloseEvent& e) {
        m_Running = false;
        return true;
    }
}