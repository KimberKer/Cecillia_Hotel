#include "duckpch.h"
#include "collision.h"


namespace Duck {

	template <typename T>
	T PhysicsLib::Max(const T& a, const T& b) {
		return (a > b) ? a : b;
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


		MathLib::Vector2D tFirst{ 0, 0 };
		MathLib::Vector2D tLast{ static_cast<float>(time.getDeltaTime()), static_cast<float>(time.getDeltaTime())};

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

				tFirst.x = max((aabb1.max.x - aabb2.min.x) / vRel.x, tFirst.x);
			}

			//| rect A | <- | rect B |
			else if (aabb1.min.x < aabb2.max.x) {
				tLast.x = max((aabb1.min.x - aabb2.max.x) / vRel.x, tLast.x);
			}

		}
		else {

			//no intersection 
			if (aabb1.max.x < aabb2.min.x)
			{
				return 0;
			}

			if (aabb1.max.x > aabb2.min.x) {
				tFirst.x = max((aabb1.max.x - aabb2.min.x) / vRel.x, tFirst.x);
			}
			else if (aabb1.max.x > aabb2.min.x) {
				tLast.x = max((aabb1.max.x - aabb2.min.x) / vRel.x, tLast.x);
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

				tFirst.y = max((aabb1.max.y - aabb2.min.y) / vRel.y, tFirst.y);
			}

			//| rect A | <- | rect B |
			else if (aabb1.min.y < aabb2.max.y) {
				tLast.y = max((aabb1.min.y - aabb2.max.y) / vRel.y, tLast.y);
			}

		}
		else {

			//no intersection 
			if (aabb1.max.y < aabb2.min.y)
			{
				return false;
			}

			if (aabb1.max.y > aabb2.min.y) {
				tFirst.y = max((aabb1.max.y - aabb2.min.y) / vRel.y, tFirst.y);
			}
			else if (aabb1.max.x > aabb2.min.x) {
				tLast.y = max((aabb1.max.y - aabb2.min.y) / vRel.y, tLast.y);
			} 

		}

		//no intersection
		if (tFirst.y > tLast.y) {
			return 0;
		}


		return 1;

	}

	//void PhysicsLib::PlayerMovement(bool keyPressed, int longPressedKey, MathLib::Vector2D player_current_position, MathLib::Vector2D player_current_Velocity) {
	//	//----------sample data until GameObject has been created---------
	//	const float				PLAYER_VELOCITY{ 4.0f };
	//	const float				GRAVITY{ 0.0f };
	//	//-----------------------------------------------------------------
	//
	//	if (keyPressed) {
	//		switch (longPressedKey) {
	//			// GLFW_KEY_A -> player moving left
	//		case GLFW_KEY_A:
	//
	//			player_current_Velocity.x = -PLAYER_VELOCITY;
	//			break;
	//
	//			// GLFW_KEY_D -> player moving right
	//		case GLFW_KEY_D:
	//			player_current_Velocity.x = PLAYER_VELOCITY;
	//			break;
	//
	//			// GLFW_KEY_W -> player moving up
	//		case GLFW_KEY_W:
	//			player_current_Velocity.y = PLAYER_VELOCITY;
	//			break;
	//
	//			// GLFW_KEY_S -> player moving down
	//		case GLFW_KEY_S:
	//			player_current_Velocity.y = -PLAYER_VELOCITY;
	//			break;
	//		}
	//
	//		//gravity
	//		player_current_Velocity.y = player_current_Velocity.y - GRAVITY * deltaTime.count();
	//
	//		//movement
	//		player_current_position.x = player_current_Velocity.x * deltaTime.count() + player_current_position.x;
	//		player_current_position.y = player_current_Velocity.y * deltaTime.count() + player_current_position.y;
	//
	//	}
	//}
}


