//---------------------------------------------------------
// File:		GraphicsComponent.cpp
// 
// authors:		Kristy Lee Yu Xuan
// email:		kristyyuxuan.lee\@digipen.edu
//
// Brief:       This file declares the functions in the GraphicsComponent class.
//
// Copyright ? 2023 DigiPen, All rights reserved.
//-------------------------------------------------------
#pragma once

#include "Graphics.h"
#include <memory>

enum GraphicsType
{
	GRAPHICS_NONE,
	GRAPHICS_TEXTURE,
	GRAPHICS_FONT,
	GRAPHICS_CAMERA
};


namespace Duck
{
	class GraphicsComponent
	{
	public:
		GraphicsComponent() = default;
		GraphicsComponent(GraphicsType type, std::string name, std::string path) : graphicsType(type), filename(name), filepath(path) {}
		
		GraphicsType GetGraphicsType() { return graphicsType; }
		
		std::string GetPath() const { return filepath; }
		std::string GetName() const { return filename; }
		
		uint32_t GetID() const { return ID; }
		void SetID(uint32_t txt) { ID = txt; }
		
		bool GetLoaded() const { return loaded; }
		void SetLoaded(bool load) { loaded = load; }
		
		bool GetBB() const { return showBB; }
		void SetBB(bool bb) { showBB = bb; }
	private:
		
		GraphicsType graphicsType = GRAPHICS_NONE;
		
		std::string filepath{};
		std::string filename{};
		
		uint32_t ID = 0;
		
		bool loaded = false;
		bool showBB = false;
	};
}