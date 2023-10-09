//---------------------------------------------------------
// File:		Time.h
// 
// authors:		Kristy Lee Yu Xuan
// email:		kristyyuxuan.lee\@digipen.edu
//
// Brief:       This header file defines the classes aand functions
//              related to time.
//
// Copyright © 2023 DigiPen, All rights reserved.
//-------------------------------------------------------

#pragma once

namespace Duck
{

	class Time
	{

	public:
		Time(double fps = 60.0);

		void update();
		double getElapsedTime() const;
		double getDeltaTime() const;
		double getFPS() const;
		double getFrameTime() const;

	private:
		double limitFPS;

		double frameTime;
		double lastFrameTime;

		double elapsedTime;
		double deltaTime;

	};

}