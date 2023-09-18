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

struct LineSegment
{
	MathLib::Vector2D	m_pt0;
	MathLib::Vector2D	m_pt1;
	MathLib::Vector2D	m_normal;
};

void BuildLineSegment(LineSegment& lineSegment,								//Line segment reference - input
	const MathLib::Vector2D& p0,									//Point P0 - input
	const MathLib::Vector2D& p1);									//Point P1 - input

/******************************************************************************/
/*!
	initialize struct Circle
 */
 /******************************************************************************/
struct Circle
{
	MathLib::Vector2D  m_center;
	float	m_radius;
};


// INTERSECTION FUNCTIONS
int CollisionIntersection_CircleLineSegment(const Circle& circle,			//Circle data - input
	const MathLib::Vector2D& ptEnd,													//End circle position - input
	const LineSegment& lineSeg,												//Line segment - input
	MathLib::Vector2D& interPt,														//Intersection point - output
	MathLib::Vector2D& normalAtCollision,												//Normal vector at collision time - output
	float& interTime,														//Intersection time ti - output
	bool& checkLineEdges);													//The last parameter is for Extra Credits: when true => check collision with line segment edges



// For Extra Credits
int CheckMovingCircleToLineEdge(bool withinBothLines,						//Flag stating that the circle is starting from between 2 imaginary line segments distant +/- Radius respectively - input
	const Circle& circle,													//Circle data - input
	const MathLib::Vector2D& ptEnd,													//End circle position - input
	const LineSegment& lineSeg,												//Line segment - input
	MathLib::Vector2D& interPt,														//Intersection point - output
	MathLib::Vector2D& normalAtCollision,												//Normal vector at collision time - output
	float& interTime);														//Intersection time ti - output



// RESPONSE FUNCTIONS
void CollisionResponse_CircleLineSegment(const MathLib::Vector2D& ptInter,				//Intersection position of the circle - input
	const MathLib::Vector2D& normal,													//Normal vector of reflection on collision time - input
	MathLib::Vector2D& ptEnd,															//Final position of the circle after reflection - output
	MathLib::Vector2D& reflected);														//Normalized reflection vector direction - output


MathLib::Vector2D NormalizeVector(MathLib::Vector2D& vector);

#endif // MathLib_COLLISION_H_