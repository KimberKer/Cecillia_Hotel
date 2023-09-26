#include "Vector2D.h"
#include <math.h>
#include <iostream>

namespace MathLib
{

	Vector2D::Vector2D(float _x, float _y) : x(_x), y(_y) {};

	Vector2D& Vector2D::operator += (const Vector2D& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vector2D& Vector2D::operator -= (const Vector2D& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	Vector2D& Vector2D::operator *= (float rhs)
	{
		x *= rhs;
		y *= rhs;

		return *this;
	}

	Vector2D& Vector2D::operator /= (float rhs)
	{
		x /= rhs;
		y /= rhs;

		return *this;
	}

	Vector2D Vector2D::operator - () const
	{
		return { -x, -y };
	}

	Vector2D operator + (const Vector2D& lhs, const Vector2D& rhs)
	{
		Vector2D result;

		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;

		return result;
	}

	Vector2D operator - (const Vector2D& lhs, const Vector2D& rhs)
	{
		Vector2D result;

		result.x = lhs.x - rhs.x;
		result.y = lhs.y - rhs.y;

		return result;
	}

	Vector2D operator * (const Vector2D& lhs, float rhs)
	{
		Vector2D result;

		result.x = lhs.x * rhs;
		result.y = lhs.y * rhs;

		return result;
	}

	Vector2D operator * (float lhs, const Vector2D& rhs)
	{
		Vector2D result;

		result.x = lhs * rhs.x;
		result.y = lhs * rhs.y;

		return result;
	}

	Vector2D operator / (const Vector2D& lhs, float rhs)
	{
		Vector2D result;

		result.x = lhs.x / rhs;
		result.y = lhs.y / rhs;

		return result;
	}

	void	Vector2DNormalize(Vector2D& pResult, const Vector2D& pVec0)
	{
		float len = Vector2DLength(pVec0);
		pResult = pVec0;
		pResult /= len;
	}

	float	Vector2DLength(const Vector2D& pVec0)
	{
		return sqrtf(pVec0.x * pVec0.x + pVec0.y * pVec0.y);
	}

	float	Vector2DSquareLength(const Vector2D& pVec0)
	{
		return powf(pVec0.x, 2.0f) + powf(pVec0.y, 2.0f);
	}

	float	Vector2DDistance(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		float x_dist = pVec0.x - pVec1.x;
		float y_dist = pVec0.y - pVec1.y;

		return sqrtf(powf(x_dist, 2.0f) + powf(y_dist, 2.0f));
	}

	float	Vector2DSquareDistance(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		float x_dist = pVec0.x - pVec1.x;
		float y_dist = pVec0.y - pVec1.y;

		return powf(x_dist, 2.0f) + powf(y_dist, 2.0f);
	}

	float	Vector2DDotProduct(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		return (pVec0.x * pVec1.x) + (pVec0.y * pVec1.y);
	}

	float	Vector2DCrossProductMag(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		return (pVec0.x * pVec1.y) - (pVec0.y * pVec1.x);
	}

}