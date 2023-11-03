//---------------------------------------------------------
// File:		PlayerComponent.cpp
// 
// authors:		Kristy Lee Yu Xuan
// email:		kristyyuxuan.lee\@digipen.edu
//
// Brief:       This  ile defines the functions in the PlayerComponent class.
//
// Copyright ? 2023 DigiPen, All rights reserved.
//-------------------------------------------------------
#pragma once

#include "Duck/Math/Vector2D.h"

namespace Duck
{

	class PlayerComponent
	{
	public:
		PlayerComponent() = default;

		bool IsMoving() { return moving; }
		unsigned const int GetPlayerVelocity() { return playerVelocity; }
		int GetPlayerOrientation() { return playerOrientation; }
		float GetPercentMove() { return percentMove; }
		MathLib::Vector2D GetInitialPos() { return initialPosition; }

		void SetMoving(bool move) { moving = move; }
		void SetPlayerOrientation(int orientation) { playerOrientation = orientation; }
		void SetPercentMove(float x) { percentMove = x; }
		void SetInitialPosition(MathLib::Vector2D newPos) { initialPosition = newPos; }

	private:
		bool moving = false;

		unsigned int playerVelocity = 20;
		unsigned int playerAcceleration = 5;

		int playerOrientation = 0;

		float percentMove{};
		MathLib::Vector2D initialPosition{};
	};

}