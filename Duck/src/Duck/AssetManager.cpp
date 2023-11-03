//---------------------------------------------------------
// File:    AssetManager.cpp
//authors:	Ahmad Mahdi Bin Jamal
// email:	ahmadmahdi.b@digipen.edu
// 
//
// Brief:   Implementation file for the AssetManager class, responsible for 
//          loading and managing assets, such as textures, in the Duck 
//          game engine. It utilizes the Graphics and Shader components 
//          to handle the loading of image assets and provides access to 
//          the loaded textures.
// 
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "duckpch.h"
#include "AssetManager.h"
#include "Graphics/Shader.h"
#include "Graphics/Graphics.h"

namespace Duck {


	// Constructor
	AssetManager::AssetManager() {

	}

	
	// Destructor
	AssetManager::~AssetManager() {

	}
 

	// Load assets, including textures, from the specified directory
	void AssetManager::LoadAssets() {


		
		///////////////////////////    Load Texures    ///////////////////////////

		
		// Load textures from the "assets/images/" directory
		// and store them in the TextureList map
		static std::vector<std::filesystem::directory_entry> assetEntries;
		static std::filesystem::path currentAssetDirectory("../assets/images/");
		//std::vector<uint32_t> assets;
		for (const auto& entry : std::filesystem::directory_iterator(currentAssetDirectory)) {
			assetEntries.push_back(entry);
		}
		for (int i = 0; i < assetEntries.size(); i++) {
			uint32_t asset{};
			std::filesystem::path entryPath = assetEntries[i].path();
			std::string assetName = entryPath.filename().string();

			std::string image = "../assets/images/" + assetName;

			asset = Duck::Shader::LoadTexture(image.c_str());

			TextureList.insert(std::pair<std::string, uint32_t>(assetName, asset));

		}


	}


	// Get the map containing the names and IDs of loaded textures
	std::map<std::string, uint32_t>& AssetManager::GetTextureList() {

		return TextureList;

	}

	// Get the ID of a specific texture by its asset name
	uint32_t AssetManager::GetTexture(std::string AssetName) {

		// Retrieve the texture ID from the TextureList map
		uint32_t asset = TextureList[AssetName];

		if (asset <= 0) {

			std::cout << "Texture " << AssetName << " was not found!\n";
			return 0;
		}

		return asset;


	}

}

