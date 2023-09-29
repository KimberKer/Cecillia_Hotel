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
#include "Duck/Application.h"


namespace Duck {

    class DUCK_API Graphics {

    public:

        // Constructor for the Graphics class.
        Graphics();

        // Destructor for the Graphics class.
        virtual ~Graphics();

        // Factory method to create an instance of the Graphics class.
        static Graphics* Create();


		virtual void SetGridSize(int GridSize);

        // Renders the background with a repeated image using the provided texture.
        virtual void DrawBackground(const uint32_t texture);

        // Renders a grid overlay on the screen based on the current grid size.
        virtual void ShowGrid();

        // Draws a square object at the specified position with optional rotation and texture.
        virtual void DrawSquareObject(const float PosX, const float PosY, const float scale, const float angle, const uint32_t texture, const bool ShowBoundingBox);

    private:

		int cols;
		int rows;

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
    };
	

}