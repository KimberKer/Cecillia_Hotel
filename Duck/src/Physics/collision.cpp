#include "collision.h"
#include <GLFW/glfw3.h>


PhysicsLib physics;
float dt = physics.GetDeltaTime();

PhysicsLib::PhysicsLib() {
	//obtain current time
	startTime = std::chrono::high_resolution_clock::now();
	//stores in current time
	currentTime = startTime;
}

float PhysicsLib::GetDeltaTime() {
	currentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - startTime);
	startTime = currentTime;
	return deltaTime.count();
}


bool PhysicsLib::CollisionIntersection_RectRect(const AABB& aabb1, const MathLib::Vector2D& vel1,
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
	MathLib::Vector2D tLast{ dt, dt };

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

void PhysicsLib::PlayerMovement(bool keyPressed,int longPressedKey, MathLib::Vector2D player_current_position, MathLib::Vector2D player_current_Velocity) {
	//----------sample data until GameObject has been created---------
	const float				PLAYER_VELOCITY				{ 4.0f };
	const float				GRAVITY						{ 0.0f };
	//-----------------------------------------------------------------

	if (keyPressed) {
		switch (longPressedKey) {
			// GLFW_KEY_A -> player moving left
		case GLFW_KEY_A:

			player_current_Velocity.x = -PLAYER_VELOCITY;
			break;

			// GLFW_KEY_D -> player moving right
		case GLFW_KEY_D:
			player_current_Velocity.x = PLAYER_VELOCITY;
			break;

			// GLFW_KEY_W -> player moving up
		case GLFW_KEY_W:
			player_current_Velocity.y = PLAYER_VELOCITY;
			break;

			// GLFW_KEY_S -> player moving down
		case GLFW_KEY_S:
			player_current_Velocity.y = -PLAYER_VELOCITY;
			break;
		}

		//gravity
		player_current_Velocity.y = player_current_Velocity.y - GRAVITY * dt;

		//movement
		player_current_position.x = player_current_Velocity.x * dt + player_current_position.x;
		player_current_position.y = player_current_Velocity.y * dt + player_current_position.y;

	}
}
