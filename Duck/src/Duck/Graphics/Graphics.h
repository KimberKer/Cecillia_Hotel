//---------------------------------------------------------
// File:    Graphics.h
//authors:	Ahmad Mahdi Bin Jamal
// email:	ahmadmahdi.b@digipen.edu
// 
//
// Brief:   This file defines the Graphics class, which handles 
//          rendering graphics elements, such as squares, 
//          triangles, and backgrounds, in the Duck game.
//          It provides functions for setting up graphics, 
//          drawing objects, and managing the grid size and 
//          tile width.
// 
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include <memory>
#include "Duck/Window.h"
#include "Duck/Application.h"
#include "Camera.h"
#include <ft2build.h>
#include FT_FREETYPE_H  

namespace Duck {

    class Graphics {

    public:

        // Constructor for the Graphics class.
        Graphics(Window& window);

        // Destructor for the Graphics class.
         ~Graphics();

		 void SetGridSize(int GridSize);

        // Renders the background with a repeated image using the provided texture.
         void DrawBackground(const uint32_t texture);

        // Renders a grid overlay on the screen based on the current grid size.
         void ShowGrid();

        // Draws a square object at the specified position with optional rotation and texture.
         void DrawSquareObject(const float PosX, const float PosY, const float scale, const float angle, const uint32_t texture, const bool ShowBoundingBox);

         void DrawUISquareObject(const float PosX, const float PosY, const float Scale, const float angle, const float ObjHeight, const float ObjWidth, const uint32_t texture);

         void UpdateCameraPos(float x, float y);
         void UpdateCameraZoom( float zoom);

         void DrawAnimation(float x, float y, float scale, float angle, uint32_t texture, int numRows, int numCols, float dt, const bool ShowBoundingBox);

         void LoadFont(std::string filepath, std::string fontKey);
         void RenderText(std::string text, float x, float y, float scale, glm::vec3 color, std::string fontKey);

         void StartScene();
         void EndScene();

        // FONTS
        struct Character {
            unsigned int TextureID;  // ID handle of the glyph texture
            glm::ivec2   Size;       // Size of glyph
            glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
            unsigned int Advance;    // Offset to advance to next glyph
        };



    private:

        Window* m_Window;

		int cols;
		int rows;
        float TileWidth;
        float TileHeight;
        float TotalWidth;
        float TotalHeight;
        float WindowWidth;
        float WindowHeight;
        float uv_x;
        float uv_y;

        glm::mat4 mProj;

        uint32_t m_RendererID{};

        std::shared_ptr<VertexArray> m_TriangleVA;
        std::shared_ptr<Shader> m_TriangleShader;

        std::shared_ptr<VertexArray> m_SquareVA;
        std::shared_ptr<Shader> m_SquareShader;

        std::shared_ptr<VertexArray> m_PointVA;
        std::shared_ptr<Shader> m_PointShader;

        std::shared_ptr<VertexArray> m_LineVA;
        std::shared_ptr<Shader> m_LineShader;
        std::shared_ptr<Shader> m_BoundingLineShader;

        std::shared_ptr<VertexArray> m_SquareImgVA;
        std::shared_ptr<Shader> m_SquareImgShader;
        std::shared_ptr<Shader> m_BackgroundImgShader;

        std::shared_ptr<VertexArray> m_SquareSprVA;
        std::shared_ptr<Shader> m_SquareSprShader;
        float timeOld, timeNow, timeDelta, SPframe;

        unsigned int m_TextVA;
        unsigned int m_TextVB;
        std::shared_ptr<Shader> m_TextShader;

        std::map<std::string, std::map<char, Character>> Fonts;

        std::shared_ptr<Camera> m_camera;
        std::shared_ptr<Camera> m_UIcamera;

        



    };

    

	

    


}