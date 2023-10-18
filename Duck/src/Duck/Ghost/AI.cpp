#include "duckpch.h"
#include "AI.h"
#include "Duck/Log.h"
#include "Duck/De-serialize/GameObject.h"

int gridCellSize = 10;
static float moveTimer = 0.0f;

namespace Duck {
    // Constructor for the Ghost class
    Ghost::Ghost() :
        state(State::Idle),
        ghostPositionX(0.0f),
        ghostPositionY(0.0f),
        roamDuration(0), // Initialize with appropriate default values
        idleDuration(0), // Initialize with appropriate default values
        timeInCurrentState(0),
        roamSpeed(0.0f), // Initialize with appropriate default values
        maxChaseSpeed(0.0f), // Initialize with appropriate default values
        waypointThreshold(0.0f), // Initialize with appropriate default values
        waypoints(ReadWaypointsFromFile("../txtfiles/waypoints.txt")),
        boundingbox({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
        isMovingToWaypoint(false)
    {
        srand(static_cast<unsigned int>(time(nullptr)));
    }

    void Ghost::SetGhostProperties(float posX, float posY, float velX, float velY, float roamDur, float idleDur, float roamSpd, float maxChaseSpd, float wpThreshold, Duck::AABB p_boundingbox) {
        ghostPositionX = posX;
        ghostPositionY = posY;
        velocityX = velX;
        velocityY = velY;
        roamDuration = roamDur;
        idleDuration = idleDur;
        roamSpeed = roamSpd;
        maxChaseSpeed = maxChaseSpd;
        waypointThreshold = wpThreshold;
        boundingbox = p_boundingbox;
    }

    // Update function for the Ghost class
    void Ghost::Update(float deltaTime, GameObject& gameObject) {
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
                chaseSpeed = 0.1f; // Reset chasing speed when transitioning to "Idle"
            }
            if (IsPlayerNearby(gameObject)) {
                state = State::Chasing;
                DUCK_CORE_INFO("Switched to Chasing state!");
                timeInCurrentState = 0;
                chaseSpeed = 0.1f; // Reset chasing speed when transitioning to "Chasing"
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
        // Implement "Idle" behavior here
        DUCK_CORE_INFO("Ghost is idle.");
    }

    // Roam behavior for the Ghost class
    void Ghost::Roam(float deltaTime) {
        // Check if there are waypoints to roam
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
                DUCK_CORE_ERROR("Reached!");

                isMovingToWaypoint = false; // Set the flag to indicate waiting

                // If all waypoints have been visited, reset the list to start over
                if (waypoints.empty()) {
                    waypoints = ReadWaypointsFromFile("../txtfiles/waypoints.txt");
                }
            }
            else {
                // Check if the ghost has reached the center of the target grid cell
                currentGridX = std::ceil(ghostPositionX);
                currentGridY = std::ceil(ghostPositionY);

                // Calculate direction vector towards the selected waypoint
                velocityX = targetGridX - currentGridX;
                velocityY = targetGridY - currentGridY;

                // Movement of the Ghost
                moveTimer += 0.05f;
                if (moveTimer >= 1.0f) { // Adjust 1.0f to control the delay
                    moveTimer = 0.0f;

                    if (currentGridX < targetGridX) {
                        ghostPositionX += roamSpeed * velocityX;
                    }
                    else if (currentGridX > targetGridX) {
                        ghostPositionX += roamSpeed * velocityX;
                    }
                    else if (currentGridY < targetGridY) {
                        ghostPositionY += roamSpeed * velocityY;
                    }
                    else if (currentGridY > targetGridY) {
                        ghostPositionY += roamSpeed * velocityY;
                    }
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

            // Set the flag to indicate movement
            isMovingToWaypoint = true;
        }

        // Print Target and Current position of Ghost
        //DUCK_CORE_INFO("Target Grid X: {0}, Target Grid Y: {1}", targetGridX, targetGridY);
        //DUCK_CORE_INFO("Current Grid X: {0}, Current Grid Y: {1}", currentGridX, currentGridY);
    }

    // Chase behavior for the Ghost class
    void Ghost::Chase(float deltaTime, GameObject& gameObject) {
        // Gradually increase chasing speed
        chaseSpeed += roamSpeed;
        if (chaseSpeed > maxChaseSpeed) {
            chaseSpeed = maxChaseSpeed; // Cap the speed at the maximum limit
        }

        // Get the player's position from the GameObject (player)
        float playerPositionX = gameObject.getX();
        float playerPositionY = gameObject.getY();

        // Calculate direction vector towards the player
        float directionX = playerPositionX - ghostPositionX;
        float directionY = playerPositionY - ghostPositionY;

        // Movement of the Ghost
        moveTimer += 0.05f;
        if (moveTimer >= (1.0f - chaseSpeed)) {
            moveTimer = 0.0f;

            // Move towards the player with the gradually increasing speed
            ghostPositionX += directionX * chaseSpeed;
            ghostPositionY += directionY * chaseSpeed;
        }
        
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

        // Check if the distance is less than 2 grid cells wide
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

    float Ghost::getVelocityX() const {
        return velocityX;
    }

    float Ghost::getVelocityY() const {
        return velocityY;
    }

    void Ghost::SetVelocityX(float velx) {
        velocityX = velx;
    }

    void Ghost::SetVelocityY(float vely) {
        velocityY = vely;
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