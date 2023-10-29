#pragma once

#ifndef JIANGSHI_H
#define JIANGSHI_H

#include "duckpch.h"
#include "Duck/De-serialize/GameObject.h"
#include "Duck/Math/Vector2D.h"
#include "Duck/Log.h"
#include "Duck/ECS/Entity.h"

// Enumeration for different AI states
enum State {
    Idle,
    Roaming,
    Chasing
};

namespace Duck {
    class JiangShi {
    public:
        JiangShi();
        JiangShi(
            float roamDur,
            float idleDur,
            float roamSpd,
            float chaseSpd,
            float maxChaseSpd,
            Duck::AABB p_boundingBox,
            State currentState
        );
        
        std::vector<MathLib::Vector2D> ReadWaypointsFromFile(const std::string& filename);

        // Get Function
        float getTimeInCurrentState() { return timeInCurrentState; }
        float getIdleDuration() { return idleDuration; }
        float getRoamDuration() { return roamDuration; }
        float getTimeElapsed() { return timeElapsed; }

        int getCurrentGridX() { return currentGridX; }
        int getCurrentGridY() { return currentGridY; }
        int getTargetGridX() { return targetGridX; }
        int getTargetGridY() { return targetGridY; }

        float getRoamspeed() { return roamSpeed; }
        float getChaseSpeed() { return chaseSpeed; }
        float getMaxChaseSpeed() { return maxChaseSpeed; }

        int getRandomIndex() { return randomIndex; }

        bool getIsMovingToWaypoint() { return isMovingToWaypoint; }

        std::vector<MathLib::Vector2D> getWaypoints() { return waypoints; }
        State getState() { return state; }

        // Set Function
        void setTimeInCurrentState(float setTime) { timeInCurrentState = setTime; }
        void setChaseSpeed(float speed) { chaseSpeed = speed; }
        void setTimeElapsed(float timeEl) { timeElapsed = timeEl; }

        void setState(State newState) { state = newState; }

        void setCurrentGridX(int gridX) { currentGridX = gridX; }
        void setCurrentGridY(int gridY) { currentGridY = gridY; }
        void setTargetGridX(int gridX) { targetGridX = gridX; }
        void setTargetGridY(int gridY) { targetGridY = gridY; }

        void setChaseSpeed(int speed) { chaseSpeed = speed; }

        void setRandomIndex(int index) { randomIndex = index; }

        void setIsMovingToWaypoint(bool setWaypoint) { isMovingToWaypoint = setWaypoint; }


    private:
        std::vector<MathLib::Vector2D> waypoints; // Waypoints for roaming
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
    };
    
    class JiangShiSystem : public System {
    public:
        void Update(double deltaTime);
        void Idle();
        void Roam(double deltaTime, GameObject ghost, JiangShi jiangshi);
        void Chase(double deltaTime, GameObject obj, JiangShi jiangshi);
        bool IsPlayerNearby(GameObject obj);
    };  
}
#endif
