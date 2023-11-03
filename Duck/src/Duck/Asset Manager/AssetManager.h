//---------------------------------------------------------
// File:    AssetManager.h
//authors:	Kimber Ker Soon Kiat
// email:	s.ker\@digipen.edu
// 
//
// Brief:     Contain the function for AssetManager
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------
#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <memory>
#include "Asset.h"

class AssetManager {
public:
    // Load an asset
    std::shared_ptr<Asset> LoadAsset(const std::string& name, const std::string& filePath, AssetType type);

    // Get an asset
    std::shared_ptr<Asset> GetAsset(const std::string& name);

    // Unload an asset
    void UnloadAsset(const std::string& name);

private:
    std::map<std::string, std::shared_ptr<Asset>> assetDatabase;
};

#endif // ASSETMANAGER_H
