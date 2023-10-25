//---------------------------------------------------------
// File:    AI.h
// Authors: Kimber Ker Soon Kiat
// Email:   s.ker\@digipen.edu
//
// Brief:   
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once

#ifndef AI_H
#define AI_H

#include "Duck/De-serialize/GameObject.h"
#include "duckpch.h"

struct Vector2 {
    float x;
    float y;

    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float x, float y) : x(x), y(y) {}
};

namespace Duck {
    class Ghost {
    public:
        // Enumeration for different AI states
        enum class State {
            Idle,
            Roaming,
            Chasing
        };

        // Constructor for the Ghost class
        Ghost();

        // Update function for the Jiangshi Ghost
        void Jiangshi(float deltaTime, std::shared_ptr<GameObject> gameObject);

        // Load waypoints from a file
        std::vector<Vector2> ReadWaypointsFromFile(const std::string& filename);

        // Idle behavior for the Ghost
        void Idle();

        // Roam behavior for the Ghost
        void Roam(float deltaTime);

        // Chase behavior for the Ghost
        void Chase(float deltaTime, std::shared_ptr<GameObject> gameObject);

        // Check if the player is nearby
        bool IsPlayerNearby(std::shared_ptr<GameObject> gameObject);

        void SetGhostProperties(float posX,
                                float posY,
                                float velX,
                                float velY,
                                float roamDur,
                                float idleDur,
                                float roamSpd,
                                float chaseSpd,
                                float maxChaseSpd,
                                Duck::AABB p_boundingBox);

        float GetGhostPositionX() const;
        float GetGhostPositionY() const;
        float getVelocityX() const;
        float getVelocityY() const;
        STATE getState() const;
        int getgridCollisionFlag() const;
        OBJ_TYPE getObj() const;
       
        void SetGhostPositionX(float x);
        void SetGhostPositionY(float y);
        void SetVelocityX(float velx);
        void SetVelocityY(float vely);
        void SetState(STATE state);
        void SetgridCollisionFlag(float posY);

        void ReadState(std::string state);
        void ReadObj(std::string obj);
        bool loadFromFile(const std::string& filename);

    private:
        std::vector<Vector2> waypoints; // Waypoints for roaming
        float ghostPositionX;           // X-coordinate of the ghost's position
        float ghostPositionY;           // Y-coordinate of the ghost's position
        float velocityX;
        float velocityY;
        int gridCollisionFlag;
        float roamDuration;             // Duration of the "Roaming" state
        float idleDuration;             // Duration of the "Idle" state
        float timeInCurrentState;       // Time elapsed in the current state
        float roamSpeed;                // Speed while roaming
        float chaseSpeed;               // Speed while chasing
        float maxChaseSpeed;            // Maximum chasing speed
        float timeElapsed;
        bool isMovingToWaypoint;

        int randomIndex;

        int currentGridX;
        int currentGridY;
        int targetGridX;
        int targetGridY;

        Duck::AABB boundingBox;
        State state;                    // Current AI state
        OBJ_TYPE obj_type;

        AABB aabb;
        PhysicsLib m_phy;
    };
}
#endif
