//---------------------------------------------------------
// File:		Vector2D.cpp
// 
// authors:		Kristy Lee Yu Xuan
// email:		kristyyuxuan.lee\@digipen.edu
//
// Brief:       This source file defines the classes aand functions
//              related to 2D vectors.
//
// Copyright © 2023 DigiPen, All rights reserved.
//-------------------------------------------------------

#include "duckpch.h"
#include "Vector2D.h"
#include <math.h>
#include <iostream>

namespace MathLib
{
	/*-----------------------------------------------------------
	\Brief
		Constructor for Vector2D

	\Param _x
		Desired X value. Default value is 0.

	\Param _y
		Desired Y value. Default value is 0.
	-----------------------------------------------------------*/
	Vector2D::Vector2D(float _x, float _y) : x(_x), y(_y) {};

	/*-----------------------------------------------------------
	\Brief
		Overloaded compound addition assignment operator.
		Adds another 2D vector to the current 2D vector.

	\Param rhs
		2D vector to be added

	\Return
		Returns a reference to the modified 2D vector
	-----------------------------------------------------------*/
	Vector2D& Vector2D::operator += (const Vector2D &rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	/*-----------------------------------------------------------
	\Brief
		Overloaded compound subtraction assignment operator.
		Subtracts another 2D vector from the current 2D vector.

	\Param rhs
		2D vector to be subtracted.

	\Return
		Returns a reference to the modified 2D vector
	-----------------------------------------------------------*/
	Vector2D& Vector2D::operator -= (const Vector2D &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	/*-----------------------------------------------------------
	\Brief
		Overloaded compound multiplication assignment operator.
		Multiple current 2D vector with a scalar value.

	\Param rhs
		Scalar value to be multiplied by.

	\Return
		Returns a reference to the modified 2D vector
	-----------------------------------------------------------*/
	Vector2D& Vector2D::operator *= (float rhs)
	{
		x *= rhs;
		y *= rhs;

		return *this;
	}

	/*-----------------------------------------------------------
	\Brief
		Overloaded compound division assignment operator.
		Divides current 2D vector with a scalar value.

	\Param rhs
		Scalar value to be divided by.

	\Return
		Returns a reference to the modified 2D vector
	-----------------------------------------------------------*/
	Vector2D& Vector2D::operator /= (float rhs)
	{
		x /= rhs;
		y /= rhs;

		return *this;
	}

	/*-----------------------------------------------------------
	\Brief
		Overloaded unary negation operator. 
		Negates the current 2D vector.


	\Return
		Returns the negated 2D vector
	-----------------------------------------------------------*/
	Vector2D Vector2D::operator - () const
	{
		return {-x, -y};
	}

	/*-----------------------------------------------------------
	\Brief
		Overloaded addition operator.
		Adds 2 2D vectors together

	\Param lhs
		Left hand side 2D vector

	\Param rhs
		Right hand side 2D vector

	\Return
		Returns the result of the addition.
	-----------------------------------------------------------*/
	Vector2D operator + (const Vector2D& lhs, const Vector2D& rhs)
	{
		Vector2D result;

		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;

		return result;
	}

	/*-----------------------------------------------------------
	\Brief
		Overloaded subtraction operator.
		Subtracts a 2D vector from another 2D vector

	\Param lhs
		Left hand side 2D vector

	\Param rhs
		Right hand side 2D vector

	\Return
		Returns the result of the subtraction.
	-----------------------------------------------------------*/
	Vector2D operator - (const Vector2D& lhs, const Vector2D& rhs)
	{
		Vector2D result;

		result.x = lhs.x - rhs.x;
		result.y = lhs.y - rhs.y;

		return result;
	}

	/*-----------------------------------------------------------
	\Brief
		Overloaded multiplication operator.
		Multiplies a 2D vector with a scalar value.

	\Param lhs
		Left hand side 2D vector

	\Param rhs
		Right hand side scalar value

	\Return
		Returns the result of the multiplication.
	-----------------------------------------------------------*/
	Vector2D operator * (const Vector2D& lhs, float rhs)
	{
		Vector2D result;

		result.x = lhs.x * rhs;
		result.y = lhs.y * rhs;

		return result;
	}

	/*-----------------------------------------------------------
	\Brief
		Overloaded multiplication operator.
		Multiplies a 2D vector with a scalar value.

	\Param lhs
		Left hand side scalar value

	\Param rhs
		Right hand side 2D vector

	\Return
		Returns the result of the multiplication.
	-----------------------------------------------------------*/
	Vector2D operator * (float lhs, const Vector2D& rhs)
	{
		Vector2D result;

		result.x = lhs * rhs.x;
		result.y = lhs * rhs.y;

		return result;
	}

	/*-----------------------------------------------------------
	\Brief
		Overloaded division operator.
		Divides a 2D vector with a scalar value.

	\Param lhs
		Left hand side 2D vector

	\Param rhs
		Right hand side scalar value

	\Return
		Returns the result of the division.
	-----------------------------------------------------------*/
	Vector2D operator / (const Vector2D& lhs, float rhs)
	{
		Vector2D result;

		result.x = lhs.x / rhs;
		result.y = lhs.y / rhs;

		return result;
	}

	/*-----------------------------------------------------------
	\Brief
		Function to normalise a 2D vector

	\Param pResult
		The normalised 2D vector.

	\Param rhs
		2D vector to be normlaised.
	-----------------------------------------------------------*/
	void	Vector2DNormalize(Vector2D& pResult, const Vector2D& pVec0)
	{
		float len = Vector2DLength(pVec0);
		pResult = pVec0;
		pResult /= len;
	}

	/*-----------------------------------------------------------
	\Brief
		Function to calculate the length of a 2D vector.

	\Param pVec0
		2D vector being used for calculation

	\Return
		Returns the length of the 2D vector.
	-----------------------------------------------------------*/
	float	Vector2DLength(const Vector2D& pVec0)
	{
		return sqrtf(pVec0.x * pVec0.x + pVec0.y * pVec0.y);
	}

	/*-----------------------------------------------------------
	\Brief
		Function to calculate the squared length of a 2D vector.

	\Param pVec0
		2D vector being used for calculation

	\Return
		Returns the squared length of the 2D vector.
	-----------------------------------------------------------*/
	float	Vector2DSquareLength(const Vector2D& pVec0)
	{
		return powf(pVec0.x, 2.0f) + powf(pVec0.y, 2.0f);
	}

	/*-----------------------------------------------------------
	\Brief
		Function to calculate the distance between 2 2D vectors.

	\Param pVec0
		First 2D vector

	\Param pVec1
		Second 2D vector

	\Return
		Returns the distance between the 2 2D vectors.
	-----------------------------------------------------------*/
	float	Vector2DDistance(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		float x_dist = pVec0.x - pVec1.x;
		float y_dist = pVec0.y - pVec1.y;

		return sqrtf(powf(x_dist, 2.0f) + powf(y_dist, 2.0f));
	}

	/*-----------------------------------------------------------
	\Brief
		Function to calculate the squared distance between 2 2D vectors.

	\Param pVec0
		First 2D vector

	\Param pVec1
		Second 2D vector

	\Return
		Returns the squared distance between the 2 2D vectors.
	-----------------------------------------------------------*/
	float	Vector2DSquareDistance(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		float x_dist = pVec0.x - pVec1.x;
		float y_dist = pVec0.y - pVec1.y;

		return powf(x_dist, 2.0f) + powf(y_dist, 2.0f);
	}

	/*-----------------------------------------------------------
	\Brief
		Function to get the dot product between 2 2D vectors.

	\Param pVec0
		First 2D vector

	\Param pVec1
		Second 2D vector

	\Return
		Returns the dot product of the 2 2D vectors.
	-----------------------------------------------------------*/
	float	Vector2DDotProduct(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		return (pVec0.x * pVec1.x) + (pVec0.y * pVec1.y);
	}

	/*-----------------------------------------------------------
	\Brief
		Function to get the cross product between 2 2D vectors.

	\Param pVec0
		First 2D vector

	\Param pVec1
		Second 2D vector

	\Return
		Returns the cross product of the 2 2D vectors.
	-----------------------------------------------------------*/
	float	Vector2DCrossProductMag(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		return (pVec0.x * pVec1.y) - (pVec0.y * pVec1.x);
	}

}