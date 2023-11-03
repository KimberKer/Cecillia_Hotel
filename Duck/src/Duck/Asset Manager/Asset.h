//---------------------------------------------------------
// File:    Asset.h
//authors:	Kimber Ker Soon Kiat
// email:	s.ker\@digipen.edu
// 
//
// Brief:     Contain the declaration for Asset
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------
#ifndef ASSET_H
#define ASSET_H

#include <string>

enum class AssetType {
    Texture,
    Audio,
    Model,
};

class Asset {
public:
    Asset(const std::string& name, const std::string& filePath, AssetType type);
    std::string GetName() const;
    std::string GetFilePath() const;
    AssetType GetType() const;

private:
    std::string name;
    std::string filePath;
    AssetType type;
};

#endif // ASSET_H
