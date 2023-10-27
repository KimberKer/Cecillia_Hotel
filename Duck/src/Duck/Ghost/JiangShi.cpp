#include "duckpch.h"
#include "JiangShi.h"

namespace Duck {
	JiangShi::JiangShi() :
        state(State::Idle),
        roamDuration(0),
        idleDuration(0),
        timeInCurrentState(0),
        roamSpeed(0.0f),
        maxChaseSpeed(0.0f),
        waypoints(ReadWaypointsFromFile("../txtfiles/waypoints.txt")),
        boundingBox({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
        timeElapsed(0.0f),
        isMovingToWaypoint(false),
        randomIndex(0)
    {
        srand(static_cast<unsigned int>(time(nullptr)));
    }

    JiangShi::JiangShi(float roamDur, float idleDur, float roamSpd, float chaseSpd, float maxChaseSpd, Duck::AABB p_boundingBox) :
        roamDuration(roamDur),
        idleDuration(idleDur),
        roamSpeed(roamSpd),
        chaseSpeed(chaseSpd),
        maxChaseSpeed(maxChaseSpd),
        boundingBox(p_boundingBox),
        isMovingToWaypoint(false),
        randomIndex(0),
        state(State::Idle),
        timeElapsed(0.0f),
        timeInCurrentState(0),
        waypoints(ReadWaypointsFromFile("../txtfiles/waypoints.txt"))
    {
    }

    void JiangShi::Update(float deltaTime, std::shared_ptr<GameObject> gameObject) {
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
            Roam(deltaTime, gameObject);
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
    }

    void JiangShi::Idle() {
        DUCK_CORE_INFO("Ghost is idling.");
    }

    void JiangShi::Roam(float deltaTime, std::shared_ptr<GameObject> gameObject) {
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
                gameObject->SetPositionX(static_cast<float>(targetGridX));
                gameObject->SetPositionY(static_cast<float>(targetGridY));

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
                currentGridX = std::ceil(gameObject->getX());
                currentGridY = std::ceil(gameObject->getY());

                // Calculate direction vector towards the selected waypoint
                float directionX = static_cast<float>(targetGridX - currentGridX);
                float directionY = static_cast<float>(targetGridY - currentGridY);

                if (currentGridX < targetGridX || currentGridX > targetGridX) {
                    gameObject->SetPositionX(gameObject->getX() + roamSpeed * directionX * deltaTime);
                }
                else if (currentGridY < targetGridY || currentGridY > targetGridY) {
                    gameObject->SetPositionY(gameObject->getY() + roamSpeed * directionY * deltaTime);
                }
            }
        }
        else {
            // Select a random waypoint
            randomIndex = rand() % waypoints.size();
            const MathLib::Vector2D& targetWaypoint = waypoints[randomIndex];

            // Calculate the target grid cell based on the waypoint
            targetGridX = static_cast<int>(targetWaypoint.x);
            targetGridY = static_cast<int>(targetWaypoint.y);

            // Set the flag to indicate movement
            isMovingToWaypoint = true;
        }
    }

    void JiangShi::Chase(float deltaTime, std::shared_ptr<GameObject> gameObject) {
        timeElapsed += deltaTime;

        if (chaseSpeed < maxChaseSpeed) {
            // Increase chaseSpeed to maxChaseSpeed over 5 seconds
            chaseSpeed += (maxChaseSpeed / 5.0f) * timeElapsed;
        }
        else {
            // Cap the speed at the maximum limit
            chaseSpeed = maxChaseSpeed;
        }

        // Get the player's position from the GameObject (player)
        float playerPositionX = gameObject->getX();
        float playerPositionY = gameObject->getY();

        // Calculate direction vector towards the player
        float directionX = static_cast<float>(playerPositionX - gameObject->getX());
        float directionY = static_cast<float>(playerPositionY - gameObject->getY());

        // Move towards the player with the gradually increasing speed
        gameObject->SetPositionX(gameObject->getX() + chaseSpeed * directionX * deltaTime);
        gameObject->SetPositionY(gameObject->getY() + chaseSpeed * directionY * deltaTime);
    }

    bool JiangShi::IsPlayerNearby(std::shared_ptr<GameObject> gameObject) {
        // Get the player's position from the GameObject (player)
        float playerPositionX = gameObject->getX();
        float playerPositionY = gameObject->getY();

        // Calculate the distance between the ghost and the player
        float distance = std::sqrt((gameObject->getX() - playerPositionX) * (gameObject->getX() - playerPositionX) +
            (gameObject->getY() - playerPositionY) * (gameObject->getY() - playerPositionY));

        return distance <= 3.0f;
    }

    std::vector<MathLib::Vector2D> JiangShi::ReadWaypointsFromFile(const std::string& filename) {
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
}