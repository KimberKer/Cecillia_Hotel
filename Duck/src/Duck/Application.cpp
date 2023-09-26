#include "duckpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Events/ApplicationEvent.h"
#include "Map/Map.h"
#include "Duck//Log.h"
#include "Time.h"
#include "Duck/Graphics/Graphics.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Duck/stb_image.h"
#include <GLFW/glfw3.h>


#include "Input.h"


const float  PLAYER_VELOCITY = 0.1F;

GameObject player;
MapDataHandler map;
bool loadFiles = false;
bool showImGuiWindow = false;

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

        //gets player values
        player.loadFromFile("player.txt");

        /////////////////////////////////////////////////// MAHDI ////////////////////////////////////////////////////////////////
        /////                                                                                                                /////



                /////////////////////////////// TRIANGLES /////////////////////////////

        m_VertexArray.reset(new VertexArray());

        float vertices[3 * 7] = {
            //Coordinates         //Colors
            -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f
        };

        m_VertexBuffer.reset(new VertexBuffer(vertices, sizeof(vertices)));

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
            -1.0f, -1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
             1.0f,  1.0f, 0.0f,
            -1.0f,  1.0f, 0.0f
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
        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

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
             1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f
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





        /////////////////////////////// SQUARE W/ IMAGE /////////////////////////////


        m_SquareImgVA.reset(new VertexArray);

        float SquareImgVertices[5 * 4] = {
            //Coordinates          //Texture Coord  
            -1.0f, -1.0f, 0.0f,    0.0f, 0.0f,
             1.0f, -1.0f, 0.0f,    1.0f, 0.0f,
             1.0f,  1.0f, 0.0f,    1.0f, 1.0f,
            -1.0f,  1.0f, 0.0f,    0.0f, 1.0f
        };

        std::shared_ptr<VertexBuffer> SquareImgVB;
        SquareImgVB.reset(new VertexBuffer(SquareImgVertices, sizeof(SquareImgVertices)));

        BufferLayout SquareImgLayout = {

            { ShaderDataType::Float3, "aPos"},
            { ShaderDataType::Float2, "aTex"}

        };

        SquareImgVB->SetLayout(SquareImgLayout);
        m_SquareImgVA->AddVertexBuffer(SquareImgVB);

        unsigned int SquareImgIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<IndexBuffer> SquareImgIB;
        SquareImgIB.reset(new IndexBuffer(SquareImgIndices, sizeof(SquareImgIndices)));
        m_SquareImgVA->AddIndexBuffer(SquareImgIB);

        m_SquareImgVA->SetPrimitiveType(GL_TRIANGLES);




        /////////////////////////////// SQUARE W/ SPRITE /////////////////////////////


        m_SquareSprVA.reset(new VertexArray);

        float SquareSprVertices[5 * 4] = {
            //Coordinates          //Texture Coord  
            -1.0f, -1.0f, 0.0f,    0.0f, 0.0f,
             1.0f, -1.0f, 0.0f,    1.0f, 0.0f,
             1.0f,  1.0f, 0.0f,    1.0f, 1.0f,
            -1.0f,  1.0f, 0.0f,    0.0f, 1.0f
        };

        std::shared_ptr<VertexBuffer> SquareSprVB;
        SquareSprVB.reset(new VertexBuffer(SquareSprVertices, sizeof(SquareSprVertices)));

        BufferLayout SquareSprLayout = {

            { ShaderDataType::Float3, "aPos"},
            { ShaderDataType::Float2, "aTex"}

        };

        SquareSprVB->SetLayout(SquareSprLayout);
        m_SquareSprVA->AddVertexBuffer(SquareSprVB);

        unsigned int SquareSprIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<IndexBuffer> SquareSprIB;
        SquareSprIB.reset(new IndexBuffer(SquareSprIndices, sizeof(SquareSprIndices)));
        m_SquareSprVA->AddIndexBuffer(SquareSprIB);

        m_SquareSprVA->SetPrimitiveType(GL_TRIANGLES);



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

        // Square Image Shaders
        std::string SquareImgVertexShaderSrc = Shader::LoadShaderSource("../shaders/SquareImg_Vtx_Shader.glsl");
        std::string SquareImgFragmentShaderSrc = Shader::LoadShaderSource("../shaders/SquareImg_Frg_Shader.glsl");
        m_SquareImgShader.reset(new Shader(SquareImgVertexShaderSrc, SquareImgFragmentShaderSrc));

        // Background Image Shaders
        std::string BackgroundImgVertexShaderSrc = Shader::LoadShaderSource("../shaders/Background_Vtx_Shader.glsl");
        std::string BackgroundImgFragmentShaderSrc = Shader::LoadShaderSource("../shaders/Background_Frg_Shader.glsl");
        m_BackgroundImgShader.reset(new Shader(BackgroundImgVertexShaderSrc, BackgroundImgFragmentShaderSrc));


        // Square Sprite Shaders
        std::string SquareSprVertexShaderSrc = Shader::LoadShaderSource("../shaders/SquareSpr_Vtx_Shader.glsl");
        std::string SquareSprFragmentShaderSrc = Shader::LoadShaderSource("../shaders/SquareSpr_Frg_Shader.glsl");
        m_SquareSprShader.reset(new Shader(SquareSprVertexShaderSrc, SquareSprFragmentShaderSrc));


        m_CharacterTexture = Shader::LoadTexture("../images/Character1.png");
        m_BackgroundTexture = Shader::LoadTexture("../images/FloorTile1.png");
        m_Sprite = Shader::LoadTexture("../images/Character1Sprite.png", m_SpriteWidth, m_SpriteHeight);


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
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer) {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

        //DUCK_CORE_INFO("{0}", e);

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
            (*--it)->OnEvent(e);
            if (e.Handled) {
                break;
            }
        }

        if (e.GetEventType() == EventType::KeyPressed) {
            KeyPressedEvent& keyEvent = dynamic_cast<KeyPressedEvent&>(e);
            if (keyEvent.GetKeyCode() == Key::I) {
                showImGuiWindow = !showImGuiWindow; // Toggle the window's visibility
            }

            //Gameobject changing state
            switch (keyEvent.GetKeyCode()) {
                //GameObj go LEFT
            case Key::A:
                player.SetState(STATE_GOING_LEFT);
                break;
            case Key::D:
                player.SetState(STATE_GOING_RIGHT);
                break;
            case Key::W:
                player.SetState(STATE_GOING_UP);
                break;
            case Key::S:
                player.SetState(STATE_GOING_DOWN);
                break;
            default:
                player.SetState(STATE_NONE);
                break;
            }
        }
        else if (e.GetEventType() == EventType::KeyReleased) {
            KeyReleasedEvent& keyEvent = dynamic_cast<KeyReleasedEvent&>(e);
            // Reset the velocity when the 'D' key is released
            switch (keyEvent.GetKeyCode()) {
                //GameObj go LEFT
            case Key::A:
                player.SetState(STATE_NONE);
                break;
            case Key::D:
                player.SetState(STATE_NONE);
                break;
            case Key::W:
                player.SetState(STATE_NONE);
                break;
            case Key::S:
                player.SetState(STATE_NONE);
                break;
          
            }
        }
    }

    void Application::Run() {
        while (m_Running) {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            //object
            switch (player.getState()) {
            case STATE_GOING_LEFT:
                player.SetVelocityX(-PLAYER_VELOCITY);
                break;
            case STATE_GOING_RIGHT:
                player.SetVelocityX(PLAYER_VELOCITY);
                break;
            case STATE_GOING_DOWN:
                player.SetVelocityY(PLAYER_VELOCITY);
                break;
            case STATE_GOING_UP:
                player.SetVelocityY(-PLAYER_VELOCITY);
                break;
                case STATE_NONE:
                player.SetVelocityX(0);
                player.SetVelocityY(0);
                break;
            }

            //NEED MULTIPLY BY DELTA TIME
            player.SetPositionX(player.getVelocityX() + player.getX());
            player.SetPositionY(player.getVelocityY() + player.getY());
           // pInst->posCurr.y = pInst->velCurr.y * g_dt + pInst->posCurr.y;

            ////////////////////////////////////////////////// MAHDI /////////////////////////////////////////////////////////////////
            /////                                                                                                                /////

            RenderCommand::SetClearColor({ 0.2, 0.2, 0.2, 1 });
            RenderCommand::Clear();

            // Would be used for cameras
            Renderer::BeginScene();

            //glm::vec3 SquarePos{ 0.2f,0.2f,0.0f };
            //m_SquareTransform = glm::translate(glm::mat4(1.0), SquarePos);
            //Renderer::Submit(m_SquareVA, m_SquareShader, m_SquareTransform);

            //glm::vec3 TrianglePos{ 0.2f,0.2f,0.0f };
            //m_TriangleTransform = glm::translate(glm::mat4(1.0), TrianglePos);
            //Renderer::Submit(m_VertexArray, m_Shader, m_TriangleTransform);

            //glm::vec3 LinePos{ 0.5f,0.5f,0.0f };
            //float LineAngle{ 45.f };
            //glm::vec3 LineScale{ 2.0f, 2.0f, 1.0f };
            //m_LineTransform = glm::translate(glm::mat4(1.0), LinePos);
            //m_LineTransform = glm::rotate(m_LineTransform,glm::radians(LineAngle), glm::vec3(0, 0, 1));
            //m_LineTransform = glm::scale(m_LineTransform, LineScale);
            //Renderer::Submit(m_LineVA, m_LineShader, m_LineTransform);

            //glm::vec3 Line2Pos{ 0.0f,0.0f,0.0f };
            //float Line2Angle{ 0.0f };
            //glm::vec3 Line2Scale{ 1.0f, 1.0f, 1.0f };
            //m_LineTransform = glm::translate(glm::mat4(1.0), Line2Pos);
            //m_LineTransform = glm::rotate(m_LineTransform, glm::radians(Line2Angle), glm::vec3(0, 0, 1));
            //m_LineTransform = glm::scale(m_LineTransform, Line2Scale);
            //Renderer::Submit(m_LineVA, m_LineShader, m_LineTransform);
            //
            //glm::vec3 PointPos{ 0.0f,0.0f,0.0f };
            //m_PointTransform = glm::translate(glm::mat4(1.0), PointPos);
            //Renderer::Submit(m_PointVA, m_PointShader, m_PointTransform);

            //glm::vec3 SquareImgPos{ -0.5f,-0.5f,0.0f };
            //m_SquareImgTransform = glm::translate(glm::mat4(1.0), SquareImgPos);
            //Renderer::Submit(m_SquareImgVA, m_SquareImgShader, m_SquareImgTransform, m_Texture);

            //glm::vec3 SquareSprPos{ 0.5f,-0.5f,0.0f };
            //m_SquareImgTransform = glm::translate(glm::mat4(1.0), SquareSprPos);
            //Renderer::Submit(m_SquareSprVA, m_SquareSprShader, m_SquareSprTransform, m_Texture);



            DrawBackground(20, 20, m_SquareImgVA, m_BackgroundImgShader, m_BackgroundTexture);
            std::cout << player.getX() << " " << player.getY() << std::endl;

            DrawSquareObject(map.SnapToCellX(0.5f,player.getX()), map.SnapToCellX(0.5f,player.getY()), m_SquareImgVA, m_SquareImgShader, m_CharacterTexture);
            //(player.getX(), player.getY(), m_SquareImgVA, m_SquareImgShader, m_CharacterTexture);
            DrawGrid(20, 20, m_LineVA, m_LineShader);


            Renderer::EndScene();

            /////                                                                                                                /////
            ////////////////////////////////////////////////// MAHDI /////////////////////////////////////////////////////////////////

                        // Log Mouse Position to Console
           // auto [x, y] = Input::GetMousePosition();
            //DUCK_CORE_TRACE("{0}, {1}", x, y);

            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate();
            }


            m_ImGuiLayer->Begin();
            if (showImGuiWindow) {
                for (Layer* layer : m_LayerStack) {
                    layer->OnImGuiRender();
                }
            }
            m_ImGuiLayer->End();

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

    }

    bool Application::OnWindowClose(WindowCloseEvent& e) {
        m_Running = false;
        return true;
    }
};