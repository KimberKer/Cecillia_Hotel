//---------------------------------------------------------
// File:    Graphics.cpp
//authors:	Ahmad Mahdi Bin Jamal
// email:	ahmadmahdi.b@digipen.edu
// 
//
// Brief:     This file contains the definitions of the 
//          Graphics class, which handles rendering objects 
//          in a 2D grid-based environment. It uses OpenGL 
//          for rendering.
// 
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "duckpch.h"
#include "Graphics.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <filesystem>
#include <GLFW/glfw3.h>


namespace Duck {


    // Constructor for the Graphics class. Initializes various graphics objects and shaders.
	Graphics::Graphics(std::shared_ptr<Window> window) {

        // Default Grid Size

        cols = 10;
        rows = 10;
        TileWidth = 100.f;
        TileHeight = 100.f;
        TotalWidth = TileWidth * static_cast<float>(cols);
        TotalHeight = TileHeight * static_cast<float>(rows);

        // Initialize Projection matrix from the Window Size.

        mProj = 
            {

    2.f / window->GetWidth(), 0.f,						 0.f, 0.f,
    0.f,				      2.f / window->GetHeight(), 0.f, 0.f,
    0.f,					  0.f,						 1.f, 0.f,
    0.f,                      0.f,                       0.f, 1.f

};
       //glm::ortho(-(window->GetWidth()/2), (window->GetWidth() / 2), (window->GetHeight() / 2), -(window->GetHeight() / 2));
        
        


        // Animation Variables

        //SPframe = 2.f;
        //timeNow = timeOld = 0.f;
        //uv_x = 0.f;
        //uv_y = 1.f;

        uv_x = 0.0f, uv_y = 2.0f;
        //timeNow, timeOld, time_delta, SPframe;
        SPframe = 4.0f;
        timeNow = timeOld = glfwGetTime();



        // Initialize Camera

        m_camera.reset(new Camera(0.f,0.f));
        m_UIcamera.reset(new Camera(0.f, 0.f));


        /////////////////////////////////// LOAD FONTS ////////////////////////////////


        LoadFont("../fonts/Roboto-Bold.ttf");


        /////////////////////////////// TRIANGLES /////////////////////////////

        m_TriangleVA.reset(new VertexArray());

        float vertices[3 * 7] = {
            //Coordinates         //Colors
            -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f
        };

        std::shared_ptr<VertexBuffer> m_TriangleVB;
        m_TriangleVB.reset(new VertexBuffer(vertices, sizeof(vertices)));

        BufferLayout layout = {

            { ShaderDataType::Float3, "aPos"},
            { ShaderDataType::Float4, "aColor"}

        };

        m_TriangleVB->SetLayout(layout);
        m_TriangleVA->AddVertexBuffer(m_TriangleVB);

        unsigned int indices[3] = { 0, 1, 2 };
        std::shared_ptr<IndexBuffer> TrianlgleIB;
        TrianlgleIB.reset(new IndexBuffer(indices, sizeof(indices)));
        m_TriangleVA->AddIndexBuffer(TrianlgleIB);

        m_TriangleVA->SetPrimitiveType(GL_TRIANGLES);

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
            -1.0f,  1.0f, 0.0f,    0.0f, 1.0f,

        };

        float SquareSprVertices1[5 * 4] = {
            //Coordinates          //Texture Coord  
            -1.0f, -1.0f, 0.0f,    0.0f, 0.0f,
             1.0f, -1.0f, 0.0f,    0.25f, 0.0f,
             1.0f,  1.0f, 0.0f,    0.25f, 1.f,
            -1.0f,  1.0f, 0.0f,    0.0f, 1.f,

        };

        float SquareSprVertices2[5 * 4] = {
            //Coordinates          //Texture Coord  
            -1.0f, -1.0f, 0.0f,    0.25f, 0.0f,
             1.0f, -1.0f, 0.0f,    0.5f, 0.0f,
             1.0f,  1.0f, 0.0f,    0.5f, 1.f,
            -1.0f,  1.0f, 0.0f,    0.25f, 1.f,

        };

        float SquareSprVertices3[5 * 4] = {
            //Coordinates          //Texture Coord  
            -1.0f, -1.0f, 0.0f,    0.5f, 0.0f,
             1.0f, -1.0f, 0.0f,    0.75f, 0.0f,
             1.0f,  1.0f, 0.0f,    0.75f, 1.f,
            -1.0f,  1.0f, 0.0f,    0.5f, 1.f,

        };

        float SquareSprVertices4[5 * 4] = {
            //Coordinates          //Texture Coord  
            -1.0f, -1.0f, 0.0f,    0.75f, 0.0f,
             1.0f, -1.0f, 0.0f,    1.f, 0.0f,
             1.0f,  1.0f, 0.0f,    1.f, 1.f,
            -1.0f,  1.0f, 0.0f,    0.75f, 1.f,

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






        /////////////////////////////// FONTS //////////////////////////////


        /////////////////////////////// SHADERS /////////////////////////////

        // IMPLEMENT ASSET MANAGER HERE


        // Load vertex and fragment shader.

        // Triangle Shaders
        std::string vertexShaderSource = Shader::LoadShaderSource("../shaders/vertex_shader.glsl");
        std::string fragmentShaderSource = Shader::LoadShaderSource("../shaders/fragment_shader.glsl");
        m_TriangleShader.reset(new Shader(vertexShaderSource, fragmentShaderSource));

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

        // Bouding Line Shaders
        std::string BoundingLineFragmentShaderSrc = Shader::LoadShaderSource("../shaders/BoundingLine_Frg_Shader.glsl");
        m_BoundingLineShader.reset(new Shader(LineVertexShaderSrc, BoundingLineFragmentShaderSrc));


        // Square Image Shaders
        std::string SquareImgVertexShaderSrc = Shader::LoadShaderSource("../shaders/SquareImg_Vtx_Shader.glsl");
        std::string SquareImgFragmentShaderSrc = Shader::LoadShaderSource("../shaders/SquareImg_Frg_Shader.glsl");
        m_SquareImgShader.reset(new Shader(SquareImgVertexShaderSrc, SquareImgFragmentShaderSrc));

        // Background Image Shaders
        std::string BackgroundImgVertexShaderSrc = Shader::LoadShaderSource("../shaders/Background_Vtx_Shader.glsl");
        std::string BackgroundImgFragmentShaderSrc = Shader::LoadShaderSource("../shaders/Background_Frg_Shader.glsl");
        m_BackgroundImgShader.reset(new Shader(BackgroundImgVertexShaderSrc, BackgroundImgFragmentShaderSrc));

        // Square Sprite Shaders
        std::string SquareSprVertexShaderSrc = Shader::LoadShaderSource("../shaders/SquareSprImg_Vtx_Shader.glsl");
        std::string SquareSprFragmentShaderSrc = Shader::LoadShaderSource("../shaders/SquareSprImg_Frg_Shader.glsl");
        m_SquareSprShader.reset(new Shader(SquareSprVertexShaderSrc, SquareSprFragmentShaderSrc));

        // Font Shaders
        std::string FontVertexShaderSrc = Shader::LoadShaderSource("../shaders/Fonts_Vtx_Shader.glsl");
        std::string FontFragmentShaderSrc = Shader::LoadShaderSource("../shaders/Fonts_Frg_Shader.glsl");
        m_TextShader.reset(new Shader(FontVertexShaderSrc, FontFragmentShaderSrc));

	}

    // Destructor for the Graphics class. Clean up resources if necessary.
    Graphics::~Graphics() {



            

    }


    // Set the grid size (number of rows and columns) for rendering.
    void Graphics::SetGridSize(int GridSize) {

        cols = GridSize;
        rows = GridSize;

    }

	// Renders the background with a repeated image with the texture provided.
	void Graphics::DrawBackground(const uint32_t texture) {


		glm::vec3 Pos{ (TotalWidth / 2.f) -(TileWidth / 2.f)  , -(TotalHeight / 2.f) + (TileHeight / 2.f), 0.0f};
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Pos);
		transform = glm::scale(transform, glm::vec3(TotalWidth / 2.f , TotalHeight / 2.f, 1.0f));
        transform = mProj * m_camera->getViewMatrix() * transform;
		Renderer::BackgroundSubmit(m_SquareImgVA, m_BackgroundImgShader, transform, texture, cols, rows);
		
	}

    // Renders a grid overlay on the screen based on the current grid size.
	void Graphics::ShowGrid() {
        


        float xOffset = TileWidth;
            //TileWidth;
            
		float yOffset = TileHeight;

        float xMax = (TotalWidth / 2.f);
		float xMin = -xMax;

		float yMax = TotalHeight / 2.f;
		float yMin = -yMax;

        // Creates all the Vertical Lines
		for (float x = xMin; x < (xMax + xOffset); x += xOffset ) {

			glm::vec3 LinePos{ x + (TotalWidth - TileWidth) / 2.f ,-(TotalHeight - TileHeight) / 2.f,0.0f };
			float LineAngle{ 90.0f };
			glm::mat4 transform = glm::translate(glm::mat4(1.0), LinePos);
			transform = glm::rotate(transform, glm::radians(LineAngle), glm::vec3(0, 0, 1));
            transform = glm::scale(transform, glm::vec3(TotalWidth / 2.f, 0.5f * TotalHeight / 2.f, 1.0f));
            transform = mProj * m_camera->getViewMatrix() * transform;
			Renderer::Submit(m_LineVA, m_LineShader, transform);
		}

        // Creates all the Horizontal Lines
		for (float y = yMin; y < (yMax + yOffset); y += yOffset) {

			glm::vec3 LinePos{ (TotalWidth - TileWidth) / 2.f, y - (TotalHeight - TileHeight) / 2.f, 0.0f};
			float LineAngle{ 0.0f };
			glm::mat4 transform = glm::translate(glm::mat4(1.0), LinePos);		
			transform = glm::rotate(transform, glm::radians(LineAngle), glm::vec3(0, 0, 1));
            transform = glm::scale(transform, glm::vec3(TotalWidth / 2.f, 0.5f * TotalHeight / 2.f, 1.0f));
            transform = mProj * m_camera->getViewMatrix() * transform;
			Renderer::Submit(m_LineVA, m_LineShader, transform);
		}
	}


    // Draws a square object at the specified position with optional rotation and texture.
	void Graphics::DrawSquareObject(const float PosX, const float PosY, const float Scale, const float angle, const uint32_t texture, const bool ShowBoundingBox) {


        float scale = Scale / 2.f;


        float x = (PosX * TileWidth);

        float y = -(PosY * TileHeight);



		glm::vec3 Pos{ x,y ,0.0f };
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Pos);
        transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0, 0, 1));
		transform = glm::scale(transform, glm::vec3(TileWidth * scale, TileHeight * scale,1.0f));
        transform = mProj * m_camera->getViewMatrix() * transform;
		Renderer::Submit(m_SquareImgVA, m_SquareImgShader, transform, texture);



        // Draws the square bounding box if required.
		if (ShowBoundingBox) {

            
            glLineWidth(3.f);

            float LineAngle{ 90.0f };
            float halfWidth = TileWidth / 2.f;
                //(2.f / (float)cols);
            float halfHeight = TileHeight / 2.f;
                //2.f / (float)rows;


            glm::vec3 Pos1 = glm::vec3(
                x + halfWidth * cos(glm::radians(angle)),
                y + halfWidth * sin(glm::radians(angle)),
                0.0f
            );
            glm::mat4 transform1 = glm::translate(glm::mat4(1.0f), Pos1);
            transform1 = glm::rotate(transform1, glm::radians(angle + LineAngle), glm::vec3(0, 0, 1));
            transform1 = glm::scale(transform1, glm::vec3(TileWidth * scale, TileHeight * scale, 1.0f));   
            transform1 = mProj * m_camera->getViewMatrix() * transform1;
            Renderer::Submit(m_LineVA, m_BoundingLineShader, transform1);


            glm::vec3 Pos2 = glm::vec3(
                x - halfWidth * cos(glm::radians(angle)),
                y - halfWidth * sin(glm::radians(angle)),
                0.0f
            );
            glm::mat4 transform2 = glm::translate(glm::mat4(1.0f), Pos2);
            transform2 = glm::rotate(transform2, glm::radians(angle + LineAngle), glm::vec3(0, 0, 1));
            transform2 = glm::scale(transform2, glm::vec3(TileWidth * scale, TileHeight * scale, 1.0f));
            transform2 = mProj * m_camera->getViewMatrix() * transform2;
            Renderer::Submit(m_LineVA, m_BoundingLineShader, transform2);


            glm::vec3 Pos3 = glm::vec3(
                x + halfWidth * cos(glm::radians(angle + LineAngle)),
                y + halfWidth * sin(glm::radians(angle + LineAngle)),
                0.0f
            );
            glm::mat4 transform3 = glm::translate(glm::mat4(1.0f), Pos3);
            transform3 = glm::rotate(transform3, glm::radians(angle), glm::vec3(0, 0, 1));
            transform3 = glm::scale(transform3, glm::vec3(TileWidth * scale, TileHeight * scale, 1.0f));   
            transform3 = mProj * m_camera->getViewMatrix() * transform3;
            Renderer::Submit(m_LineVA, m_BoundingLineShader, transform3);


            glm::vec3 Pos4 = glm::vec3(
                x - halfWidth * cos(glm::radians(angle + LineAngle)),
                y - halfWidth * sin(glm::radians(angle + LineAngle)),
                0.0f
            );
            glm::mat4 transform4 = glm::translate(glm::mat4(1.0f), Pos4);
            transform4 = glm::rotate(transform4, glm::radians(angle), glm::vec3(0, 0, 1));
            transform4 = glm::scale(transform4, glm::vec3(TileWidth * scale, TileHeight * scale, 1.0f));
            transform4 = mProj * m_camera->getViewMatrix() * transform4;
            Renderer::Submit(m_LineVA, m_BoundingLineShader, transform4);


            glLineWidth(1.f);
		}

	}


    void Graphics::UpdateCameraPos(float x, float y) {

        m_camera->UpdateCamPos(x * TileWidth, y * TileHeight);

    }

    void Graphics::UpdateCameraZoom(float zoom) {

        m_camera->UpdateCamZoom(zoom);

    }




    // Draws a square object at the specified position with optional rotation and texture.
    void Graphics::DrawAnimatedSquareObject(const float PosX, const float PosY, const float Scale, const float angle, const uint32_t texture, const bool ShowBoundingBox, float dt) {


        float scale = Scale / 2.f;


        float x = (PosX * TileWidth);

        float y = -(PosY * TileHeight);



        glm::vec3 Pos{ x,y ,0.0f };
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), Pos);
        transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0, 0, 1));
        transform = glm::scale(transform, glm::vec3(TileWidth * scale, TileHeight * scale, 1.0f));
        transform = mProj * m_camera->getViewMatrix() * transform;
        Renderer::Submit(m_SquareImgVA, m_SquareImgShader, transform, texture);



        // Draws the square bounding box if required.
        if (ShowBoundingBox) {


            glLineWidth(3.f);

            float LineAngle{ 90.0f };
            float halfWidth = TileWidth / 2.f;
            //(2.f / (float)cols);
            float halfHeight = TileHeight / 2.f;
            //2.f / (float)rows;


            glm::vec3 Pos1 = glm::vec3(
                x + halfWidth * cos(glm::radians(angle)),
                y + halfWidth * sin(glm::radians(angle)),
                0.0f
            );
            glm::mat4 transform1 = glm::translate(glm::mat4(1.0f), Pos1);
            transform1 = glm::rotate(transform1, glm::radians(angle + LineAngle), glm::vec3(0, 0, 1));
            transform1 = glm::scale(transform1, glm::vec3(TileWidth * scale, TileHeight * scale, 1.0f));
            transform1 = mProj * m_camera->getViewMatrix() * transform1;
            Renderer::Submit(m_LineVA, m_BoundingLineShader, transform1);


            glm::vec3 Pos2 = glm::vec3(
                x - halfWidth * cos(glm::radians(angle)),
                y - halfWidth * sin(glm::radians(angle)),
                0.0f
            );
            glm::mat4 transform2 = glm::translate(glm::mat4(1.0f), Pos2);
            transform2 = glm::rotate(transform2, glm::radians(angle + LineAngle), glm::vec3(0, 0, 1));
            transform2 = glm::scale(transform2, glm::vec3(TileWidth * scale, TileHeight * scale, 1.0f));
            transform2 = mProj * m_camera->getViewMatrix() * transform2;
            Renderer::Submit(m_LineVA, m_BoundingLineShader, transform2);


            glm::vec3 Pos3 = glm::vec3(
                x + halfWidth * cos(glm::radians(angle + LineAngle)),
                y + halfWidth * sin(glm::radians(angle + LineAngle)),
                0.0f
            );
            glm::mat4 transform3 = glm::translate(glm::mat4(1.0f), Pos3);
            transform3 = glm::rotate(transform3, glm::radians(angle), glm::vec3(0, 0, 1));
            transform3 = glm::scale(transform3, glm::vec3(TileWidth * scale, TileHeight * scale, 1.0f));
            transform3 = mProj * m_camera->getViewMatrix() * transform3;
            Renderer::Submit(m_LineVA, m_BoundingLineShader, transform3);


            glm::vec3 Pos4 = glm::vec3(
                x - halfWidth * cos(glm::radians(angle + LineAngle)),
                y - halfWidth * sin(glm::radians(angle + LineAngle)),
                0.0f
            );
            glm::mat4 transform4 = glm::translate(glm::mat4(1.0f), Pos4);
            transform4 = glm::rotate(transform4, glm::radians(angle), glm::vec3(0, 0, 1));
            transform4 = glm::scale(transform4, glm::vec3(TileWidth * scale, TileHeight * scale, 1.0f));
            transform4 = mProj * m_camera->getViewMatrix() * transform4;
            Renderer::Submit(m_LineVA, m_BoundingLineShader, transform4);


            glLineWidth(1.f);
        }

    }






    // Draws a square animation frame at the specified position using the provided vertex array, shader, and texture.
	void DrawSquareAnimation(float PosX, float PosY, std::shared_ptr<VertexArray> VA, std::shared_ptr<Shader> shader, uint32_t texture) {

		float x = (PosX * 0.2f) - 0.9f;
		float y = -(PosX * 0.2f) + 0.9f;


		glm::vec3 Pos{ x,y ,0.0f };
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Pos);
		transform = glm::scale(transform, glm::vec3(0.1f, 0.1f, 1.0f));
		Renderer::Submit(VA, shader, transform, texture);

	}


    // Draws a square animation frame at the specified position using the provided vertex array, shader, and texture.
	void Graphics::DrawAnimation(float x, float y,float Scale,float angle, uint32_t texture, int numRows, int numCols, float dt, const bool ShowBoundingBox) {

        float scale = Scale / 2.f;



        //timeNow += 0.1f;
        //timeDelta = timeNow - timeOld;

        //if (timeDelta >= SPframe) {

        //    timeOld = timeNow;
        //    timeDelta = 0.f;
        //    uv_x += 1.f/numCols;

        //    if (uv_x >= numRows) {

        //        uv_x = 0.f;
        //        //uv_y += 1.f;

        //        //if (uv_y >= numCols) {

        //        //    uv_y = 0.f;
        //        //}

        //    }


        //}


        timeNow = glfwGetTime();
        timeDelta = timeNow - timeOld;
        if(timeDelta >= 1.0f / SPframe) {
            timeOld = timeNow;
            timeDelta = 0.0f;
            uv_x += 1.0f;
            if(uv_x >= numCols) {
                uv_x = 0.0f;
            }
        }


        glm::vec3 Pos{ x,y ,0.0f };
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), Pos);
        transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0, 0, 1));
        transform = glm::scale(transform, glm::vec3(TileWidth * scale, TileHeight * scale, 1.0f));
        transform = mProj * m_camera->getViewMatrix() * transform;


        m_SquareSprShader->Bind();
        //glBindTexture(GL_TEXTURE_2D, texture);
        //m_SquareSprShader->UploadUniformFloat("x_dir", x);
        //m_SquareSprShader->UploadUniformFloat("y_dir", y);
        m_SquareSprShader->UploadUniformFloat("uv_x", uv_x);
        m_SquareSprShader->UploadUniformFloat("uv_y", uv_y);
        m_SquareSprShader->UploadUniformFloat("nx_frames", numCols);
        m_SquareSprShader->UploadUniformFloat("ny_frames", numRows);
        m_SquareSprShader->UploadUniformMat4("u_Transform", transform);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        m_SquareSprShader->UploadUniformInt("u_Tex", 0);


        m_SquareSprVA->Bind();


        RenderCommand::DrawIndex(m_SquareSprVA);




        //Renderer::Submit(m_SquareSprVA, m_SquareSprShader, transform, texture);
        
        //
        //m_SquareSprVA->Bind();

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //m_SquareSprShader->Unbind();






        // Draws the square bounding box if required.
        if (ShowBoundingBox) {


            glLineWidth(3.f);

            float LineAngle{ 90.0f };
            float halfWidth = TileWidth / 2.f;
            //(2.f / (float)cols);
            float halfHeight = TileHeight / 2.f;
            //2.f / (float)rows;


            glm::vec3 Pos1 = glm::vec3(
                x + halfWidth * cos(glm::radians(angle)),
                y + halfWidth * sin(glm::radians(angle)),
                0.0f
            );
            glm::mat4 transform1 = glm::translate(glm::mat4(1.0f), Pos1);
            transform1 = glm::rotate(transform1, glm::radians(angle + LineAngle), glm::vec3(0, 0, 1));
            transform1 = glm::scale(transform1, glm::vec3(TileWidth * scale, TileHeight * scale, 1.0f));
            transform1 = mProj * m_camera->getViewMatrix() * transform1;
            Renderer::Submit(m_LineVA, m_BoundingLineShader, transform1);


            glm::vec3 Pos2 = glm::vec3(
                x - halfWidth * cos(glm::radians(angle)),
                y - halfWidth * sin(glm::radians(angle)),
                0.0f
            );
            glm::mat4 transform2 = glm::translate(glm::mat4(1.0f), Pos2);
            transform2 = glm::rotate(transform2, glm::radians(angle + LineAngle), glm::vec3(0, 0, 1));
            transform2 = glm::scale(transform2, glm::vec3(TileWidth * scale, TileHeight * scale, 1.0f));
            transform2 = mProj * m_camera->getViewMatrix() * transform2;
            Renderer::Submit(m_LineVA, m_BoundingLineShader, transform2);


            glm::vec3 Pos3 = glm::vec3(
                x + halfWidth * cos(glm::radians(angle + LineAngle)),
                y + halfWidth * sin(glm::radians(angle + LineAngle)),
                0.0f
            );
            glm::mat4 transform3 = glm::translate(glm::mat4(1.0f), Pos3);
            transform3 = glm::rotate(transform3, glm::radians(angle), glm::vec3(0, 0, 1));
            transform3 = glm::scale(transform3, glm::vec3(TileWidth * scale, TileHeight * scale, 1.0f));
            transform3 = mProj * m_camera->getViewMatrix() * transform3;
            Renderer::Submit(m_LineVA, m_BoundingLineShader, transform3);


            glm::vec3 Pos4 = glm::vec3(
                x - halfWidth * cos(glm::radians(angle + LineAngle)),
                y - halfWidth * sin(glm::radians(angle + LineAngle)),
                0.0f
            );
            glm::mat4 transform4 = glm::translate(glm::mat4(1.0f), Pos4);
            transform4 = glm::rotate(transform4, glm::radians(angle), glm::vec3(0, 0, 1));
            transform4 = glm::scale(transform4, glm::vec3(TileWidth * scale, TileHeight * scale, 1.0f));
            transform4 = mProj * m_camera->getViewMatrix() * transform4;
            Renderer::Submit(m_LineVA, m_BoundingLineShader, transform4);


            glLineWidth(1.f);
        }



	}




    // (NOTE: Coordinates are in window coordinates and not in tile coordinate) 
    // Draws a square object at the specified position with optional rotation and texture. 
    void Graphics::DrawUISquareObject(const float PosX, const float PosY, const float Scale, const float angle, const float ObjHeight, const float ObjWidth, const uint32_t texture) {


        float scale = Scale / 2.f;


        float x = PosX;

        float y = -PosY;



        glm::vec3 Pos{ x,y ,0.0f };
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), Pos);
        transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0, 0, 1));
        transform = glm::scale(transform, glm::vec3(ObjWidth * scale, ObjHeight * scale, 1.0f));
        transform = mProj * m_UIcamera->getViewMatrix() * transform;
        Renderer::Submit(m_SquareImgVA, m_SquareImgShader, transform, texture);



    }

        int Graphics::LoadFont(std::string filepath) {

            // FreeType
                // --------
                FT_Library ft;
            // All functions return a value different than 0 whenever an error occurred

                
            if (FT_Init_FreeType(&ft))
            {
                std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
                return -1;
            }

            // load font as face
            FT_Face face;
            if (FT_New_Face(ft, filepath.c_str(), 0, &face)) {
                std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
                return -1;
            }
            else {
                // set size to load glyphs as
                FT_Set_Pixel_Sizes(face, 0, 100);

                // disable byte-alignment restriction
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

                // load first 128 characters of ASCII set
                for (unsigned char c = 0; c < 128; c++)
                {
                    // Load character glyph 
                    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                    {
                        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                        continue;
                    }
                    // generate texture
                    unsigned int texture;
                    glGenTextures(1, &texture);
                    glBindTexture(GL_TEXTURE_2D, texture);
                    glTexImage2D(
                        GL_TEXTURE_2D,
                        0,
                        GL_RED,
                        face->glyph->bitmap.width,
                        face->glyph->bitmap.rows,
                        0,
                        GL_RED,
                        GL_UNSIGNED_BYTE,
                        face->glyph->bitmap.buffer
                    );
                    // set texture options
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    // now store character for later use
                    Graphics::Character character = {
                        texture,
                        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                        static_cast<unsigned int>(face->glyph->advance.x)
                    };
                    Characters.insert(std::pair<char, Graphics::Character>(c, character));
                }

                glBindTexture(GL_TEXTURE_2D, 0);

            }

            // destroy FreeType once we're finished
            FT_Done_Face(face);
            FT_Done_FreeType(ft);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



            // configure VAO/VBO for texture quads
            // -----------------------------------
            glGenVertexArrays(1, &m_TextVA);
            glGenBuffers(1, &m_TextVB);
            glBindVertexArray(m_TextVA);
            glBindBuffer(GL_ARRAY_BUFFER, m_TextVB);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);




       }



        void Graphics::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
        {

            // activate corresponding render state	
            m_TextShader->Bind();
            m_TextShader->UploadUniform3f("textColor", color);
            m_TextShader->UploadUniformMat4("projection", glm::mat4(glm::ortho(0.f,800.f,0.f,800.f)));
            //glUniform3f(glGetUniformLocation(s.Program, "textColor"), color.x, color.y, color.z);
            glActiveTexture(GL_TEXTURE0);
            glBindVertexArray(m_TextVA);

            // iterate through all characters
            std::string::const_iterator c;
            for (c = text.begin(); c != text.end(); c++)
            {
                Character ch = Characters[*c];

                float xpos = x + ch.Bearing.x * scale;
                float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

                float w = ch.Size.x * scale;
                float h = ch.Size.y * scale;
                // update VBO for each character
                float vertices[6][4] = {
                    { xpos,     ypos + h,   0.0f, 0.0f },
                    { xpos,     ypos,       0.0f, 1.0f },
                    { xpos + w, ypos,       1.0f, 1.0f },

                    { xpos,     ypos + h,   0.0f, 0.0f },
                    { xpos + w, ypos,       1.0f, 1.0f },
                    { xpos + w, ypos + h,   1.0f, 0.0f }
                };
                // render glyph texture over quad
                glBindTexture(GL_TEXTURE_2D, ch.TextureID);
                // update content of VBO memory
                glBindBuffer(GL_ARRAY_BUFFER, m_TextVB);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                // render quad
                glDrawArrays(GL_TRIANGLES, 0, 6);
                // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
                x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
            }
            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);
            m_TextShader->Unbind();
        }






}

