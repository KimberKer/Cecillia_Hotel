//---------------------------------------------------------
// File:		collision.cpp
// 
// authors:		Rina Firdianna binte Raihan
// email:		rinafirdiana.b\@digipen.edu
//
// Brief:       This file contains function and classes
//				related to collision detection and handling, 
//				including AABB (Axis-Aligned Bounding Box) 
//				calculations.
//
// Copyright © 2023 DigiPen, All rights reserved.
//-------------------------------------------------------
#include "duckpch.h"
#include "collision.h"
#include <GLFW/glfw3.h>
#include "Duck/Time.h"

namespace Duck {
	// Constructors
	AABB::AABB() : minVec(0, 0), maxVec(0, 0) {}
	AABB::AABB(const MathLib::Vector2D& minVec, const MathLib::Vector2D& maxVec)
		: minVec(minVec), maxVec(maxVec) {}

	/******************************************************************************/
	/*!
		This function converts coordinates and dimensions to an AABB.
	*/
	/******************************************************************************/
	AABB AABB::ConvertToAABB(float x, float y, float width, float height) {

		AABB boundingBox;
		boundingBox.minVec.x = x;
		boundingBox.minVec.y = y;
		boundingBox.maxVec.x = x + width;
		boundingBox.maxVec.y = y + height;
		return boundingBox;
	}

	/******************************************************************************/
	/*!
		Template function to return the maximum of two values.
	*/
	/******************************************************************************/
	template <typename T>
	T PhysicsLib::Max(const T& a, const T& b) {
		return (a > b) ? a : b;
	}

	/******************************************************************************/
	/*!
		Template function checks for intersection between two AABBs with velocities.
	*/
	/******************************************************************************/
	bool PhysicsLib::CollisionIntersection_RectRect(const AABB& aabb1, const MathLib::Vector2D& vel1,
		const AABB& aabb2, const MathLib::Vector2D& vel2)
	{
		Time time;
		time.update(); // Call this at the beginning of each frame

		double dt = time.getDeltaTime();
		//No intersection
		if ((aabb1.minVec.x < aabb2.maxVec.x) &&
			(aabb1.maxVec.x > aabb2.minVec.x) &&
			(aabb1.maxVec.y > aabb2.minVec.y) &&
			(aabb1.minVec.y < aabb2.maxVec.y)
			)
		{

			return true;
		}
		//overlap
		else
		{
			return false;
		}


		MathLib::Vector2D tFirst{ 0, 0 };
		MathLib::Vector2D tLast{ static_cast<float>(dt), static_cast<float>(dt) };

		// Initialize and calculate the new velocity of Vb

		MathLib::Vector2D vRel;
		vRel.x = vel2.x - vel1.x;
		vRel.y = vel2.y - vel1.y;


		if (vRel.x < 0) {
			//no intersection
			if (aabb1.minVec.x > aabb2.maxVec.x) {
				return 0;
			}

			//| rect A | -> | rect B |
			if (aabb1.maxVec.x < aabb2.minVec.x) {
				tFirst.x = Max((aabb1.maxVec.x - aabb2.minVec.x) / vRel.x, tFirst.x);
			}

			//| rect A | <- | rect B |
			else if (aabb1.minVec.x < aabb2.maxVec.x) {
				tLast.x = Max((aabb1.minVec.x - aabb2.maxVec.x) / vRel.x, tLast.x);
			}

		}
		else {
			//no intersection 
			if (aabb1.maxVec.x < aabb2.minVec.x)
			{
				return 0;
			}
			//if player is collding at the right side
			if (aabb1.maxVec.x > aabb2.minVec.x) {
				tFirst.x = Max((aabb1.maxVec.x - aabb2.minVec.x) / vRel.x, tFirst.x);
			}

			else if (aabb1.minVec.x < aabb2.maxVec.x) {
		
				tLast.x = Max((aabb1.maxVec.x - aabb2.minVec.x) / vRel.x, tLast.x);
			}

		}

		//no intersection
		if (tFirst.x > tLast.x) {
			return 0;
		}

		//-------------------------------------Y-AXIS--------------------------

		if (vRel.y < 0) {
			//no intersection
			if (aabb1.minVec.y > aabb2.maxVec.y) {
				return 0;
			}

			//| rect A | -> | rect B |
			if (aabb1.maxVec.y < aabb2.minVec.y) {
				tFirst.y = Max((aabb1.maxVec.y - aabb2.minVec.y) / vRel.y, tFirst.y);
			}

			//| rect A | <- | rect B |
			else if (aabb1.minVec.y < aabb2.maxVec.y) {
				tLast.y = Max((aabb1.minVec.y - aabb2.maxVec.y) / vRel.y, tLast.y);
			}

		}
		else {

			//no intersection 
			if (aabb1.maxVec.y < aabb2.minVec.y)
			{
				return false;
			}

			if (aabb1.maxVec.y > aabb2.minVec.y) {
				tFirst.y = Max((aabb1.maxVec.y - aabb2.minVec.y) / vRel.y, tFirst.y);
			}
			else if (aabb1.maxVec.x > aabb2.minVec.x) {
				tLast.y = Max((aabb1.maxVec.y - aabb2.minVec.y) / vRel.y, tLast.y);
			}

		}

		//no intersection
		if (tFirst.y > tLast.y) {
			return 0;
		}


		return 1;

	}

	/******************************************************************************/
	/*!
		Template function checks if an AABB is out of bounds compared to another AABB.
	*/
	/******************************************************************************/
	bool PhysicsLib::IsOutOfBounds(const AABB& boundingBox, const AABB& other) const {
		// Check for collision between the boundingBox and the other AABB
		return  (other.maxVec.x > boundingBox.maxVec.x) || (other.minVec.x < boundingBox.minVec.x) ||
				(boundingBox.minVec.y >other.minVec.y) || (other.maxVec.y > boundingBox.maxVec.y);

	}


}

