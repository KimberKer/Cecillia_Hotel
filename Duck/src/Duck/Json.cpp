#include "duckpch.h"
#include "Json.h"
#include "Duck/Log.h"

// Constructor to initialize member variables with default values
JsonReader::JsonReader(const std::string& filename)
    : filename_(filename), xPosition_(0.0), yPosition_(0.0), xVelocity_(0.0), yVelocity_(0.0), xGrid(0), yGrid(0) {}

// Function to read and parse the JSON file
bool JsonReader::ReadAndParse() {
    std::ifstream inputFile(filename_);

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open JSON file: " << filename_ << std::endl;
        return false;
    }

    // Read the entire file into a string
    std::string jsonString((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    // Close the file
    inputFile.close();

    // Parse the JSON string
    document_.Parse(jsonString.c_str());

    if (document_.HasParseError()) {
        std::cerr << "JSON parse error: " << document_.GetParseError() << std::endl;
        return false;
    }

    // Try to retrieve player data, and if successful, return true.
    // If not, try to retrieve grid size, and if successful, return true.
    // If neither succeeds, return false.
    if (GetPlayerData()) {
        return true;
    }
    else if (GetGridSize()) {
        return true;
    }

    return false;
}

// Function to retrieve player data from the parsed JSON
bool JsonReader::GetPlayerData() {
    if (document_.HasMember("player") && document_["player"].IsObject()) {
        const rapidjson::Value& player = document_["player"];

        if (player.HasMember("position") && player.HasMember("velocity")) {
            const rapidjson::Value& position = player["position"];
            const rapidjson::Value& velocity = player["velocity"];

            if (position.HasMember("x") && position.HasMember("y") &&
                velocity.HasMember("x") && velocity.HasMember("y")) {
                xPosition_ = position["x"].GetFloat();
                yPosition_ = position["y"].GetFloat();
                xVelocity_ = velocity["x"].GetFloat();
                yVelocity_ = velocity["y"].GetFloat();

                return true; // Successfully retrieved player data
            }
        }
    }

    return false; // Player data not found in the JSON
}

// Function to retrieve grid size from the parsed JSON
bool JsonReader::GetGridSize() {
    if (document_.HasMember("grid") && document_["grid"].IsObject()) {
        const rapidjson::Value& grid = document_["grid"];

        if (grid.HasMember("x") && grid.HasMember("y")) {
            xGrid = grid["x"].GetInt();
            yGrid = grid["y"].GetInt();

            return true; // Successfully retrieved grid size
        }
    }

    return false; // Grid size not found in the JSON
}

// Accessors for player X and Y positions
float JsonReader::GetPlayerXPosition() const {
    return xPosition_;
}

float JsonReader::GetPlayerYPosition() const {
    return yPosition_;
}

// Accessors for player X and Y velocities
float JsonReader::GetPlayerXVelocity() const {
    return xVelocity_;
}

float JsonReader::GetPlayerYVelocity() const {
    return yVelocity_;
}

// Accessors for grid size in the X and Y dimensions
int JsonReader::GetGridSizeX() const {
    return xGrid;
}

int JsonReader::GetGridSizeY() const {
    return yGrid;
}
