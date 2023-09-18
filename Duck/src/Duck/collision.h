#pragma once
#include "Vector2D.h"

#ifndef MathLib_COLLISION_H_
#define MathLib_COLLISION_H_

struct AABB
{
	MathLib::Vector2D	min;
	MathLib::Vector2D	max;
};

bool CollisionIntersection_RectRect(const AABB& aabb1, const MathLib::Vector2D& vel1,
	const AABB& aabb2, const MathLib::Vector2D& vel2);

#endif // MathLib_COLLISION_H_