//---------------------------------------------------------
// File:    Camera.cpp
//authors:	Ahmad Mahdi Bin Jamal
// email:	ahmadmahdi.b@digipen.edu
// 
//
// Brief:   Implementation of the Camera class for managing
//          a virtual camera in a 2D scene.
// 
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "duckpch.h"
#include "Camera.h"


namespace Duck {



	// Constructor for the Camera class.
	// Initializes the camera position and view matrix.
	Camera::Camera(float X, float Y) {

		PosX = X;
		PosY = Y;

		// Initialize the view matrix with translation based on PosX and PosY.
		mView = { 
			
			zoom,  0.f,  0.f, 0.f,
			0.f,  zoom,  0.f, 0.f,
			0.f,  0.f,  1.f, 0.f, 
			-PosX, PosY, 0.f, 1.f};

	}
	
	// Destructor for the Camera class.
	Camera::~Camera() {

	}

	// Get the current view matrix of the camera.
	glm::mat4 Camera::getViewMatrix() const {

		return mView;

	}


	// Update the camera position based on provided X and Y coordinates.
	// Recalculates the view matrix with the updated position.
	void Camera::UpdateCamPos(float X, float Y) {

		PosX = X - (X * (1.f - zoom));
		PosY = Y - (Y * (1.f - zoom));

		mView = {

			zoom,  0.f,  0.f, 0.f,
			0.f,  zoom,  0.f, 0.f,
			0.f,  0.f,  1.f, 0.f,
			-PosX, PosY, 0.f, 1.f };


	}


	// Update the camera zoom factor.
	// Limits the zoom factor to be between 0.5 and 2.
	// Recalculates the view matrix with the updated zoom and position.
	void Camera::UpdateCamZoom( float Zoom) {


		// Limit zoom to between 0.5 and 2.
		zoom = (Zoom < 0.5f) ? 0.5f : Zoom;
		zoom = (Zoom > 2.f) ? 2.f : Zoom;

		// Calculate the adjustment based on the change in zoom
	// Calculate the adjustment based on the change in zoom
		float zoomFactor = zoom / prevZoom;

		// Update the translation components
		PosX *= zoomFactor;
		PosY *= zoomFactor;

		// Update the zoom factor for the next frame
		prevZoom = zoom;

		mView = {

			zoom,  0.f,  0.f, 0.f,
			0.f,  zoom,  0.f, 0.f,
			0.f,  0.f,  1.f, 0.f,
			-PosX, PosY, 0.f, 1.f };


	}






}

