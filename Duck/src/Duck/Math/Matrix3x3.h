//---------------------------------------------------------
// File:		Matrix3x3.h
// 
// authors:		Kristy Lee Yu Xuan
// email:		kristyyuxuan.lee\@digipen.edu
//
// Brief:       This header file defines the classes aand functions
//              related to 3x3 matrixes.
//
// Copyright � 2023 DigiPen, All rights reserved.
//-------------------------------------------------------

#pragma once
#include "duckpch.h"
#include "Vector2D.h"
#include <math.h>
#include <iostream>


namespace MathLib
{

	typedef union Matrix3x3
	{
		struct 
		{
			float m00, m01, m02;
			float m10, m11, m12;
			float m20, m21, m22;
		};

		float m[9];
		float m2[3][3];

		Matrix3x3() : m00(0.0f), m01(0.0f), m02(0.0f), m10(0.0f), m11(0.0f), m12(0.0f), m20(0.0f), m21(0.0f), m22(0.0f) {}
		Matrix3x3(const float *pArr);
		Matrix3x3(float _00, float _01, float _02,
				  float _10, float _11, float _12,
				  float _20, float _21, float _22);
		Matrix3x3& operator=(const Matrix3x3 &rhs);

		Matrix3x3(const Matrix3x3& rhs) = default;

		Matrix3x3& operator *= (const Matrix3x3 &rhs);

	} Matrix3x3, Mtx33;

	Matrix3x3 operator * (const Matrix3x3 &lhs, const Matrix3x3 &rhs);
	
	Vector2D  operator * (const Matrix3x3 &pMtx, const Vector2D &rhs);
	
	void Mtx33Identity(Matrix3x3 &pResult);
	void Mtx33Translate(Matrix3x3 &pResult, float x, float y);
	void Mtx33Scale(Matrix3x3 &pResult, float x, float y);
	void Mtx33RotRad(Matrix3x3 &pResult, float angle);
	void Mtx33RotDeg(Matrix3x3 &pResult, float angle);
	void Mtx33Transpose(Matrix3x3 &pResult, const Matrix3x3 &pMtx);
	void Mtx33Inverse(Matrix3x3 *pResult, float *determinant, const Matrix3x3 &pMtx);

}