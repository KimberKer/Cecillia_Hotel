//---------------------------------------------------------
// File:    Entity.h
//authors:	Kimber Ker Soon Kiat
// email:	s.ker\@digipen.edu
// 
//
// Brief:     Contains the foundaiton of the ECS
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once

#include <iostream>
#include <bitset>
#include "Components.h"
#include <queue>

namespace Duck {
	using EntityID = uint32_t;
	using ComponentType = std::uint8_t;

	// Define the size using the max component number
	const ComponentType MAX_COMPONENT = CT_MAXCOMPONENT;
	using Signature = std::bitset<MAX_COMPONENT>;

	class Entity {

	};

	class EntityManager {
		
	};
}