//---------------------------------------------------------
// File:    Camera.h
//authors:	Ahmad Mahdi Bin Jamal
// email:	ahmadmahdi.b@digipen.edu
// 
//
// Brief:   
// 
// 
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include <glm/gtc/matrix_transform.hpp>


namespace Duck {




	class Camera {

	public:

		Camera(float X = 0.f, float Y = 0.f);
		~Camera();

		glm::mat4 getViewMatrix() const;

		void UpdateCamPos(float X, float Y);
		void UpdateCamZoom(float Zoom);



	private:

		float PosX;
		float PosY;
		float zoom = 1.f;
		glm::mat4 mView;



	};

}