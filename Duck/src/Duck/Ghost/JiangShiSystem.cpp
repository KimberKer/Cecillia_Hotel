//---------------------------------------------------------
// File:    JiangShiSystem.cpp
//authors:	Kimber Ker Soon Kiat
// email:	s.ker\@digipen.edu
// 
//
// Brief:   Contain the main function for JiangShi. This file
//          can be used for multiple Ghost. Since the idle,
//          and roam is similar for each ghost. As for the chase,
//          it can be unique to each ghost on how each ghost
//          should behave while chasing.
//
// Copyright � 2023 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "duckpch.h"
#include "JiangShi.h"

float playerPositionX{}, playerPositionY{};

namespace Duck {
    void JiangShiSystem::Update(double deltaTime) {
        for (auto const& entity : m_Entities) {
            auto &gameObjectEntity = ecs.getComponent<GameObject>(entity);

            if(gameObjectEntity.getObj() == OBJ_PLAYER) {
                playerPositionX = gameObjectEntity.getX();
                playerPositionY = gameObjectEntity.getY();
            }
        }

        for (auto const& entity : m_Entities) {
            auto& gameObjectEntity = ecs.getComponent<GameObject>(entity);

            if (ecs.HasComponent<JiangShi>(entity)) {
                auto& ghostCompEntity = ecs.getComponent<JiangShi>(entity);
                float currentStateTime = ghostCompEntity.getTimeInCurrentState();
                currentStateTime += deltaTime;
                ghostCompEntity.setTimeInCurrentState(currentStateTime);

                switch (ghostCompEntity.getState()) {
                case State::Idle:
                    Idle(); // Execute the Idle state function
                    if (ghostCompEntity.getTimeInCurrentState() >= ghostCompEntity.getIdleDuration()) {
                        DUCK_CORE_INFO("Ghost idled for: {0}", ghostCompEntity.getTimeInCurrentState());
                        ghostCompEntity.setTimeInCurrentState(0.0f);
                        DUCK_CORE_INFO("Switched to Roaming state!");
                        ghostCompEntity.setState(State::Roaming);
                    }
                    break;
                case State::Roaming:
                    Roam(deltaTime, gameObjectEntity, ghostCompEntity); // Execute the Roaming state function
                    //DUCK_CORE_TRACE("x: {0}, y: {1}", gameObjectEntity.getX(), gameObjectEntity.getY());
                    //DUCK_CORE_INFO("Ghost is Roaming");
                    if (ghostCompEntity.getTimeInCurrentState() >= ghostCompEntity.getRoamDuration()) {
                        DUCK_CORE_INFO("Ghost roamed for: {0}", ghostCompEntity.getTimeInCurrentState());
                        ghostCompEntity.setState(State::Idle);
                        DUCK_CORE_INFO("Switched to Idle state!");
                        ghostCompEntity.setTimeInCurrentState(0.0f);
                        ghostCompEntity.setChaseSpeed(0.0f); // Reset chasing speed when transitioning to "Idle"
                    }
                    if (IsPlayerNearby(gameObjectEntity)) {
                        ghostCompEntity.setState(State::Chasing);
                        DUCK_CORE_INFO("Switched to Chasing state!");
                        ghostCompEntity.setTimeInCurrentState(0.0f);
                        ghostCompEntity.setChaseSpeed(0.0f); // Reset chasing speed when transitioning to "Chasing"
                    }
                    break;
                case State::Chasing:
                    Chase(deltaTime, gameObjectEntity, ghostCompEntity); // Execute the Chasing state function
                    if (!IsPlayerNearby(gameObjectEntity)) {
                        ghostCompEntity.setState(State::Idle);
                        DUCK_CORE_INFO("Switched to Idle state!");
                        ghostCompEntity.setTimeInCurrentState(0.0f);
                    }
                    break;
                }
                DUCK_CORE_TRACE("{0}, {1}", gameObjectEntity.getX(), gameObjectEntity.getY());
            }
        }
    }

    void JiangShiSystem::Idle() {
        DUCK_CORE_INFO("Ghost is idling.");
    }

    void JiangShiSystem::Roam(double deltaTime, GameObject &ghost, JiangShi &jiangshi) {
        // Check if there are waypoints to roam
        jiangshi.setTimeElapsed(0.0f);

        MathLib::Vector2D targetWaypoint;
        std::vector<MathLib::Vector2D> currentWaypoints;
        currentWaypoints = jiangshi.getWaypoints();

        if (currentWaypoints.empty()) {
            DUCK_CORE_ERROR("No waypoints available for roaming.");
            return;
        }

        // Check if the ghost is currently moving or waiting at a waypoint
        if (jiangshi.getIsMovingToWaypoint()) {
            // Check if the ghost has reached the center of the target grid cell
            if (jiangshi.getCurrentGridX() == jiangshi.getTargetGridX() && jiangshi.getCurrentGridY() == jiangshi.getTargetGridY()) {
                // Snap the ghost's position to the center of the target grid cell
                ghost.SetPositionX(static_cast<float>(jiangshi.getTargetGridX()));
                ghost.SetPositionY(static_cast<float>(jiangshi.getTargetGridY()));

                // Remove the reached waypoint from the list
                currentWaypoints.erase(currentWaypoints.begin() + jiangshi.getRandomIndex());
                DUCK_CORE_INFO("Waypoint reached!");

                // Set the flag to indicate waiting
                jiangshi.setIsMovingToWaypoint(false);

                // If all waypoints have been visited, reset the list to start over
                if (jiangshi.getWaypoints().empty()) {
                    DUCK_CORE_INFO("All waypoints reached!");
                    jiangshi.getWaypoints() = jiangshi.ReadWaypointsFromFile("../txtfiles/waypoints.txt");
                }
            }
            else {
                // Check if the ghost has reached the center of the target grid cell
                jiangshi.setCurrentGridX(std::ceil(ghost.getX()));
                jiangshi.setCurrentGridY(std::ceil(ghost.getY()));

                // Calculate direction vector towards the selected waypoint
                float directionX = static_cast<float>(jiangshi.getTargetGridX() - jiangshi.getCurrentGridX());
                float directionY = static_cast<float>(jiangshi.getTargetGridY() - jiangshi.getCurrentGridY());

                // Move Ghost
                if (jiangshi.getCurrentGridX() < jiangshi.getTargetGridX() || jiangshi.getCurrentGridX() > jiangshi.getTargetGridX()) {
                    ghost.SetPositionX(ghost.getX() + jiangshi.getRoamspeed() * directionX * deltaTime);
                }
                else if (jiangshi.getCurrentGridY() < jiangshi.getTargetGridY() || jiangshi.getCurrentGridY() > jiangshi.getTargetGridY()) {
                    ghost.SetPositionY(ghost.getY() + jiangshi.getRoamspeed() * directionY * deltaTime);
                }
            }
        }
        else {
            // Select a random waypoint
            jiangshi.setRandomIndex(rand() % currentWaypoints.size());

            targetWaypoint = currentWaypoints[jiangshi.getRandomIndex()];

            // Calculate the target grid cell based on the waypoint
            jiangshi.setTargetGridX(static_cast<int>(targetWaypoint.x));
            jiangshi.setTargetGridY(static_cast<int>(targetWaypoint.y));

            // Set the flag to indicate movement
            jiangshi.setIsMovingToWaypoint(true);
        }
    }

    void JiangShiSystem::Chase(double deltaTime, GameObject& ghost, JiangShi jiangshi) {
        float playerPositionX{}, playerPositionY{}, ghostPositionX{}, ghostPositionY{};

        jiangshi.setTimeElapsed(jiangshi.getTimeElapsed() + deltaTime);

        if (jiangshi.getChaseSpeed() < jiangshi.getMaxChaseSpeed()) {
            // Increase chaseSpeed to maxChaseSpeed over 5 seconds
            jiangshi.setChaseSpeed(jiangshi.getChaseSpeed() + (jiangshi.getMaxChaseSpeed() / 5.0f) * jiangshi.getTimeElapsed());
        }
        else {
            // Cap the speed at the maximum limit
            jiangshi.setChaseSpeed(jiangshi.getMaxChaseSpeed());
        }

        ghostPositionX = ghost.getX();
        ghostPositionY = ghost.getY();

        // Calculate direction vector towards the player
        float directionX = static_cast<float>(playerPositionX - ghostPositionX);
        float directionY = static_cast<float>(playerPositionY - ghostPositionY);

        // Move towards the player with the gradually increasing speed
        ghost.SetPositionX(ghost.getX() + jiangshi.getChaseSpeed() * directionX * deltaTime);
        ghost.SetPositionY(ghost.getY() + jiangshi.getChaseSpeed() * directionY * deltaTime);
    }
    
    bool JiangShiSystem::IsPlayerNearby(GameObject& ghost) {
        float ghostPositionX = ghost.getX();
        float ghostPositionY = ghost.getY();

        // Calculate the distance between the ghost and the player
        float distance = std::sqrt((ghostPositionX - playerPositionX) * (ghostPositionX - playerPositionX) +
            (ghostPositionY - playerPositionY) * (ghostPositionY - playerPositionY));

        return distance <= 3.0f;
    }
}
