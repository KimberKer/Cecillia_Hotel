//---------------------------------------------------------
// File:		Time.cpp
// 
// authors:		Kristy Lee Yu Xuan
// email:		kristyyuxuan.lee\@digipen.edu
//
// Brief:       This source file defines the classes aand functions
//              related to time.
//
// Copyright © 2023 DigiPen, All rights reserved.
//-------------------------------------------------------

#include "duckpch.h"
#include "Time.h"

#include <GLFW/glfw3.h>


namespace Duck
{

	/*-----------------------------------------------------------
	\Brief
		Constructor for time

	\Param fps
		Desired fps, default value is 60
	-----------------------------------------------------------*/
	Time::Time(double fps)
	{
		limitFPS = fps;

		frameTime = 1 / limitFPS;
		lastFrameTime = glfwGetTime();

		elapsedTime = 0.0;
		deltaTime = 0.0;
	}

	/*-----------------------------------------------------------
	\Brief
		Function to update time, updates the delta and elapsed time. 
		This function should be called at the beginning of every frame.
	-----------------------------------------------------------*/
	void Time::update()
	{
		double currFrameTime = glfwGetTime();

		deltaTime = currFrameTime - lastFrameTime;
		lastFrameTime = currFrameTime;

		elapsedTime += deltaTime;
	}

	/*-----------------------------------------------------------
	\Brief
		Function to get elapsed time.

	\Return
		Returns the elapsed time from the start of the program
		to the current frame.
	-----------------------------------------------------------*/
	double Time::getElapsedTime() const
	{
		return elapsedTime;
	}

	/*-----------------------------------------------------------
	\Brief
		Function to get delta time.

	\Return
		Returns the delta time of the frame.
	-----------------------------------------------------------*/
	double Time::getDeltaTime() const
	{
		return deltaTime;
	}

	/*-----------------------------------------------------------
	\Brief
		Function to get the desired FPS

	\Return
		Returns the desired FPS of the program. Does not reflect
		the actual FPS.
	-----------------------------------------------------------*/
	double Time::getFPS() const
	{
		return limitFPS;
	}

	/*-----------------------------------------------------------
	\Brief
		Function to get the desired frame time.

	\Return
		Returns the desired frame time of the program. Does not
		reflect the actual frame time.
	-----------------------------------------------------------*/
	double Time::getFrameTime() const
	{
		return frameTime;
	}

}