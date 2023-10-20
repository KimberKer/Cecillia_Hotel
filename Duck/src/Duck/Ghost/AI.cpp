//---------------------------------------------------------
// File:    AI.cpp
// Authors: Kimber Ker Soon Kiat
// Email:   s.ker\@digipen.edu
//
// Brief:   
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

/*---------------------------------------------------------
Jiangshi:
- Able to move through all rooms and levels.
- Movement speed is slow.
- Only able to travel laterally.

Pontianak:
- Roams in one of the levels only.
- Able to enter rooms.
- Movement speed is same as player.
- Able to travel laterally and diagonally.

Hachishakusama:
- Roams in all levels.
- Not able to enter any rooms.
- Movement speed is slightly faster than player.
- Able to travel laterally and diagonally.


!! Ghost will begin chase when player is 3 grids near the ghost.
!! Ghost will increase its chasing speed exponentially over a period of time.
---------------------------------------------------------*/
#include "duckpch.h"
#include "AI.h"
#include "Duck/Log.h"
#include "Duck/De-serialize/GameObject.h"


namespace Duck {
    // Constructor for the Ghost class
    Ghost::Ghost() :
        state(State::Idle),
        ghostPositionX(0.0f),
        ghostPositionY(0.0f),
        roamDuration(0),
        idleDuration(0),
        timeInCurrentState(0),
        roamSpeed(0.0f),
        maxChaseSpeed(0.0f),
        waypoints(ReadWaypointsFromFile("../txtfiles/waypoints.txt")),
        boundingbox({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
        timeElapsed(0.0f),
        isMovingToWaypoint(false)
    {
        srand(static_cast<unsigned int>(time(nullptr)));
    }

    void Ghost::SetGhostProperties(float posX, float posY, float dirX, float dirY, float roamDur, float idleDur, float roamSpd, float chaseSpd, float maxChaseSpd, Duck::AABB p_boundingbox) {
        ghostPositionX = posX;
        ghostPositionY = posY;
        directionX = dirX;
        directionY = dirY;
        roamDuration = roamDur;
        idleDuration = idleDur;
        roamSpeed = roamSpd;
        chaseSpeed = chaseSpd;
        maxChaseSpeed = maxChaseSpd;
        boundingbox = p_boundingbox;
    }

    // Update function for the Ghost class
    void Ghost::Jiangshi(float deltaTime, GameObject& gameObject) {
        timeInCurrentState += deltaTime;

        switch (state) {
        case State::Idle:
            Idle();
            if (timeInCurrentState >= idleDuration) {
                state = State::Roaming;
                DUCK_CORE_INFO("Switched to Roaming state!");
                timeInCurrentState = 0;
            }
            break;

        case State::Roaming:
            Roam(deltaTime);
            if (timeInCurrentState >= roamDuration) {
                state = State::Idle;
                DUCK_CORE_INFO("Switched to Idle state!");
                timeInCurrentState = 0;
                chaseSpeed = 0.0f; // Reset chasing speed when transitioning to "Idle"
            }
            if (IsPlayerNearby(gameObject)) {
                state = State::Chasing;
                DUCK_CORE_INFO("Switched to Chasing state!");
                timeInCurrentState = 0;
                chaseSpeed = 0.0f; // Reset chasing speed when transitioning to "Chasing"
            }
            break;

        case State::Chasing:
            Chase(deltaTime, gameObject);
            if (!IsPlayerNearby(gameObject)) {
                state = State::Idle;
                DUCK_CORE_INFO("Switched to Idle state!");
                timeInCurrentState = 0;
            }
            break;
        }
    }

    // Idle behavior for the Ghost class
    void Ghost::Idle() {
        DUCK_CORE_INFO("Ghost is idle.");
    }

    // Roam behavior for the Ghost class
    void Ghost::Roam(float deltaTime) {
        // Check if there are waypoints to roam
        timeElapsed = 0.0;
        if (waypoints.empty()) {
            DUCK_CORE_ERROR("No waypoints available for roaming.");
            return;
        }

        // Check if the ghost is currently moving or waiting at a waypoint
        if (isMovingToWaypoint) {
            // Check if the ghost has reached the center of the target grid cell
            if (currentGridX == targetGridX && currentGridY == targetGridY) {
                // Snap the ghost's position to the center of the target grid cell
                ghostPositionX = static_cast<float>(targetGridX);
                ghostPositionY = static_cast<float>(targetGridY);

                // Remove the reached waypoint from the list
                waypoints.erase(waypoints.begin() + randomIndex);
                DUCK_CORE_INFO("Waypoint reached!");

                // Set the flag to indicate waiting
                isMovingToWaypoint = false;

                // If all waypoints have been visited, reset the list to start over
                if (waypoints.empty()) {
                    DUCK_CORE_INFO("All waypoints reached!");
                    waypoints = ReadWaypointsFromFile("../txtfiles/waypoints.txt");
                }
            }
            else {
                // Check if the ghost has reached the center of the target grid cell
                currentGridX = std::ceil(ghostPositionX);
                currentGridY = std::ceil(ghostPositionY);

                // Calculate direction vector towards the selected waypoint
                directionX = static_cast<float>(targetGridX - currentGridX);
                directionY = static_cast<float>(targetGridY - currentGridY);

                if (currentGridX < targetGridX || currentGridX > targetGridX) {
                    ghostPositionX += roamSpeed * directionX * deltaTime;
                }
                else if (currentGridY < targetGridY || currentGridY > targetGridY) {
                    ghostPositionY += roamSpeed * directionY * deltaTime;
                }
            }
        }
        else {
            // Select a random waypoint
            randomIndex = rand() % waypoints.size();
            const Vector2& targetWaypoint = waypoints[randomIndex];

            // Calculate the target grid cell based on the waypoint
            targetGridX = static_cast<int>(targetWaypoint.x);
            targetGridY = static_cast<int>(targetWaypoint.y);
            
            DUCK_CORE_INFO("Target Grid X: {0}, Target Grid Y: {1}", targetGridX, targetGridY);

            // Set the flag to indicate movement
            isMovingToWaypoint = true;
        }

        // Print Current position of Ghost
        //DUCK_CORE_INFO("Current Grid X: {0}, Current Grid Y: {1}", currentGridX, currentGridY);
    }

    // Chase behavior for the Ghost class
    void Ghost::Chase(float deltaTime, GameObject& gameObject) {
        // Gradually increase chasing speed
        timeElapsed += deltaTime;

        if (chaseSpeed < maxChaseSpeed) {
            chaseSpeed += (maxChaseSpeed - chaseSpeed) * (timeElapsed / 10.0f);
            DUCK_CORE_INFO("Chase Speed: {0}", chaseSpeed);
            DUCK_CORE_INFO("Time: {0}", timeElapsed);
        }
        else {
            chaseSpeed = maxChaseSpeed; // Cap the speed at the maximum limit
        }

        // Get the player's position from the GameObject (player)
        float playerPositionX = gameObject.getX();
        float playerPositionY = gameObject.getY();

        // Calculate direction vector towards the player
        directionX = static_cast<float>(playerPositionX - ghostPositionX);
        directionY = static_cast<float>(playerPositionY - ghostPositionY);

        // Move towards the player with the gradually increasing speed
        ghostPositionX += chaseSpeed * directionX * deltaTime;
        ghostPositionY += chaseSpeed * directionY * deltaTime;
        
        // Print ghost's position (replace with actual rendering)
        //DUCK_CORE_INFO("Ghost is chasing at: {0}, {1}", ghostPositionX, ghostPositionY);
    }

    // Check if the player is nearby
    bool Ghost::IsPlayerNearby(GameObject& gameObject) {
        // Get the player's position from the GameObject (player)
        float playerPositionX = gameObject.getX();
        float playerPositionY = gameObject.getY();

        // Calculate the distance between the ghost and the player
        float distance = std::sqrt((ghostPositionX - playerPositionX) * (ghostPositionX - playerPositionX) +
            (ghostPositionY - playerPositionY) * (ghostPositionY - playerPositionY));

        // Check if the distance is less than 3 grid cells wide
        float gridCellSize = 1.0f;

        return distance <= 3.0f * gridCellSize;
    }

    // Getter for ghostPosition
    float Ghost::GetGhostPositionX() const {
        return ghostPositionX;
    }

    float Ghost::GetGhostPositionY() const {
        return ghostPositionY;
    }

    // Setter for ghostPosition
    void Ghost::SetGhostPositionX(float x) {
        ghostPositionX = x;
    }

    void Ghost::SetGhostPositionY(float y) {
        ghostPositionX = y;
    }

    // Load waypoints from a file
    std::vector<Vector2> Ghost::ReadWaypointsFromFile(const std::string& filename) {
        std::vector<Vector2> waypoints;
        std::ifstream file(filename);

        if (!file.is_open()) {
            DUCK_CORE_ERROR("Failed to open waypoints file.")
                return waypoints;
        }

        Vector2 waypoint;
        std::string line;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            if (iss >> waypoint.x >> waypoint.y) {
                waypoints.push_back(waypoint);
            }
        }

        file.close();
        return waypoints;
    }
}