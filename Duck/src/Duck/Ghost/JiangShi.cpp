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
        state(State::Roaming),
        timeElapsed(0.0f),
        timeInCurrentState(0),
        waypoints(ReadWaypointsFromFile("../txtfiles/waypoints.txt"))
    {
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