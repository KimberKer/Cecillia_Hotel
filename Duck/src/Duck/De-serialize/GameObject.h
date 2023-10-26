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

#include <string>
#include "../Physics/collision.h"
#include "../Map/map.h"

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
	OBJ_OBJ,
	OBJ_GHOST,
	OBJ_NPC,
	OBJ_WALL,
	OBJ_ERROR,
	OBJ_COUNT
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
		OBJ_TYPE getObj() const;
		std::shared_ptr<GameObject> CreateObj(float p_x,
			float p_y,
			float p_velocityX,
			float p_velocityY,
			int p_gridCollisionFlag,
			Duck::AABB p_boundingbox,
			STATE p_state,
			OBJ_TYPE p_obj_type);


		void  SetState(STATE state);
		void  SetType(OBJ_TYPE getType);
		void  SetVelocityX(float velx);
		void  SetVelocityY(float vely);
		void  SetPositionX(float posX);
		void  SetPositionY(float posY);
		void SetgridCollisionFlag(float posY);

		void ReadState(std::string state);
		void ReadObj(std::string obj);
		std::shared_ptr<GameObject> CreateObj(float x,
			float y,
			STATE state,
			OBJ_TYPE obj_type);

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
		MapDataHandler m_map;
		STATE state;
		OBJ_TYPE obj_type;
	};
}
#endif
