//---------------------------------------------------------
// File:    Camera.h
//authors:	Ahmad Mahdi Bin Jamal
// email:	ahmadmahdi.b@digipen.edu
// 
//
// Brief:   Declaration of the Camera class, providing a simple 2D camera
//          implementation with position and zoom controls. The camera 
//          uses glm for matrix operations to generate a view matrix, 
//          facilitating integration into graphics systems.
// 
// 
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include <glm/gtc/matrix_transform.hpp>


namespace Duck {



	// Class declaration for a simple 2D Camera
	class Camera {

	public:

		// Constructor with default position values
		Camera(float X = 0.f, float Y = 0.f);
		// Destructor
		~Camera();

		// Get the view matrix generated based on camera parameters
		glm::mat4 getViewMatrix() const;

		// Update camera position
		void UpdateCamPos(float X, float Y);
		// Update camera zoom level
		void UpdateCamZoom(float Zoom);



	private:

		// Camera position variable
		float PosX;
		float PosY;

		// Zoom level, initial zoom, and the previous zoom level
		float zoom = 1.f;
		float prevZoom = 1.f;

		// View matrix for the camera
		glm::mat4 mView;
		



	};

}