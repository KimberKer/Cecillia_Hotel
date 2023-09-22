#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

class GameObject {
public:
    GameObject();
    GameObject(float x, float y, float velocityX, float velocityY);

    // Getters
    float getX() const;
    float getY() const;
    float getVelocityX() const;
    float getVelocityY() const;

    // Load object properties from a .txt file
    bool loadFromFile(const std::string& filename);

    // Function to load player data
    void loadPlayerData();

private:
    float x;
    float y;
    float velocityX;
    float velocityY;
};

#endif
