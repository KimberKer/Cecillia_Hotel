//---------------------------------------------------------
// File:    AssetManager.cpp
//authors:	Kimber Ker Soon Kiat
// email:	s.ker\@digipen.edu
// 
//
// Brief:   Contain function for AssetManager. To load, get and unload assets.
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "duckpch.h"
#include "AssetManager.h"

std::shared_ptr<Asset> AssetManager::LoadAsset(const std::string& name, const std::string& filePath, AssetType type) {
    // Check if the asset already exists in the database
    auto it = assetDatabase.find(name);
    if (it != assetDatabase.end()) {
        // Asset already loaded, return it
        return it->second;
    }

    // Load the asset (implementation depends on the type)
    // Example: Load a texture, audio, or model here
    // Add error handling and loading logic specific to each asset type

    // Create and store the asset in the database
    std::shared_ptr<Asset> asset = std::make_shared<Asset>(name, filePath, type);
    assetDatabase[name] = asset;

    return asset;
}

std::shared_ptr<Asset> AssetManager::GetAsset(const std::string& name) {
    auto it = assetDatabase.find(name);
    if (it != assetDatabase.end()) {
        return it->second;
    }
    return nullptr; // Asset not found
}

void AssetManager::UnloadAsset(const std::string& name) {
    auto it = assetDatabase.find(name);
    if (it != assetDatabase.end()) {
        assetDatabase.erase(it);
    }
}
