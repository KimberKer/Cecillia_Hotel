#include "duckpch.h"
#include "Duck/Json.h"
#include "Duck/Log.h"
#include "Player.h"

//Player::Player() : xPosition(0.0), yPosition(0.0), xVelocity(0.0), yVelocity(0.0), loadPlayer(false) {}
Player::Player() : PosVec(0), loadPlayer(false) {}

JsonReader jsonReaderPlayer("../json/playerinfo.json"); // Create a JsonReader instance for playerinfo.json
JsonReader jsonReaderGrid("../json/gridsize.json");     // Create a JsonReader instance for gridsize.json

std::vector<float> Player::LoadPlayerData() {
    if (jsonReaderPlayer.ReadAndParse()) {
        // Retrieve the player's position and velocity using GetPlayerData
        if (jsonReaderPlayer.GetPlayerData()) {
            // Use the retrieved player's position and velocity
            PosVec.push_back(jsonReaderPlayer.GetPlayerXPosition());
            PosVec.push_back(jsonReaderPlayer.GetPlayerYPosition());
            PosVec.push_back(jsonReaderPlayer.GetPlayerXVelocity());
            PosVec.push_back(jsonReaderPlayer.GetPlayerYVelocity());

            if (!loadPlayer) {
                DUCK_INFO("Player Position (x, y): {0}, {1}", PosVec[0], PosVec[1]);
                DUCK_INFO("Player Velocity (x, y): {0}, {1}", PosVec[2], PosVec[3]);

                // Set the flag to true to indicate data has been loaded
                loadPlayer = true;
            }
        }
        else {
            DUCK_ERROR("Failed to retrieve player data from JSON");
        }
    }
    
    return PosVec;
}

//void LoadGrid() {
//    if (jsonReaderGrid.ReadAndParse()) {
//        // Retrieve the grid x and y using GetPlayerData
//        if (jsonReaderGrid.GetGridSize()) {
//            // Use the retrieved player's position and velocity
//            int xGrid = jsonReaderGrid.GetGridSizeX();
//            int yGrid = jsonReaderGrid.GetGridSizeY();
//
//            if (!loadGrid) {
//                DUCK_INFO("Grid: (x, y): {0}, {1}", xGrid, yGrid);
//
//                // Set the flag to true to indicate data has been loaded
//                loadGrid = true;
//            }
//        }
//        else {
//            DUCK_ERROR("Failed to retrieve grid data from JSON");
//        }
//    }
//}
