#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

enum STATE
{
    STATE_NONE,
    STATE_GOING_LEFT,
    STATE_GOING_RIGHT,
    STATE_GOING_UP,
    STATE_GOING_DOWN,
};

class GameObject {

public:
    GameObject();
    GameObject(float x, float y, float velocityX, float velocityY, STATE state);

    // Getters
    float getX() const;
    float getY() const;
    float getVelocityX() const;
    float getVelocityY() const;
    STATE getState() const;

    void  SetState(STATE state);
    void  SetVelocityX(float velx);
    void  SetVelocityY(float vely);
    void  SetPositionX(float posX);
    void  SetPositionY(float posY);


    // Load object properties from a .txt file
    bool loadFromFile(const std::string& filename);

    // Function to load player data
    void loadPlayerData();

private:
    float x;
    float y;
    float velocityX;
    float velocityY;
    STATE state;
};

#endif
