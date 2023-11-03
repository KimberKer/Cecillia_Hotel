//---------------------------------------------------------
// File:    Asset.cpp
//authors:	Kimber Ker Soon Kiat
// email:	s.ker\@digipen.edu
// 
//
// Brief:     Contain the function for Asset. To get the information of the Asset.
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "duckpch.h"
#include "Asset.h"

Asset::Asset(const std::string& name, const std::string& filePath, AssetType type)
    : name(name), filePath(filePath), type(type) {}

std::string Asset::GetName() const {
    return name;
}

std::string Asset::GetFilePath() const {
    return filePath;
}

AssetType Asset::GetType() const {
    return type;
}
