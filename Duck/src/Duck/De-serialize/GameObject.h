//---------------------------------------------------------
// File:    GameObject.h
// authors:	Kimber Ker Soon Kiat
// email:	\@digipen.edu
// 
// co-authors:	Rina Firdianna binte Raihan
// email:		rinafirdiana.b\@digipen.edu
//
// Brief:     Contains the declarations related to GameObject class
//
// Copyright   2023 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <unordered_map>
#include <string>
#include "../Physics/collision.h"


enum STATE
{
	STATE_NONE,
	STATE_GOING_LEFT,
	STATE_GOING_RIGHT,
	STATE_GOING_UP,
	STATE_GOING_DOWN,
};
enum OBJ_TYPE
{
	OBJ_EMPTY,
	OBJ_PLAYER,
	OBJ_WALL,
	OBJ_GHOST,
	OBJ_NPC,
	OBJ_OBJ,
	OBJ_ERROR,
	OBJ_COUNT
};

const std::unordered_map<int, OBJ_TYPE> cellToObject = {
	  {0, OBJ_EMPTY},
	  {1, OBJ_PLAYER},
	  {2, OBJ_WALL},
	  {3, OBJ_GHOST},
	  {4, OBJ_NPC},
	  {5, OBJ_OBJ},
};
namespace Duck {
	class GameObject {
	public:
		GameObject();
		GameObject(
			float x,
			float y,
			float velocityX,
			float velocityY,
			int gridCollisionFlag,
			uint32_t image,
			STATE state,
			OBJ_TYPE obj_type
		);

		// Getters
		float getX() const;
		float getY() const;
		float getVelocityX() const;
		float getVelocityY() const;
		STATE getState() const;
		int getgridCollisionFlag() const;
		uint32_t GetImage();
		OBJ_TYPE getObj() const;
		std::shared_ptr<GameObject> CreateObj(float p_x,
			float p_y,
			uint32_t image,
			STATE p_state,
			OBJ_TYPE p_obj_type);



		void  SetState(STATE state);
		void  SetType(OBJ_TYPE getType);
		void  SetVelocityX(float velx);
		void  SetVelocityY(float vely);
		void  SetPositionX(float posX);
		void  SetPositionY(float posY);
		void SetgridCollisionFlag(float posY);
		void SetImage(uint32_t p_image);

		void ReadState(std::string state);
		void ReadObj(std::string obj);

		// Load object properties from a .txt file
		bool loadFromFile(const std::string& filename);

		// Function to load player data
		void loadPlayerData();

	private:
		float x;
		float y;
		float velocityX;
		float velocityY;
		int gridCollisionFlag;
		Duck::AABB boundingBox;
		uint32_t image;
		STATE state;
		OBJ_TYPE obj_type;
	};
}
#endif
