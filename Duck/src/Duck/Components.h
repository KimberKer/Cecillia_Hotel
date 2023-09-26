#pragma once
namespace Duck {
	enum ComponentTypeID {
		CT_NONE = 0,
		CT_TRANSFORM = 2,
		CT_RIGIDBODY = 4,
		CT_MAXCOMPONENT = 8,
		CT_DRAWABLES = 16
	};
}