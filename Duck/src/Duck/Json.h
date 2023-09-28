#ifndef JSON_H
#define JSON_H

#include <string>
#include "../rapidjson/document.h"

class JsonReader {
public:
    // Constructor that takes a filename to open and read
    JsonReader(const std::string& filename);

    // Function to read and parse the JSON data
    bool ReadAndParse();

    // Functions to retrieve player data from the parsed JSON
    bool GetPlayerData();

    // Functions to retrieve grid size from the parsed JSON
    bool GetGridSize();

    // Accessors for player X and Y positions
    float GetPlayerXPosition() const;
    float GetPlayerYPosition() const;

    // Accessors for player X and Y velocities
    float GetPlayerXVelocity() const;
    float GetPlayerYVelocity() const;

    // Accessors for grid size in the X and Y dimensions
    int GetGridSizeX() const;
    int GetGridSizeY() const;

private:
    std::string filename_; // The name of the JSON file to read
    rapidjson::Document document_; // RapidJSON document to hold the parsed JSON data

    // Variables to store player data
    float xPosition_;
    float yPosition_;
    float xVelocity_;
    float yVelocity_;

    // Variables to store grid size
    int xGrid;
    int yGrid;
};

#endif
