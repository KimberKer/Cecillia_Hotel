#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>

enum class AssetType {
    Sprite,
    Audio,
};

class Asset {
public:
    Asset(AssetType t, const std::string& p) : type(t), path(p) {}

    AssetType GetType() const { return type; }
    std::string GetPath() const { return path; }

private:
    AssetType type;
    std::string path;
};

class AssetManager {
public:
    void LoadAsset(const std::string& name, AssetType type, const std::string& path);
    Asset GetAsset(const std::string& name);

private:
    std::map<std::string, Asset> assets;
};

#endif
