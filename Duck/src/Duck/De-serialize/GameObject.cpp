//---------------------------------------------------------
// File:    GameObject.cpp
//authors:	Kimber Ker Soon Kiat
// email:	\@digipen.edu
// 
// co-authors:	Rina Firdianna binte Raihan
// email:	rinafirdiana.b\@digipen.edu
//
// Brief:     Contains the implementation of the GameObject class
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include "duckpch.h"
#include "GameObject.h"


namespace Duck {
	GameObject::GameObject()
		: x(0.0f),
		y(0.0f),
		velocityX(0.0f),
		velocityY(0.0f),
		gridCollisionFlag(0.0f),
		boundingbox({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
		state(STATE_NONE),
		obj_type(OBJ_EMPTY) {}

	GameObject::GameObject(float x, float y, float velocityX, float velocityY, int gridCollisionFlag, Duck::AABB boundingbox, STATE getstate, OBJ_TYPE obj_type)
		: x(x), y(y), velocityX(velocityX), velocityY(velocityY), gridCollisionFlag(gridCollisionFlag), boundingbox(boundingbox), state(getstate), obj_type(obj_type) {}


	STATE GameObject::getState() const {
		return state;
	}
	void GameObject::SetState(STATE getstate) {
		state = getstate;
	}
	float GameObject::getX() const {
		return x;
	}
	int GameObject::getgridCollisionFlag() const {
		return gridCollisionFlag;
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
	void GameObject::SetgridCollisionFlag(float posY) {
		gridCollisionFlag = posY;
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
	Duck::AABB GameObject::getBoundingBox() const {
		return boundingbox;
	}

	bool GameObject::loadFromFile(const std::string& filename) {
		std::string pos_x, pos_y, vel_x, vel_y, curr_state, bounding, type, getstate, getType, gridFlag;
		// Specify the absolute path to "player.txt"
		const std::string path = "../txtfiles/" + filename;

		std::ifstream file(path);
		if (!file.is_open()) {
			std::cerr << "Error: Unable to open file " << path << std::endl;
			return false;
		}

		float minx, miny, maxx, maxy;
		// Read and parse data from the file
		file >> pos_x >> x
			>> pos_y >> y
			>> vel_x >> velocityX
			>> vel_y >> velocityX
			>> gridFlag >> gridCollisionFlag
			>> bounding >> minx >> miny >> maxx >> maxy
			>> curr_state >> getstate
			>> type >> getType;

		ReadState(getstate);
		ReadObj(getType);

		MathLib::Vector2D minVec(minx, miny);
		MathLib::Vector2D maxVec(maxx, maxy);
		boundingbox = { minVec, maxVec };

		file.close();
		return true;
	}

	void GameObject::ReadState(std::string state) {
		if (state == "STATE_NONE") {
			state = STATE_NONE;
		}
		else if (state == "STATE_GOING_LEFT") {
			state = STATE_GOING_LEFT;
		}
		else if (state == "STATE_GOING_RIGHT") {
			state = STATE_GOING_RIGHT;
		}
		else if (state == "STATE_GOING_UP") {
			state = STATE_GOING_UP;
		}
		else if (state == "STATE_GOING_UP") {
			state = STATE_GOING_UP;
		}
	}

	void GameObject::ReadObj(std::string obj) {
		if (obj == "OBJ_EMPTY") {
			obj_type = OBJ_EMPTY;
		}
		else if (obj == "STATE_GOING_LEFT") {
			obj_type = OBJ_PLAYER;
		}
		else if (obj == "STATE_GOING_RIGHT") {
			obj_type = OBJ_GHOST;
		}
		else if (obj == "STATE_GOING_UP") {
			obj_type = OBJ_NPC;
		}
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
}
