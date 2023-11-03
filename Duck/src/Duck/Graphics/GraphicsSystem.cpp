//---------------------------------------------------------
// File:		GraphicsSystem.cpp
// 
// authors:		Kristy Lee Yu Xuan
// email:		kristyyuxuan.lee\@digipen.edu
//
// Brief:       This file defines the functions in the Graphics System class.
//
// Copyright ? 2023 DigiPen, All rights reserved.
//-------------------------------------------------------
#include "duckpch.h"

#include "Duck/KeyCodes.h"
#include "Duck/Platform/Windows/WindowsInput.h"

#include "GraphicsComponent.h"
#include "GraphicsSystem.h"
#include "Graphics.h"
#include "Shader.h"

namespace Duck
{

	void GraphicsSystem::Init()
	{
		graphicsUnique = std::make_unique<Graphics>(Application::Get().GetWindow());
	}

	void GraphicsSystem::Update()
	{
		//RenderCommand::SetClearColor({ 0.2, 0.2, 0.2, 1 });
		//RenderCommand::Clear();
		for (auto& entity : m_Entities)
		{
			auto& graphicObj = ecs.getComponent<GraphicsComponent>(entity);
			auto& gameObj = ecs.getComponent<GameObject>(entity);

			//loading 
			if (!graphicObj.GetLoaded())
			{
				//load textures
				std::string name = graphicObj.GetName();
				std::string path = graphicObj.GetPath();
				if (graphicObj.GetGraphicsType() == GRAPHICS_TEXTURE)
				{
					graphicObj.SetID(Shader::LoadTexture(path.c_str()));
					graphicObj.SetLoaded(true);
				}

				//load fonts
				if (graphicObj.GetGraphicsType() == GRAPHICS_FONT)
				{
					graphicsUnique->LoadFont(path.c_str(), name.c_str());
					graphicObj.SetLoaded(true);
				}
			}

			//draw objects
			graphicsUnique->StartScene();

			//drawing textures
			if (graphicObj.GetGraphicsType() == GRAPHICS_TEXTURE)
			{
				/*if (graphicObj.GetName() == "player" && gameObj.getObj() == OBJ_PLAYER)
				{
					graphicsUnique->DrawSquareObject(gameObj.getX(), gameObj.getY(), cellSize, (float)gameObj.getOrientation(), graphicObj.GetID(), graphicObj.GetBB());
				}*/
			}
			
			//drawing text
			if (graphicObj.GetGraphicsType() == GRAPHICS_FONT)
			{
				graphicsUnique->RenderText("Inventory", 290.f, 90.f, 0.3f, glm::vec3(1.f, 1.f, 1.f), "Mine");
			}

			//update camera
			if (gameObj.getObj() == OBJ_PLAYER)
			{
				//graphicsUnique->UpdateCameraPos(gameObj.getX(), gameObj.getY());
			}

			graphicsUnique->EndScene();
		}
	}

}