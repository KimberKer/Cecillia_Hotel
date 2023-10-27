#include "duckpch.h"
#include "JiangShi.h"

namespace Duck {
    void JiangShiSystem::Update(double deltaTime) {
        for (auto const& entity : m_Entities) {
            auto ghostObjEntity = ecs.getComponent<GameObject>(entity);
            auto playerEntity = ecs.getComponent<GameObject>(entity);

            if (ghostObjEntity.getObj() == OBJ_GHOST) {

            }

            auto ghostCompEntity = ecs.getComponent<JiangShi>(entity);

            OBJ_TYPE ghostObjectType = ghostObjEntity.getObj();
            OBJ_TYPE playerObjectType = playerEntity.getObj();

            float currentStateTime = ghostCompEntity.getTimeInCurrentState();
            float idleDuration = ghostCompEntity.getIdleDuration();
            float roamDuration = ghostCompEntity.getRoamDuration();
            State currentState = ghostCompEntity.getState();

            currentStateTime += deltaTime;

            switch (currentState) {
            case State::Idle:
                Idle();
                if (currentStateTime >= idleDuration) {
                    DUCK_CORE_INFO("Ghost idled for: {0}", currentStateTime);
                    ghostCompEntity.setTimeInCurrentState(0.0f);
                    DUCK_CORE_INFO("Switched to Roaming state!");
                    ghostCompEntity.setState(State::Roaming);
                }
                break;
            case State::Roaming:
                Roam(deltaTime, ghostObjEntity, ghostCompEntity);
                if (currentStateTime >= roamDuration) {
                    DUCK_CORE_INFO("Ghost roamed for: {0}", currentStateTime);
                    ghostCompEntity.setState(State::Idle);
                    DUCK_CORE_INFO("Switched to Idle state!");
                    ghostCompEntity.setTimeInCurrentState(0.0f);
                    ghostCompEntity.setChaseSpeed(0.0f); // Reset chasing speed when transitioning to "Idle"
                }

                if (IsPlayerNearby(playerEntity)) {
                    ghostCompEntity.setState(State::Chasing);
                    DUCK_CORE_INFO("Switched to Chasing state!");
                    ghostCompEntity.setTimeInCurrentState(0.0f);
                    ghostCompEntity.setChaseSpeed(0.0f); // Reset chasing speed when transitioning to "Chasing"
                }
                break;
            case State::Chasing:
                Chase(deltaTime, playerEntity, ghostObjEntity, ghostCompEntity);
                if (!IsPlayerNearby(playerEntity)) {
                    ghostCompEntity.setState(State::Idle);
                    DUCK_CORE_INFO("Switched to Idle state!");
                    ghostCompEntity.setTimeInCurrentState(0.0f);
                }
                break;
            }
        }
    }

    void JiangShiSystem::Idle() {
        DUCK_CORE_INFO("Ghost is idling.");
    }

    void JiangShiSystem::Roam(double deltaTime, GameObject ghost, JiangShi jiangshi) {
        // Check if there are waypoints to roam
        jiangshi.setTimeElapsed(0.0f);
        if (jiangshi.getWaypoints().empty()) {
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
                jiangshi.getWaypoints().erase(jiangshi.getWaypoints().begin() + jiangshi.getRandomIndex());
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
            jiangshi.setRandomIndex(rand() % jiangshi.getWaypoints().size());

            const MathLib::Vector2D& targetWaypoint = jiangshi.getWaypoints()[jiangshi.getRandomIndex()];

            // Calculate the target grid cell based on the waypoint
            jiangshi.setTargetGridX(static_cast<int>(targetWaypoint.x));
            jiangshi.setTargetGridY(static_cast<int>(targetWaypoint.y));

            // Set the flag to indicate movement
            jiangshi.setIsMovingToWaypoint(true);
        }
    }

    void JiangShiSystem::Chase(double deltaTime, GameObject player, GameObject ghost, JiangShi jiangshi) {
        jiangshi.setTimeElapsed(jiangshi.getTimeElapsed() + deltaTime);

        if (jiangshi.getChaseSpeed() < jiangshi.getMaxChaseSpeed()) {
            // Increase chaseSpeed to maxChaseSpeed over 5 seconds
            jiangshi.setChaseSpeed(jiangshi.getChaseSpeed() + (jiangshi.getMaxChaseSpeed() / 5.0f) * jiangshi.getTimeElapsed());
        }
        else {
            // Cap the speed at the maximum limit
            jiangshi.setChaseSpeed(jiangshi.getMaxChaseSpeed());
        }

        // Get the player's position from the GameObject (player)
        float playerPositionX = player.getX();
        float playerPositionY = player.getY();

        float ghostPositionX = ghost.getX();
        float ghostPositionY = ghost.getY();

        // Calculate direction vector towards the player
        float directionX = static_cast<float>(playerPositionX - ghostPositionX);
        float directionY = static_cast<float>(playerPositionY - ghostPositionY);

        // Move towards the player with the gradually increasing speed
        ghost.SetPositionX(ghost.getX() + jiangshi.getChaseSpeed() * directionX * deltaTime);
        ghost.SetPositionY(ghost.getY() + jiangshi.getChaseSpeed() * directionY * deltaTime);
    }

    bool JiangShiSystem::IsPlayerNearby(GameObject player) {
        // Get the player's position from the GameObject (player)
        float playerPositionX = player.getX();
        float playerPositionY = player.getY();

        // Calculate the distance between the ghost and the player
        float distance = std::sqrt((player.getX() - playerPositionX) * (player.getX() - playerPositionX) +
            (player.getY() - playerPositionY) * (player.getY() - playerPositionY));

        return distance <= 3.0f;
    }


}

