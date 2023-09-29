//---------------------------------------------------------
// File:    MouseCodes.h
//authors:	Kimber Ker Soon Kiat
// email:	s.ker\@digipen.edu
// 
//
// Brief:     Contains the declarations for mouse codes
// 
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include <stdint.h>

namespace Duck {
	// Define an alias for the mouse code
	using MouseCode = uint16_t;

	namespace Mouse {
		enum : MouseCode {
			// Mouse button codes

			// From glfw3.h
			Button0 = 0,       // Left mouse button
			Button1 = 1,       // Right mouse button
			Button2 = 2,       // Middle mouse button
			Button3 = 3,       // Mouse button 3
			Button4 = 4,       // Mouse button 4
			Button5 = 5,       // Mouse button 5
			Button6 = 6,       // Mouse button 6
			Button7 = 7,       // Mouse button 7

			ButtonLast = Button7,  // The last available mouse button
			ButtonLeft = Button0,  // Alias for the left mouse button
			ButtonRight = Button1, // Alias for the right mouse button
			ButtonMiddle = Button2 // Alias for the middle mouse button
		};
	}
}
