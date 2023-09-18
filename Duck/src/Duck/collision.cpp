#include "collision.h"
#include <iostream>

bool CollisionIntersection_RectRect(const AABB& aabb1, const MathLib::Vector2D& vel1,
	const AABB& aabb2, const MathLib::Vector2D& vel2)
{


	//No intersection
	if (aabb1.max.x < aabb2.min.x || aabb1.min.x > aabb2.max.x ||
		aabb1.max.y < aabb2.min.y || aabb1.min.y > aabb2.max.y) {
		//nothing
	}
	//overlap
	else
		return 1;


	MathLib::Vector2D tFirst{ 0.f, 0.f };
	MathLib::Vector2D tLast{ g_dt, g_dt };

	// Initialize and calculate the new velocity of Vb

	MathLib::Vector2D vRel;
	vRel.x = vel2.x - vel1.x;
	vRel.y = vel2.y - vel1.y;


	if (vRel.x < 0) {
		//no intersection
		if (aabb1.min.x > aabb2.max.x) {
			return 0;
		}

		//| rect A | -> | rect B |
		if (aabb1.max.x < aabb2.min.x) {

			tFirst.x = std::max((aabb1.max.x - aabb2.min.x) / vRel.x, tFirst.x);
		}

		//| rect A | <- | rect B |
		else if (aabb1.min.x < aabb2.max.x) {
			tLast.x = std::max((aabb1.min.x - aabb2.max.x) / vRel.x, tLast.x);
		}

	}
	else {

		//no intersection 
		if (aabb1.max.x < aabb2.min.x)
		{
			return 0;
		}

		if (aabb1.max.x > aabb2.min.x) {
			tFirst.x = std::max((aabb1.max.x - aabb2.min.x) / vRel.x, tFirst.x);
		}
		else if (aabb1.max.x > aabb2.min.x) {
			tLast.x = std::max((aabb1.max.x - aabb2.min.x) / vRel.x, tLast.x);
		}

	}

	//no intersection
	if (tFirst.x > tLast.x) {
		return 0;
	}

	//-------------------------------------Y-AXIS--------------------------

	if (vRel.y < 0) {
		//no intersection
		if (aabb1.min.y > aabb2.max.y) {
			return 0;
		}

		//| rect A | -> | rect B |
		if (aabb1.max.y < aabb2.min.y) {

			tFirst.y = std::max((aabb1.max.y - aabb2.min.y) / vRel.y, tFirst.y);
		}

		//| rect A | <- | rect B |
		else if (aabb1.min.y < aabb2.max.y) {
			tLast.y = std::max((aabb1.min.y - aabb2.max.y) / vRel.y, tLast.y);
		}

	}
	else {

		//no intersection 
		if (aabb1.max.y < aabb2.min.y)
		{
			return false;
		}

		if (aabb1.max.y > aabb2.min.y) {
			tFirst.y = std::max((aabb1.max.y - aabb2.min.y) / vRel.y, tFirst.y);
		}
		else if (aabb1.max.x > aabb2.min.x) {
			tLast.y = std::max((aabb1.max.y - aabb2.min.y) / vRel.y, tLast.y);
		}

	}

	//no intersection
	if (tFirst.y > tLast.y) {
		return 0;
	}


	return 1;

}