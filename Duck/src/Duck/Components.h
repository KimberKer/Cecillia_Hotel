//---------------------------------------------------------
// File:    Components.h
//authors:	Kimber Ker Soon Kiat
// email:	s.ker\@digipen.edu
// 
//
// Brief:     Contains the definition enum ComponentTypeID
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

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