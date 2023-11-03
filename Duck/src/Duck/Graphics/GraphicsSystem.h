//---------------------------------------------------------
// File:		GraphicsSystem.h
// 
// authors:		Kristy Lee Yu Xuan
// email:		kristyyuxuan.lee\@digipen.edu
//
// Brief:       This file decalres the functions in the Graphics System class.
//
// Copyright ? 2023 DigiPen, All rights reserved.
//-------------------------------------------------------
#pragma once

#include "Duck/ECS/Entity.h"
#include "Graphics.h"

namespace Duck
{

	class GraphicsSystem : public System
	{
	public:
		using MapList = std::vector<std::shared_ptr<Duck::MapDataHandler>>;

	public:
		void Init();
		void Update();
	
	private:
		std::unique_ptr<Graphics> graphicsUnique = nullptr;
	};

}