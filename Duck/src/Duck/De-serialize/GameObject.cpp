#include "duckpch.h"
#include "GameObject.h"

GameObject::GameObject() : x(0.0f), y(0.0f), velocityX(0.0f), velocityY(0.0f), state(STATE_NONE) {}

GameObject::GameObject(float x, float y, float velocityX, float velocityY, STATE getstate)
    : x(x), y(y), velocityX(velocityX), velocityY(velocityY), state(getstate) {}


STATE GameObject::getState() const {
    return state;
}
void GameObject::SetState(STATE getstate) {
    state = getstate;
}
float GameObject::getX() const {
    return x;
}
void GameObject::SetVelocityX(float velx) {
    velocityX = velx;
}

void GameObject::SetVelocityY(float vely) {
    velocityY = vely;
}
void GameObject::SetPositionX(float posX) {
    x = posX;
}
void GameObject::SetPositionY(float posY) {
    y = posY;
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
    std::string pos_x, pos_y, vel_x, vel_y, curr_state;
    // Specify the absolute path to "player.txt"
    const std::string path = "../txtfiles/" + filename;

    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << path << std::endl;
        return false;
    }

    // Read and parse data from the file
    file << pos_x << x
         << pos_y << y 
         << vel_x << velocityX 
         << vel_y << velocityX 
         << curr_state << static_cast<int>(state);


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
