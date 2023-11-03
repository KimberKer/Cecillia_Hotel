//---------------------------------------------------------
// File:    AssetManager.h
//authors:	Ahmad Mahdi Bin Jamal
// email:	ahmadmahdi.b@digipen.edu
// 
//
// Brief:   Header file for the AssetManager class, which is responsible 
//          for managing and loading assets, such as textures, in the Duck 
//          game engine. The class provides methods to load textures from 
//          a specified directory, retrieve the list of loaded textures, 
//          and obtain the ID of a texture by its asset name.
// 
// 
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include <string>
#include <map>
#include <filesystem>

namespace Duck {

	// AssetManager class declaration
	class AssetManager
	{
	public:
		// Constructor
		AssetManager();
		// Destructor
		~AssetManager();

		// Load assets, including textures, from a specified directory
		void LoadAssets();

		// Get the map containing the names and IDs of loaded textures
		std::map<std::string, uint32_t>& GetTextureList();

		// Get the ID of a specific texture by its asset name
		uint32_t GetTexture(std::string AssetName);


	private:

		// Map to store loaded textures with their names and IDs
		std::map<std::string, uint32_t> TextureList;

	};
}

