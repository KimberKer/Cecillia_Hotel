//---------------------------------------------------------
// File:    Camera.cpp
//authors:	Ahmad Mahdi Bin Jamal
// email:	ahmadmahdi.b@digipen.edu
// 
//
// Brief:   
// 
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "duckpch.h"
#include "Camera.h"


namespace Duck {




	Camera::Camera(float X, float Y) {

		PosX = X;
		PosY = Y;

		
		mView = { 
			
			zoom,  0.f,  0.f, 0.f,
			0.f,  zoom,  0.f, 0.f,
			0.f,  0.f,  1.f, 0.f, 
			-PosX, PosY, 0.f, 1.f};

	}
	
	Camera::~Camera() {

	}


	glm::mat4 Camera::getViewMatrix() const {

		return mView;

	}

	void Camera::UpdateCamPos(float X, float Y) {

		PosX = X - (X * (1.f - zoom));
		PosY = Y - (Y * (1.f - zoom));

		mView = {

			zoom,  0.f,  0.f, 0.f,
			0.f,  zoom,  0.f, 0.f,
			0.f,  0.f,  1.f, 0.f,
			-PosX, PosY, 0.f, 1.f };


	}

	void Camera::UpdateCamZoom( float Zoom) {


		// Limit zoom to between 0.5 and 2.
		zoom = (Zoom < 0.5f) ? 0.5f : Zoom;
		zoom = (Zoom > 2.f) ? 2.f : Zoom;


		PosX = PosX - (PosX * (1.f - zoom));
		PosY = PosY - (PosY * (1.f - zoom));


		mView = {

			zoom,  0.f,  0.f, 0.f,
			0.f,  zoom,  0.f, 0.f,
			0.f,  0.f,  1.f, 0.f,
			-PosX, PosY, 0.f, 1.f };


	}






}

