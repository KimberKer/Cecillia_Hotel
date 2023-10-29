#include "AssetManager.h"

void AssetManager::LoadAsset(const std::string& name, AssetType type, const std::string& path) {
    assets[name] = Asset(type, path);
}

Asset AssetManager::GetAsset(const std::string& name) {
    if (assets.find(name) != assets.end()) {
        return assets[name];
    }
    else {
        // Handle missing asset
        return Asset(AssetType::Sprite, "missing.png");
    }
}
