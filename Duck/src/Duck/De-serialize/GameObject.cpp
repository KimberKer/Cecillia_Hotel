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

	void GameObject::CreateObj(	float p_x,
								float p_y,
								float p_velocityX,
								float p_velocityY,
								int p_gridCollisionFlag,
								Duck::AABB p_boundingbox,
								STATE p_state,
								OBJ_TYPE p_obj_type)
	{
		x = p_x;
		y = p_y;
		velocityX = p_velocityX;
		velocityY = p_velocityY;
		gridCollisionFlag = p_gridCollisionFlag;
		boundingbox = p_boundingbox;
		state = p_state;
		obj_type = p_obj_type;

	}
	/******************************************************************************/
	/*!
		This function returns the current state of the GameObject.
	 */
	 /******************************************************************************/
	STATE GameObject::getState() const {
		return state;
	}

	/******************************************************************************/
	/*!
		This function sets the state of the GameObject.
	 */
	 /******************************************************************************/
	void GameObject::SetState(STATE getstate) {
		state = getstate;
	}

	/******************************************************************************/
	/*!
		This function gets X position
	 */
	 /******************************************************************************/
	float GameObject::getX() const {
		return x;
	}

	/******************************************************************************/
	/*!
		This function returns the grid collision flag of the GameObject.
	 */
	 /******************************************************************************/
	int GameObject::getgridCollisionFlag() const {
		return gridCollisionFlag;
	}

	/******************************************************************************/
	/*!
		This function sets the X-axis velocity of the GameObject.
	 */
	 /******************************************************************************/
	void GameObject::SetVelocityX(float velx) {
		velocityX = velx;
	}

	/******************************************************************************/
	/*!
		This function sets the Y-axis velocity of the GameObject.
	 */
	 /******************************************************************************/
	void GameObject::SetVelocityY(float vely) {
		velocityY = vely;
	}

	/******************************************************************************/
	/*!
		This function sets the X-coordinate of the GameObject.
	 */
	 /******************************************************************************/
	void GameObject::SetPositionX(float posX) {
		x = posX;
	}

	/******************************************************************************/
	/*!
		This function sets the Y-coordinate of the GameObject.
	 */
	 /******************************************************************************/
	void GameObject::SetPositionY(float posY) {
		y = posY;
	}

	/******************************************************************************/
	/*!
		This function sets the grid collision flag of the GameObject.
	 */
	 /******************************************************************************/
	void GameObject::SetgridCollisionFlag(float posY) {
		gridCollisionFlag = static_cast<float>(posY);
	}

	/******************************************************************************/
	/*!
		This function get the grid Y-coordinate of the GameObject.
	 */
	 /******************************************************************************/
	float GameObject::getY() const {
		return y;
	}

	/******************************************************************************/
	/*!
		This function get the X-axis velocity of the GameObject.
	 */
	 /******************************************************************************/
	float GameObject::getVelocityX() const {
		return velocityX;
	}

	/******************************************************************************/
	/*!
		This function get the Y-axis velocity of the GameObject.
	 */
	 /******************************************************************************/
	float GameObject::getVelocityY() const {
		return velocityY;
	}

	/******************************************************************************/
	/*!
		This function loads GameObject data from a file.
	 */
	 /******************************************************************************/
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

	/******************************************************************************/
	/*!
		This function reads and sets the state of the GameObject.
	 */
	 /******************************************************************************/
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

	/******************************************************************************/
	/*!
		This function reads and sets the object type.
	 */
	 /******************************************************************************/
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

	/******************************************************************************/
	/*!
		This function loads player data from a file
	 */
	 /******************************************************************************/
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
