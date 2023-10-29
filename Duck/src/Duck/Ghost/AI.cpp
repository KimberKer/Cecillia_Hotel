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
- Teleport infront of the player distance between player and ghost reaches a certain distance

Hachishakusama:
- Roams in all levels.
- Not able to enter any rooms.
- Movement speed is slightly faster than player.
- Able to travel laterally and diagonally.


!! Ghost will begin chase when player is 3 grids near the ghost.
!! Ghost will increase its chasing speed exponentially over a period of time.
---------------------------------------------------------*/
#include "duckpch.h"
#include "Duck/Log.h"
#include "Duck/De-serialize/GameObject.h"
#include "AI.h"

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
        boundingBox({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
        timeElapsed(0.0f),
        isMovingToWaypoint(false)
    {
        srand(static_cast<unsigned int>(time(nullptr)));
    }

    void Ghost::SetGhostProperties(float posX, float posY, float velX, float velY, float roamDur, float idleDur, float roamSpd, float chaseSpd, float maxChaseSpd, AABB p_boundingBox) {
        ghostPositionX = posX;
        ghostPositionY = posY;
        velocityX = velX;
        velocityX = velY;
        roamDuration = roamDur;
        idleDuration = idleDur;
        roamSpeed = roamSpd;
        chaseSpeed = chaseSpd;
        maxChaseSpeed = maxChaseSpd;
        boundingBox = p_boundingBox;
    }

    // Update function for the Ghost class
    void Ghost::Jiangshi(float deltaTime, std::shared_ptr<GameObject> gameObject) {
        //for (auto const& entity : m_Entities) {
            timeInCurrentState += deltaTime;

            switch (state) {
            case State::Idle:
                Idle();
                if (timeInCurrentState >= idleDuration) {
                    DUCK_CORE_INFO("Ghost idled for: {0}", timeInCurrentState);
                    state = State::Roaming;
                    DUCK_CORE_INFO("Switched to Roaming state!");
                    timeInCurrentState = 0;
                }
                break;

            case State::Roaming:
                Roam(deltaTime);
                if (timeInCurrentState >= roamDuration) {
                    DUCK_CORE_INFO("Ghost roamed for: {0}", timeInCurrentState);
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
       //}
    }

    // Idle behavior for the Ghost class
    void Ghost::Idle() {
        DUCK_CORE_INFO("Ghost is idling.");
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
                velocityX = static_cast<float>(targetGridX - currentGridX);
                velocityY = static_cast<float>(targetGridY - currentGridY);

                if (currentGridX < targetGridX || currentGridX > targetGridX) {
                    ghostPositionX += roamSpeed * velocityX * deltaTime;
                }
                else if (currentGridY < targetGridY || currentGridY > targetGridY) {
                    ghostPositionY += roamSpeed * velocityY * deltaTime;
                }
            }
        }
        else {
            // Select a random waypoint
            randomIndex = rand() % waypoints.size();
            const MathLib::Vector2D targetWaypoint = waypoints[randomIndex];

            // Calculate the target grid cell based on the waypoint
            targetGridX = static_cast<int>(targetWaypoint.x);
            targetGridY = static_cast<int>(targetWaypoint.y);
            
            //DUCK_CORE_INFO("Target Grid X: {0}, Target Grid Y: {1}", targetGridX, targetGridY);

            // Set the flag to indicate movement
            isMovingToWaypoint = true;
        }
    }

    // Chase behavior for the Ghost class
    void Ghost::Chase(float deltaTime, std::shared_ptr<GameObject> gameObject) {
        timeElapsed += deltaTime;

        if (chaseSpeed < maxChaseSpeed) {
            chaseSpeed += (maxChaseSpeed - chaseSpeed) * (timeElapsed / 10.0f);
            //DUCK_CORE_INFO("Chase Speed: {0}", chaseSpeed);
            //DUCK_CORE_INFO("Time: {0}", timeElapsed);
        }
        else {
            // Cap the speed at the maximum limit
            chaseSpeed = maxChaseSpeed;
        }

        // Get the player's position from the GameObject (player)
        float playerPositionX = gameObject->getX();
        float playerPositionY = gameObject->getY();

        // Calculate direction vector towards the player
        velocityX = static_cast<float>(playerPositionX - ghostPositionX);
        velocityY = static_cast<float>(playerPositionY - ghostPositionY);

        // Move towards the player with the gradually increasing speed
        ghostPositionX += chaseSpeed * velocityX * deltaTime;
        ghostPositionY += chaseSpeed * velocityY * deltaTime;
    }

    // Check if the player is nearby
    bool Ghost::IsPlayerNearby(std::shared_ptr<GameObject> gameObject) {
        // Get the player's position from the GameObject (player)
        float playerPositionX = gameObject->getX();
        float playerPositionY = gameObject->getY();

        // Calculate the distance between the ghost and the player
        float distance = std::sqrt((ghostPositionX - playerPositionX) * (ghostPositionX - playerPositionX) +
            (ghostPositionY - playerPositionY) * (ghostPositionY - playerPositionY));

        return distance <= 3.0f;
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
    std::vector<MathLib::Vector2D> Ghost::ReadWaypointsFromFile(const std::string& filename) {
        std::vector<MathLib::Vector2D> waypoints;
        std::ifstream file(filename);

        if (!file.is_open()) {
            DUCK_CORE_ERROR("Failed to open waypoints file.")
                return waypoints;
        }

        MathLib::Vector2D waypoint;
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

   /* bool Ghost::loadFromFile(const std::string& filename) {
        std::string pos_x, pos_y, vel_x, vel_y, roamDur, idleDur, roamSpd, chaseSpd, maxChaseSpd, gridFlag, bounding, curr_state, getstate, type, getType;
        const std::string path = "../txtfiles/" + filename;

        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << path << std::endl;
            return false;
        }

        float minx, miny, maxx, maxy;
        file >> pos_x >> ghostPositionX
            >> pos_y >> ghostPositionY
            >> vel_x >> velocityX
            >> vel_y >> velocityX
            >> roamDur >> roamDuration
            >> idleDur >> idleDuration
            >> roamSpd >> roamSpeed
            >> chaseSpd >> chaseSpeed
            >> maxChaseSpd >> maxChaseSpeed
            >> gridFlag >> gridCollisionFlag
            >> bounding >> minx >> miny >> maxx >> maxy
            >> curr_state >> getstate
            >> type >> getType;

        ReadState(getstate);
        ReadObj(getType);

        MathLib::Vector2D minVec(minx, miny);
        MathLib::Vector2D maxVec(maxx, maxy);
        boundingBox = { minVec, maxVec };

        file.close();
        return true;
    }*/
}
