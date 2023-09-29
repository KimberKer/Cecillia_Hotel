#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "../rapidjson/include/rapidjson/document.h"
#include "duckpch.h"

class Player {
public:
    // Constructor
    Player();

    // Load player data and return the vector
    std::vector<float> LoadPlayerData();

private:
    // Variables to store player data
    std::vector<float> PosVec;

    bool loadPlayer;
    bool loadGrid;
};

#endif
