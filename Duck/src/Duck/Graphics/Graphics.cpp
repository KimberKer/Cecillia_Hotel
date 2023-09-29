#include "duckpch.h"
#include "Graphics.h"
#include <glad/glad.h>
#include "Duck/Window.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Duck {


	Graphics::Graphics() {

        // Default Grid Size

        cols = 12;
        rows = 12;


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
        std::string SquareSprVertexShaderSrc = Shader::LoadShaderSource("../shaders/SquareSpr_Vtx_Shader.glsl");
        std::string SquareSprFragmentShaderSrc = Shader::LoadShaderSource("../shaders/SquareSpr_Frg_Shader.glsl");
        m_SquareSprShader.reset(new Shader(SquareSprVertexShaderSrc, SquareSprFragmentShaderSrc));

	}


    Graphics::~Graphics() {



    }


    Graphics* Graphics::Create() {

        return new Graphics();

    }

    void Graphics::SetGridSize(int GridSize) {

        cols = GridSize;
        rows = GridSize;

    }


	// Renders the background with a repeated image with the texture provided.
	void Graphics::DrawBackground(const uint32_t texture) {


		glm::vec3 Pos{ 0.0f, 0.0f, 0.0f };
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Pos);
		transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));
		Renderer::BackgroundSubmit(m_SquareImgVA, m_BackgroundImgShader, transform, texture, cols, rows);
		
	}

	void Graphics::ShowGrid() {



		float xOffset = 2.f / (float)cols;
		float yOffset = 2.f / (float)rows;

		float xMax = (float)2.f / 2.f;
		float xMin = -xMax;

		float yMax = (float)2.f / 2.f;
		float yMin = -yMax;

		for (float x = xMin; x <= (xMax + xOffset); x += xOffset) {

			glm::vec3 LinePos{ x,0.0f,0.0f };
			float LineAngle{ 90.0f };
			glm::mat4 transform = glm::translate(glm::mat4(1.0), LinePos);
			transform = glm::scale(transform, glm::vec3(0.5f, 1.0f, 1.0f));
			transform = glm::rotate(transform, glm::radians(LineAngle), glm::vec3(0, 0, 1));

			Renderer::Submit(m_LineVA, m_LineShader, transform);
		}

		for (float y = yMin; y <= (yMax + yOffset); y += yOffset) {

			glm::vec3 LinePos{ 0.0f, y, 0.0f };
			float LineAngle{ 0.0f };
			glm::mat4 transform = glm::translate(glm::mat4(1.0), LinePos);
			transform = glm::scale(transform, glm::vec3(1.0f, 0.5f, 1.0f));
			transform = glm::rotate(transform, glm::radians(LineAngle), glm::vec3(0, 0, 1));

			Renderer::Submit(m_LineVA, m_LineShader, transform);
		}
	}



	void Graphics::DrawSquareObject(const float PosX, const float PosY, const float Scale, const float angle, const uint32_t texture, const bool ShowBoundingBox) {

		float TileWidth = 2.f / cols;
		float TileHeight = 2.f / rows;
        float scale = Scale / 2.f;


        float x = (PosX * TileWidth) - (1.0f - (TileWidth / 2.0f));
		float y = -(PosY * TileHeight) + (1.0f - (TileHeight / 2.0f));


		glm::vec3 Pos{ x,y ,0.0f };
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Pos);
        transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0, 0, 1));
		transform = glm::scale(transform, glm::vec3(TileWidth * scale, TileHeight * scale,1.0f));
		Renderer::Submit(m_SquareImgVA, m_SquareImgShader, transform, texture);

		if (ShowBoundingBox) {

            
            glLineWidth(3.f);

            float LineAngle{ 90.0f };
            float halfWidth = TileWidth * scale;
            float halfHeight = TileHeight * scale;

            glm::vec3 Pos1 = glm::vec3(
                x + halfWidth * cos(glm::radians(angle)),
                y + halfWidth * sin(glm::radians(angle)),
                0.0f
            );
            glm::mat4 transform1 = glm::translate(glm::mat4(1.0f), Pos1);
            transform1 = glm::rotate(transform1, glm::radians(angle + LineAngle), glm::vec3(0, 0, 1));
            transform1 = glm::scale(transform1, glm::vec3(TileWidth * scale, TileHeight * scale, 1.0f));            
            Renderer::Submit(m_LineVA, m_BoundingLineShader, transform1);

            glm::vec3 Pos2 = glm::vec3(
                x - halfWidth * cos(glm::radians(angle)),
                y - halfWidth * sin(glm::radians(angle)),
                0.0f
            );
            glm::mat4 transform2 = glm::translate(glm::mat4(1.0f), Pos2);
            transform2 = glm::rotate(transform2, glm::radians(angle + LineAngle), glm::vec3(0, 0, 1));
            transform2 = glm::scale(transform2, glm::vec3(TileWidth * scale, TileHeight * scale, 1.0f));      
            Renderer::Submit(m_LineVA, m_BoundingLineShader, transform2);

            glm::vec3 Pos3 = glm::vec3(
                x + halfWidth * cos(glm::radians(angle + LineAngle)),
                y + halfWidth * sin(glm::radians(angle + LineAngle)),
                0.0f
            );
            glm::mat4 transform3 = glm::translate(glm::mat4(1.0f), Pos3);
            transform3 = glm::rotate(transform3, glm::radians(angle), glm::vec3(0, 0, 1));
            transform3 = glm::scale(transform3, glm::vec3(TileWidth * scale, TileHeight * scale, 1.0f));            
            Renderer::Submit(m_LineVA, m_BoundingLineShader, transform3);

            glm::vec3 Pos4 = glm::vec3(
                x - halfWidth * cos(glm::radians(angle + LineAngle)),
                y - halfWidth * sin(glm::radians(angle + LineAngle)),
                0.0f
            );
            glm::mat4 transform4 = glm::translate(glm::mat4(1.0f), Pos4);
            transform4 = glm::rotate(transform4, glm::radians(angle), glm::vec3(0, 0, 1));
            transform4 = glm::scale(transform4, glm::vec3(TileWidth * scale, TileHeight * scale, 1.0f));      
            Renderer::Submit(m_LineVA, m_BoundingLineShader, transform4);


            glLineWidth(1.f);
		}

	}














	void DrawSquareAnimation(float PosX, float PosY, std::shared_ptr<VertexArray> VA, std::shared_ptr<Shader> shader, uint32_t texture) {

		float x = (PosX * 0.2f) - 0.9f;
		float y = -(PosX * 0.2f) + 0.9f;


		glm::vec3 Pos{ x,y ,0.0f };
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Pos);
		transform = glm::scale(transform, glm::vec3(0.1f, 0.1f, 1.0f));
		Renderer::Submit(VA, shader, transform, texture);

	}




	void DrawAnimation(GLuint texture, int numRows, int numCols, float dt) {
		static float frameTime = 0.1f; // Time in seconds per frame
		static int currentFrame = 0;

		// Update current frame based on elapsed time
		frameTime -= dt;
		if (frameTime <= 0.0f) {
			currentFrame = (currentFrame + 1) % (numRows * numCols);
			frameTime = 0.1f; // Reset frame time
		}

		// Calculate texture coordinates for the current frame
		int row = currentFrame / numCols;
		int col = currentFrame % numCols;
		float frameWidth = 1.0f / numCols;
		float frameHeight = 1.0f / numRows;
		float texCoordX = col * frameWidth;
		float texCoordY = 1.0f - (row + 1) * frameHeight; // Invert Y-axis




	}


		
		
	

}

