#pragma once

#ifndef AI_H
#define AI_H

#include "duckpch.h"
#include "Duck/De-serialize/GameObject.h"
#include "Duck/Math/Vector2D.h"

struct Vector2 {
    float x;
    float y;

    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float x, float y) : x(x), y(y) {}
};

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
            Duck::AABB p_boundingBox
        );

        void Update(float deltaTime, std::shared_ptr<GameObject> gameObject);
        void Idle();
        void Roam(float deltaTime, std::shared_ptr<GameObject> gameObject);
        void Chase(float deltaTime, std::shared_ptr<GameObject> gameObject);
        bool IsPlayerNearby(std::shared_ptr<GameObject> gameObject);
        std::vector<Vector2> ReadWaypointsFromFile(const std::string& filename);

    private:
        std::vector<Vector2> waypoints; // Waypoints for roaming
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
}
#endif
