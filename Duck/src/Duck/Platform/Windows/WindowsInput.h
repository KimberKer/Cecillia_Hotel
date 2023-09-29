//---------------------------------------------------------
// File:    WindowsInput.cpp
//authors:	Kimber Ker Soon Kiat
// email:	s.ker\@digipen.edu
// 
//
// Brief:     Contains the decalrations for windows input
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include "Duck/Input.h"

namespace Duck {
	class WindowsInput : public Input {
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float>GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}