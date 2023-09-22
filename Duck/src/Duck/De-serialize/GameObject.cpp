#include "duckpch.h"
#include "GameObject.h"

GameObject::GameObject() : x(0.0f), y(0.0f), velocityX(0.0f), velocityY(0.0f) {}

GameObject::GameObject(float x, float y, float velocityX, float velocityY)
    : x(x), y(y), velocityX(velocityX), velocityY(velocityY) {}

float GameObject::getX() const {
    return x;
}

float GameObject::getY() const {
    return y;
}

float GameObject::getVelocityX() const {
    return velocityX;
}

float GameObject::getVelocityY() const {
    return velocityY;
}

bool GameObject::loadFromFile(const std::string& filename) {
    // Specify the absolute path to "player.txt"
    const std::string path = "../txtfiles/" + filename;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << path << std::endl;
        return false;
    }

    // Read and parse data from the file
    file >> x >> y >> velocityX >> velocityY;

    file.close();
    return true;
}

void GameObject::loadPlayerData() {
    if (loadFromFile("player.txt")) {
        std::cout << "Player Position(x, y): (" << getX() << ", " << getY() << ")\n";
        std::cout << "Player Velocity(x, y): (" << getVelocityX() << ", " << getVelocityY() << ")\n";
    }
    else {
        std::cerr << "Failed to load player data from file.\n";
    }
}