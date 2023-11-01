#pragma once

#include "Duck/ECS/Entity.h"
#include "Duck/De-serialize/GameObject.h"


namespace Duck
{

	class PhysicsSystem : public System
	{
	public:
		void Init();

		void Update(double dt, int cellSize);

	};

}