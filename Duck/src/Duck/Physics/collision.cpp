#include "duckpch.h"
#include "collision.h"
#include <GLFW/glfw3.h>
#include "Duck/Time.h"

namespace Duck {
	// Constructors
	AABB::AABB() : minVec(0, 0), maxVec(0, 0) {}
	AABB::AABB(const MathLib::Vector2D& minVec, const MathLib::Vector2D& maxVec)
		: minVec(minVec), maxVec(maxVec) {}

	AABB AABB::ConvertToAABB(float x, float y, float width, float height) {

		AABB boundingBox;
		boundingBox.minVec.x = x;
		boundingBox.minVec.y = y;
		boundingBox.maxVec.x = x + width;
		boundingBox.maxVec.y = y + height;
		return boundingBox;
	}
	template <typename T>
	T PhysicsLib::Max(const T& a, const T& b) {
		return (a > b) ? a : b;
	}


	bool PhysicsLib::CollisionIntersection_RectRect(const AABB& aabb1, const MathLib::Vector2D& vel1,
		const AABB& aabb2, const MathLib::Vector2D& vel2)
	{
		DeltaTime time;
		time.Update(); // Call this at the beginning of each frame

		float dt = time.GetDeltaTime();
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
				std::cout << "player on the left" << std::endl;
				return 0;
			}

			//| rect A | -> | rect B |
			if (aabb1.maxVec.x < aabb2.minVec.x) {
				std::cout << "player most right while moving" << std::endl;
				tFirst.x = Max((aabb1.maxVec.x - aabb2.minVec.x) / vRel.x, tFirst.x);
			}

			//| rect A | <- | rect B |
			else if (aabb1.minVec.x < aabb2.maxVec.x) {
			//	std::cout << "object most right while moving" << std::endl;
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
				//std::cout << aabb1.maxVec.x<< " "<< aabb2.minVec.x << std::endl;
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
	//bool PhysicsLib::CollisionIntersection_RectRect(const AABB& aabb1, const MathLib::Vector2D& vel1,
	//	const AABB& aabb2, const MathLib::Vector2D& vel2)
	//{
	//	if ((aabb1.minVec.x < aabb2.maxVec.x) &&
	//		(aabb1.maxVec.x > aabb2.minVec.x) &&
	//		(aabb1.maxVec.y > aabb2.minVec.y) &&
	//		(aabb1.minVec.y < aabb2.maxVec.y)
	//		)
	//	{

	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}


	bool PhysicsLib::IsOutOfBounds(const AABB& boundingBox, const AABB& other) const {
		// Check for collision between the boundingBox and the other AABB
		return  (other.maxVec.x > boundingBox.maxVec.x) || (other.minVec.x < boundingBox.minVec.x) ||
				(boundingBox.minVec.y >other.minVec.y) || (other.maxVec.y > boundingBox.maxVec.y);

	}

	float PhysicsLib::CalculateXIntersectionDepth(const AABB& aabb1, const AABB& aabb2) {
		// Calculate the half-widths of the AABBs
		float halfWidth1 = 1.f;
		float halfWidth2 = 1.f;

		// Calculate the center positions of the AABBs
		float center1 = aabb1.minVec.x + halfWidth1;
		float center2 = aabb2.minVec.x + halfWidth2;

		// Calculate the absolute difference in center positions
		float centerDiff = fabs(center1 - center2);

		// Calculate the sum of half-widths
		float sumHalfWidths = halfWidth1 + halfWidth2;

		// Calculate the depth of intersection
		float intersectionDepthX = sumHalfWidths - centerDiff;

		// Return the depth of intersection (may be negative if no overlap)
		return intersectionDepthX;
	}


}

